#pragma once
#include <stdexcept>

template<typename T, bool Nullable = false> class ptr {
public:
    ptr() {
        static_assert(Nullable, "Trying to empty-initialize non-nullable pointer");
        value = nullptr;
    }

    ptr(T *raw) {
        if constexpr (!Nullable) {
            if (!raw) {
                throw std::logic_error {"Trying to initialize non-nullable pointer with raw null pointer"};
            }
        }
        value = raw;
    }

    ptr(ptr<T, false> &&other) {
        static_assert(!Nullable);
        value = std::move(other.value);
        other.value = nullptr;
    }

    ptr(ptr<T, true> &&other) {
        value = std::move(other.value);
        other.value = nullptr;
    }

    ptr(const ptr &other) = delete;
    ptr &operator =(const ptr &other) = delete;

    ~ptr() {
        if constexpr (Nullable) {
            if (!value) {
                return;
            }
        }
        delete value;
    }

    T *operator ->() {
        if constexpr (Nullable) {
            if (!value) {
                throw std::logic_error {"Null pointer access"};
            }
        }
        return value;
    }

    T operator *() {
        if constexpr (Nullable) {
            if (!value) {
                throw std::logic_error {"Null pointer dereferencing"};
            }
        }
        return *value;
    }

    operator bool() {
        return (bool) value;
    }

    template<typename ... V> static ptr<T> create(const V &... args) {
        return std::move(ptr<T>(new T(args...)));
    };

    friend std::ostream &operator <<(std::ostream &o, const ptr &p) {
        return o << "pointer@" << p.value;
    }

private:

    T *value;
};