#include "blocking_queue.h"
#include <iostream>
#include <thread>

int main() {
    rau::blocking_queue<int> q(6);

    std::thread producer([&] {
        for (int i = 1; i <= 6; ++i) {
            q.push(i);
            std::cout << "Prod: " << i << "\n";
        }
    });

    std::thread consumer([&] {
        for (int i = 0; i < 6; ++i) {
            const int val = q.pop();
            std::cout << "cons: " << val << "\n";
        }
    });

    producer.join();
    consumer.join();

    rau::blocking_queue<int> q2(5);
    q2.push(100);

    if (const auto val = q2.try_pop()) {
        std::cout << "try_poP: " << *val << "\n";
    }

    if (!q2.try_pop()) {
        std::cout << "try_poP: empty\n";
    }

    return 0;
}
