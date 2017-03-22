#pragma once

#include "hash_128.hpp"

#include <memory>
#include <cstdint>

namespace dedupe
{

template <typename T>
struct hamming_metric;

template <>
struct hamming_metric<std::uint8_t>
{
    using distance_type = std::uint8_t;
    
    constexpr static std::uint8_t table[16] = {
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
    };
    
    distance_type distance(std::uint8_t first, std::uint8_t second) const
    {
        const auto bw_xor = first ^ second;
        return table[bw_xor & 0xF] + table[(bw_xor >> 4) & 0xF];
    }
};

constexpr std::uint8_t hamming_metric<std::uint8_t>::table[];

template <>
struct hamming_metric<std::uint16_t>
{
    using distance_type = std::uint8_t;
    
    distance_type distance(std::uint16_t first, std::uint16_t second) const
    {
        const auto bw_xor = first ^ second;
        return hamming_metric<std::uint8_t>::table[bw_xor & 0xF] +
               hamming_metric<std::uint8_t>::table[(bw_xor >> 4) & 0xF] +
               hamming_metric<std::uint8_t>::table[(bw_xor >> 8) & 0xF] +
               hamming_metric<std::uint8_t>::table[(bw_xor >> 12) & 0xF];
    }
};

template <>
struct hamming_metric<std::uint32_t>
{
    using distance_type = std::uint8_t;
    
    distance_type distance(std::uint32_t first, std::uint32_t second) const
    {
        // Taken from Hacker's Delight, 2nd edition, Figure 5-2.
        auto bw_xor = first ^ second;
        bw_xor = bw_xor - ((bw_xor >> 1) & 0x55555555);
        bw_xor = (bw_xor & 0x33333333) + ((bw_xor >> 2) & 0x33333333);
        bw_xor = (bw_xor + (bw_xor >> 4)) & 0x0F0F0F0F;
        bw_xor = bw_xor + (bw_xor >> 8);
        bw_xor = bw_xor + (bw_xor >> 16);
        return bw_xor & 0x0000003F;
    }
};

template <>
struct hamming_metric<hash_128>
{
    using distance_type = std::uint8_t;
    
    distance_type distance(hash_128 first, hash_128 second)
    {
        
    }
};

} // end namespace dedupe
