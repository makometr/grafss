#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <iomanip>
#include <optional>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include "vertex.hpp"

template <typename NameT, typename WeightT>
std::optional<std::pair<std::vector<Vertex<NameT>>, WeightT>>
findMinByDeijkstra(const Graph<NameT, WeightT> &graph, Vertex<NameT> start) {
    // using Label = std::optional<WeightT>;
    using VertexLabel = std::pair<Vertex<NameT>, WeightT>;
    auto VLComparator = [](const VertexLabel &lhs, const VertexLabel &rhs) {
        return lhs.second > rhs.second;
    };
    std::priority_queue<VertexLabel, std::vector<VertexLabel>, decltype(VLComparator)> pqueue {VLComparator};
    // auto hasher = [](const Vertex<NameT> &vertex) { return std::hash<NameT>()(vertex);};
    std::unordered_map<Vertex<NameT>, WeightT, vertex_hasher<NameT>> visited {};


    pqueue.push({start, 0});
    while (!pqueue.empty()) {
        auto &[curVer, curLabel] = pqueue.top();
        if (visited.count(curVer) == 0) {
            visited.insert({curVer, curLabel});
            for (const auto &[adjVertex, weight] : graph.getAdjVerices(curVer)) {
                auto newLabel = curLabel + weight;
                pqueue.push({adjVertex, newLabel});
            }
        }
        pqueue.pop();
    }

    // for (const auto &[vertex, path] : visited) {
    //     std::cout << vertex << " " << path << "\n";
    // }

    std::vector<Vertex<NameT>> orderedKeys;
    orderedKeys.reserve(visited.size());
    std::transform(visited.begin(), visited.end(), std::back_inserter(orderedKeys), [](const auto &pair){
        return pair.first;
    });
    std::sort(orderedKeys.begin(), orderedKeys.end());
    for (const auto &elem: orderedKeys) {
        std::cout << elem << ": " <<  visited[elem] << std::endl;
    }


    return std::nullopt;
}