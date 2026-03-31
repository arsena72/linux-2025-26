#include "thread_pool.h"
#include <iostream>

int add(const int a, const int b) { return a + b; }

int main() {
    thread_pool pool;

    auto f1 = pool.enqueue(add, 1, 2);
    auto f2 = pool.enqueue(add, 213, 233);

    auto f3 = pool.enqueue([] {
        std::cout << "FrOm THE THREAD       ";
    });

    std::cout << "1 + 2 = "   << f1.get() << "\n";
    std::cout << "213 + 233 = " << f2.get() << "\n";
    f3.get();
}
