#pragma once

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <type_traits>

class thread_pool {
    public:
        explicit thread_pool(const size_t threads = std::thread::hardware_concurrency()) : stop_(false)
        {
            for (size_t i = 0; i < threads; ++i) {
                workers_.emplace_back([this] {
                    for (;;) {
                        std::function<void()> task;
                        {
                            std::unique_lock lock(mtx_);
                            cv_.wait(lock, [this] {
                                return stop_ || !tasks_.empty();
                            });

                            if (stop_ && tasks_.empty()) return;

                            task = std::move(tasks_.front());
                            tasks_.pop();
                        }
                        task();
                    }
                });
            }
        }

        ~thread_pool() {
            {
                std::lock_guard lock(mtx_);
                stop_ = true;
            }
            cv_.notify_all();
            for (auto& worker : workers_) {
                if (worker.joinable()) worker.join();
            }
        }

        template<typename F, typename... Args>
        auto enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
            using return_type = std::invoke_result_t<F, Args...>;

            auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

            std::future<return_type> res = task->get_future();
            {
                std::lock_guard lock(mtx_);
                if (stop_) throw std::runtime_error("");

                tasks_.emplace([task] {
                    (*task)();
                });
            }
            cv_.notify_one();

            return res;
        }

        thread_pool(const thread_pool&) = delete;
        thread_pool& operator=(const thread_pool&) = delete;

    private:
        std::vector<std::thread> workers_;
        std::queue<std::function<void()>> tasks_;

        std::mutex mtx_;
        std::condition_variable cv_;
        bool stop_;
};