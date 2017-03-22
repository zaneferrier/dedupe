#pragma once

#include "make_unique.hpp"

#include <memory>
#include <unordered_map>

namespace dedupe
{
namespace detail
{

template <typename T, typename Metric>
struct kd_node
{
public:

    explicit kd_node(T item)
        : value(std::move(item))
    { }
    
private:

    using distance_type = typename Metric::distance_type;
    using store_type = std::unordered_map<distance_type, std::unique_ptr<kd_node>>;
        
    Metric     metric;
    store_type children;
    T          value;
};

} // end namespace detail

template <typename T, typename Metric>
class kd_tree
{
public:

    using distance_type = typename Metric::distance_type;
    
    kd_tree() = default;
    
    explicit kd_tree(T item)
        : root(make_unique<detail::kd_node<T, Metric>>(std::move(item)))
    { }
    
private:
    
    using node_type = detail::kd_node<T, Metric>;
    
    std::unique_ptr<node_type> root;
};

} // end namespace dedupe
