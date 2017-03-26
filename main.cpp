#include "src/hamming.hpp"
#include "src/bk_tree.hpp"

#include <cassert>
#include <iostream>

int main(int argc, char **argv) 
{
    dedupe::hamming_metric<std::uint32_t> hd;
    assert(hd.distance(0, 0) == 0);
    assert(hd.distance(0, 255) == 8);
    
    dedupe::bk_tree<std::int32_t, decltype(hd)> tree;
}
