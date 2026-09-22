#include <cassert>  // assert
#include <cstddef>  // size_t
#include <cstdint>  // uint64_t, uint32_t

// Expands the binary representation of input by a factor of scale.
// e.g., expand(0b1111ull, 3) == 0b001001001001
uint64_t expand(uint64_t input, uint32_t scale) {
    assert(scale >= 1);
    uint64_t result = 0;
    for (uint32_t i = 0; i < 64; ++i) {
        uint64_t position = static_cast<uint64_t>(i) * scale;
        if (position >= 64) {
            break;
        }
        if ((input >> i) & 1ULL) {
            result |= (1ULL << position);
        }
    }
    return result;
}

int main() {
    assert(expand(0b1111, 3) == 0b001001001001);
    assert(expand(0b0101, 2) == 0b00010001);
    assert(expand(0b1111, 1) == 0b1111);  // scale of 1 should return the same number
    assert(expand(0, 2) == 0);
    // check for overflow and undefined behavior
    assert(expand(0b11, 40) == ((1ULL << 40) | 1ULL));
    assert(expand(1ULL << 32, 2) == 0);
    assert(expand(0b111, 64) == 1);
    return 0;
}
