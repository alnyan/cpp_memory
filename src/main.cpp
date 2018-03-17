#include <iostream>
#include "pointer.hpp"

class TestClass {
public:
    TestClass() {
        std::cout << "Constructor " << this << std::endl;
    }

    ~TestClass() {
        std::cout << "Destructor " << this << std::endl;
    }
};

int main() {
    try {
        shared_ptr x = new TestClass;
        shared_ptr<TestClass, true> p = nullptr;

        *p;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}