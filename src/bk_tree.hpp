#pragma once

#include "make_unique.hpp"

#include <memory>
#include <vector>
#include <unordered_map>

namespace dedupe
{
namespace detail
{

template <typename T, typename Metric>
struct bk_node
{
public:
    
    using distance_type = typename Metric::distance_type;
    
    explicit bk_node(T item)
        : value(std::move(item))
    { }
    
    bool insert(T item)
    {
        auto distance = metric.distance(value, item);
        if(distance == 0) { return false; }
        
        auto it = children.find(distance);
        if(it == children.end()) {
            auto node = make_unique<bk_node>(std::move(item));
            children.insert(std::make_pair(distance, std::move(node)));
            return true;
        } else {
            bk_node& child = *it->second;
            child.insert(std::move(item));
        }
    }
    
    void query(const T& item, distance_type max_distance, std::vector<T>& results) const
    {
        const auto distance = metric.distance(value, item);
        if(distance <= max_distance) {
            results.push_back(value);
            const auto min_sub = max_distance - distance;
            const auto max_sub = max_distance + distance;
            for(auto i = min_sub; i < max_sub; ++i) {
                auto it = children.find(i);
                if(it != children.end()) {
                    it->second->query(item, max_distance, results);
                }
            }
        }
    }
    
private:

    using store_type = std::unordered_map<distance_type, std::unique_ptr<bk_node>>;
        
    Metric     metric;
    store_type children;
    T          value;
};

} // end namespace detail

template <typename T, typename Metric>
class bk_tree
{
public:

    using distance_type = typename Metric::distance_type;
    
    bk_tree() = default;
    
    explicit bk_tree(T item)
        : root(make_unique<detail::bk_node<T, Metric>>(std::move(item)))
    { }
    
    bool insert(T item)
    {
        if(!root) { root = make_unique<node_type>(std::move(item)); }
        return root->insert(std::move(item));
    }
    
    std::vector<T> query(const T& item, distance_type max_distance) const
    {
        if(!root) return {};
        
        std::vector<T> results;
        root->query(item, max_distance, results);
        return results;
    }
    
private:
    
    using node_type = detail::bk_node<T, Metric>;
    
    std::unique_ptr<node_type> root;
};

} // end namespace dedupe
