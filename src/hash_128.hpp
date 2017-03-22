#pragma once

#include <cstdint>

namespace dedupe
{
    
struct hash_128
{
    explicit hash_128(std::uint64_t low)
        : top(0),
          bottom(low)
    { }
    
    hash_128(std::uint64_t high, std::uint64_t low)
        : top(high),
          bottom(low)
    { }
    
    std::uint64_t upper() const
    {
        return top;
    }
    
    std::uint64_t lower() const
    {
        return bottom;
    }
    
private:
    
    friend hash_128& operator^=(hash_128& lhs, hash_128 rhs);
    
    std::uint64_t top;
    std::uint64_t bottom;
};

hash_128& operator^=(hash_128& lhs, hash_128 rhs)
{
    lhs.top ^= rhs.top;
    lhs.bottom ^= rhs.bottom;
}

hash_128 operator^(hash_128 lhs, hash_128 rhs)
{
    hash_128 cpy(lhs);
    cpy ^= rhs;
}

} // end namespace dedupe
    
