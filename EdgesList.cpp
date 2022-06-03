#include "EdgesList.hpp"
#include "meta.hpp"

EdgeWeight defaultEdgeWeight = 1;

EdgesList::EdgesList(std::istream &dataStream) {
    std::string curEdge;
    std::stringstream iss;

    while (std::getline(dataStream, curEdge)) {
        iss << curEdge;
        std::string from;
        std::string to;
        EdgeWeight weight = defaultEdgeWeight;

        iss >> from >> to >> weight;
        assertm(from.size() != 0 and to.size() != 0, "Sizes must be not zeros");
        
        addEdge(Edge{std::move(from), std::move(to), weight});
        iss.clear();
    }
}
    // Если будем преобразовывать в невзвешенный граф, то важно само наличие ребра, его вес даже не пробуем читать.
    // Если преобразуем во взвешенный, то вес будет 0. - всё ок.
    // Можно добавить спец флаг, взвеш/не_взвеш/дефолт, вручную ставит его.
    // и/Или сделать более строгий метод чтения данных, который бы не пропустил отсутствие весов при чтении для взвеш. графа.

void EdgesList::addEdge(Edge edge) {
    edges.push_back(edge);
}

VerticesVector EdgesList::getVertices() const {
    VerticesVector unqVertices;
    for (auto [from, to, weight] : edges) {
        unqVertices.emplace_back(from);
        unqVertices.emplace_back(to);
    }
    unqVertices.erase(std::unique(std::begin(unqVertices), std::end(unqVertices)),
                         std::end(unqVertices));
    return unqVertices;
}

EdgesVector EdgesList::getEdges() const {
    return edges;
}

// Можно ли так делать?
std::vector<Edge>::const_iterator EdgesList::begin() const {
    return edges.cbegin();
}

std::vector<Edge>::const_iterator EdgesList::end() const {
    return edges.cend();
}

std::ostream& operator<<(std::ostream &out, const EdgesList& edgesList){
    for (const auto &[from, to, weight] : edgesList.edges)
        out << from << " - " << to << ": " << weight << "\n";
    return out;
}