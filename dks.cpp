#include <iostream>
#include <sstream>
#include <map>
#include <iomanip>

template <typename NameT>
class Vertex {
    Vertex(NameT name) : name(name) {};

private:
    NameT name;
};


template <typename NameT, typename WeightT>
class Graph {
public:
    Graph() = default;
    Graph(std::istream &in);

    template <typename NameTT, typename WeightTT>
    friend std::ostream& operator <<(std::ostream &out, const Graph<NameTT, WeightTT>& list);

private:
    std::map<Vertex<NameT>, std::map<Vertex<NameT>, WeightT>> AdjList;
};

template<typename NameT, typename WeightT>
Graph<NameT, WeightT>::Graph(std::istream &dataStream) {
    std::string curEdge;
    std::stringstream iss;

    while (std::getline(dataStream, curEdge)) {
        iss << curEdge;
        NameT from;
        NameT to;
        WeightT weight;

        iss >> from >> to >> weight;
        // assertm(from.size() != 0 and to.size() != 0, "Sizes must be not zeros");
        
        // addEdge(Edge{std::move(from), std::move(to), weight});
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
    return out;
}


int main() {
    std::stringstream stream{"A B 1\nB C 2\nC D 3\nB D 4\nA C 5\n"};
    Graph<std::string, int> graph{stream};
    std::cout << graph;

}