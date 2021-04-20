//
// Created by Tobi on 20/04/2021.
//

#pragma once
#include <ks/fs.h>
#include <ks/array.h>
#include <xxh3.h>

template<class T>
XXH128_hash_t hash_bytes(ArrayRef<T> data, size_t length) {
    return XXH128(&data, length * sizeof(T), 0); // TODO: see if this seed affects performance / hashing-proficiency
}

template<class T>
XXH128_hash_t hash_bytes(const Array<T> &bytes) {
    return hash_bytes((ArrayRef<T>) bytes.data(), bytes.size());
}