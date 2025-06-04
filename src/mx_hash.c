#include "mx/mx_hash.h"

#include <murmur_hash/murmur_hash.h>

void mx_murmur_hash_32(const void* key, int len, uint32_t seed, uint32_t* out) {
    *out = murmurhash(key, len, seed);
}

uint32_t mx_murmur_hash(const void* key, int len, uint32_t seed) {
    return murmurhash(key, len, seed);
}
