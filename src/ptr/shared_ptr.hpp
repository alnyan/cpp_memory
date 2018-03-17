#pragma once
#include "common.hpp"
#include <stdexcept>

template<typename T> class weak_ref;

class ptr_ref_count {
public:
    ptr_ref_count(): count{0} {
    }

    int inc() {
        return ++count;
    }

    int dec() {
        return --count;
    }

    int count;
};

template<typename T, bool Nullable = false, typename D = ptr_deleter> class shared_ptr {
public:
    shared_ptr() {
        static_assert(Nullable, "Trying to empty-initialize non-nullable pointer");
        value = nullptr;
        _refcount = nullptr;
    }

    shared_ptr(T *raw) {
        if constexpr (!Nullable) {
            if (!raw) {
                throw std::logic_error {"Trying to initialize non-nullable pointer with raw null pointer"};
            }

            _refcount = new ptr_ref_count;
            _refcount->inc();
        } else {
            if (raw) {
                _refcount = new ptr_ref_count;
                _refcount->inc();
            } else {
                _refcount = nullptr;
            }
        }
        value = raw;
    }

    shared_ptr(T *raw, D &&d) {
        if constexpr (!Nullable) {
            if (!raw) {
                throw std::logic_error {"Trying to initialize non-nullable pointer with raw null pointer"};
            }

            _refcount = new ptr_ref_count;
            _refcount->inc();
        } else {
            if (raw) {
                _refcount = new ptr_ref_count;
                _refcount->inc();
            } else {
                _refcount = nullptr;
            }
        }
        value = raw;
        deleter = std::move(d);
    }

    shared_ptr(const shared_ptr &other) {
        if constexpr (!Nullable) {
            if (_refcount->dec() == 0) {
                deleter(value);
                delete _refcount;
                value = nullptr;
                _refcount = nullptr;
            }
        }

        _refcount = other._refcount;
        value = other.value;
        _refcount->inc();
    }

    shared_ptr &operator =(const shared_ptr &other) {
        if constexpr (!Nullable) {
            if (_refcount->dec() == 0) {
                deleter(value);
                delete _refcount;
                value = nullptr;
                _refcount = nullptr;
            }

            _refcount = other._refcount;
            value = other.value;
            _refcount->inc();
        } else {
            if (value) {
                if (_refcount->dec() == 0) {
                    deleter(value);
                    delete _refcount;
                }
                value = nullptr;
                _refcount = nullptr;
            }

            if (other.value) {
                _refcount = other._refcount;
                value = other.value;
                _refcount->inc();
            }
        }

        return *this;
    }

    ~shared_ptr() {
        if constexpr (!Nullable) {
            if (_refcount) {
                if (_refcount->dec() == 0) {
                    deleter(value);
                    delete _refcount;
                }
            }
        } else {
            if (value) {
                if (_refcount->dec() == 0) {
                    deleter(value);
                    delete _refcount;
                }
            }
        }
    }

    T *get() const {
        return value;
    }

    T *operator ->() {
        if constexpr (!Nullable) {
            return value;
        } else {
            if (value) {
                return value;
            } else {
                throw std::logic_error {"Null pointer access"};
            }
        }
    }

    T operator *() {
        if constexpr (!Nullable) {
            return *value;
        } else {
            if (value) {
                return *value;
            } else {
                throw std::logic_error {"Null pointer dereferencing"};
            }
        }
    }

    int refcount() const {
        if constexpr (Nullable) {
            if (value) {
                return _refcount->count;
            } else {
                return 0;
            }
        } else {
            return _refcount->count;
        }
    }

    operator bool() {
        return (bool) value;
    }

protected:
    ptr_ref_count *_refcount;

private:

    D deleter;
    T *value;
};
