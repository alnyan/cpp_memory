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

        std::cout << "x = " << x << std::endl;

        {
            std::cout << "Enter scope" << std::endl;
            shared_ptr x2(x);
            std::cout << "x = " << x << std::endl;
            std::cout << "x2 = " << x2 << std::endl;
            std::cout << "Exit scope" << std::endl;
        }

        std::cout << "x = " << x << std::endl;

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
