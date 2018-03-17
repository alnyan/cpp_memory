cpp_memory
==========

A collection of (reference) implementations of memory management-releated utility classes and functions. Requires C++17-compatible compiler to work properly (constexpr-if is used).

List of what's implemented:

* Shared pointer with ref. counting (null-safe), like std::shared_ptr: ptr/shared_ptr.hpp (or pointers.hpp)
* Unique pointer (null-safe), like std::unique_ptr: ptr/ptr.hpp (or pointers.hpp)
