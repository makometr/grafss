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
// #include "edge.hpp"



template <typename NameT, typename WeightT>
class Graph {
public:
    Graph() = default;
    Graph(std::istream &in);
    // std::optional<std::pair<std::vector<Vertex<NameT>>, WeightT>> findMinByDeijkstra(Vertex<NameT> start, Vertex<NameT> finish);
    const std::map<Vertex<NameT>, WeightT>& getAdjVerices(const Vertex<NameT> &vertex) const;

    template <typename NameTT, typename WeightTT>
    friend std::ostream& operator <<(std::ostream &out, const Graph<NameTT, WeightTT>& list);

private:
    std::map<Vertex<NameT>, std::map<Vertex<NameT>, WeightT>> AdjList;
};

template<typename NameT, typename WeightT>
const std::map<Vertex<NameT>, WeightT>&
Graph<NameT, WeightT>::getAdjVerices(const Vertex<NameT> &vertex) const {
    return AdjList.at(vertex);
}

template<typename NameT, typename WeightT>
Graph<NameT, WeightT>::Graph(std::istream &dataStream) {
    std::string curEdge;
    std::stringstream iss;

    while (std::getline(dataStream, curEdge)) {
        iss << curEdge;
        Vertex<NameT> from;
        Vertex<NameT> to;
        WeightT weight;

        iss >> from >> to >> weight;
        // assertm(from.size() != 0 and to.size() != 0, "Sizes must be not zeros");
        AdjList[from][to] = weight;
        AdjList[to][from] = weight;
        
        
        iss.clear();
    }
}

template<typename NameT, typename WeightT>
std::ostream& operator<<(std::ostream &out, const Graph<NameT, WeightT>& graph){
    for (const auto& [main_vertex, list] : graph.AdjList) {
        out << main_vertex << ": ";
        for (const auto& [adj_vertex, weight] : list)
            out << "(" << adj_vertex << " - " << weight << ") ";
        out << "\n";
    }
    out << std::endl;
    return out;
}

template <typename NameT, typename WeightT>
std::optional<std::vector<std::pair<Vertex<NameT>, WeightT>>>
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

    std::vector<VertexLabel> orderedKeys;
    orderedKeys.reserve(visited.size());
    std::copy(visited.begin(), visited.end(), std::back_inserter(orderedKeys));
    std::sort(orderedKeys.begin(), orderedKeys.end());

    return {orderedKeys};
}



int main() {
    std::stringstream stream{"0 3 8\n\
                              0 4 8\n\
                              1 3 9\n\
                              2 5 7\n\
                              2 6 8\n\
                              3 0 8\n\
                              3 1 9\n\
                              3 5 5\n\
                              4 0 8\n\
                              4 6 4\n\
                              4 7 2\n\
                              5 2 7\n\
                              5 3 5\n\
                              5 6 7\n\
                              5 7 9\n\
                              6 2 8\n\
                              6 4 4\n\
                              6 5 7\n\
                              7 4 2\n\
                              7 5 9\n"
    };
    Graph<std::string, int> graph{stream};
    std::cout << graph;


    if (auto result = findMinByDeijkstra(graph, {"5"}); result) {
        for (const auto &[vertex, path] : result.value()) {
            std::cout << vertex << ": " << path << "\n";
        }
    } else {
        std::cout << "No path!\n";
    }
}