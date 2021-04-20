//
// Created by tobia on 22/02/2021.
//

#pragma once

#include <memory>
#include <string>
#include <vector>
#ifndef NDEBUG
#include <sstream>
#endif

template<class T>
using ArrayRef = T(&)[];
template<class T>
using ArrayPtr = T(*)[];

template<class T>
class Array {
    size_t size_;
    std::unique_ptr<T[]> data_;


public:
    using RefType = ArrayRef<T>;
    using PtrType = ArrayPtr<T>;

    Array(const size_t size, T const *const data_to_copy) : Array(size) {
        std::copy_n(data_to_copy, this->size(), data());
//        std::uninitialized_copy_n(other.data(), len(), data());  // TODO: implement without make_unique / copy_n - for no redundant default initialisation
    }


    Array(T const *const data_to_own, const size_t size) : size_(size), data_(data_to_own) {}

    Array(const size_t size, T *const data_to_copy) : Array(size) {
        std::copy_n(data_to_copy, this->size(), data());
//        std::uninitialized_copy_n(other.data(), len(), data());  // TODO: implement without make_unique / copy_n - for no redundant default initialisation
    }

//    Array &operator=(const Array &other) {
////        std::uninitialized_copy_n(other.data(), size(), data());  // TODO: implement without make_unique / copy_n - for no redundant default initialisation
//        size_ = other.size();
//        data_ = std::make_unique<T[]>(size_);
//        std::copy_n(other.data(), size(), data());
//        return *this;
//    }

    Array(size_t size, std::unique_ptr<T[]> &&data) : size_(size),
                                                      data_(std::move(data)) {}

    Array(const std::vector<T> &data_to_copy) : Array(data_to_copy.size(), data_to_copy.data()) {}

    Array(const Array &data_to_copy) : Array(data_to_copy.size(), data_to_copy.data_.get()) {}

    Array(Array &&other) : size_(other.size_),
                           data_(std::move(other.data_)) {}

    inline explicit Array(const size_t size) : size_(size),
                                               data_(std::make_unique<T[]>(size)) {}

    operator T *() {
        return c_data();
    }

    inline T &operator[](size_t index) const {
        return data_[index];
    }

    inline RefType data() const {
        return *(PtrType) data_.get();
    }

    inline T *c_data() const {
        return data_.get();
    }

    inline RefType release_ptr() {
        return *(PtrType) data_.release();
    }

    inline std::unique_ptr<T[]> release() {
        return std::move(data_);
    }

    inline auto size() const {
        return size_;
    }

#ifndef NDEBUG

    [[nodiscard]] std::string to_string() const {
        std::stringstream ss;
        ss << "{";
        if (size_ != 0) {
            for (int i = 0; i < size_ - 1; ++i) {
                ss << std::to_string(data_[i]) << ", ";
            }
            ss << data_[size_ - 1];
        }
        ss << "}";

        return ss.str();
    }

#endif
};

using ByteArray = Array<uint8_t>;