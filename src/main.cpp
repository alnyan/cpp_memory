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

    void method() {
        std::cout << "TestClass::method" << std::endl;
    }
};

int main() {
    try {
        shared_ptr x = new TestClass;

        x->method();

        shared_ptr<TestClass, true> p = nullptr;

        p->method();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        ptr x = new TestClass;

        x->method();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
