#pragma once

class ptr_deleter {
public:
    template<typename T> void operator()(T *ptr) {
        if constexpr (std::is_array<T>::value) {
            delete []ptr;
        } else {
            delete ptr;
        }
    }
};

