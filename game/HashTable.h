#pragma once

#include <cstdint>

template<typename K, typename V>
class HashTable {
    K* keys;
    V* values;
    uint32_t count;
    uint32_t max_count;
    int unk;
    uint32_t value_size;
public:
    V* Get(K key) {
        uint64_t hash_value = (((uint64_t)key * 0x9e3779b1) >> 32) ^ ((uint64_t)key * 0x9e3779b1);
        uint32_t index = hash_value % max_count;

        uint32_t current_key = keys[index];

        while (current_key != key) {
            if (current_key == 0) {
                return nullptr;
            }

            index = (index + 1) % max_count;
            current_key = this->keys[index];
        }

        return &values[index];
    }
};