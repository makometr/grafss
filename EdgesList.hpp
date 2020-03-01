#pragma once
#include "meta.hpp"

// Список рёбер
class EdgesList {
private:
    std::vector<Edge> edges;

public:
    EdgesList() = default;
    EdgesList(std::istream &dataStream){
        handleDataStream(dataStream);
    }

    void addEdge(Edge edge){
        edges.emplace_back(std::move(edge));
    }

std::vector<std::string> getVertices() const {
    std::vector<std::string> UniqueVertices;
    for (auto [from, to, weight] : edges){
        UniqueVertices.emplace_back(std::move(from));
        UniqueVertices.emplace_back(std::move(to));
    }
    UniqueVertices.erase(std::unique(std::begin(UniqueVertices), std::end(UniqueVertices)),
                    std::end(UniqueVertices));
    return UniqueVertices;
}
    // Можно ли так делать?
    auto begin() const {
        return edges.cbegin();
    }

    auto end() const {
        return edges.cend();
    }

friend std::ostream& operator<<(std::ostream &out, const EdgesList& edgesList){
    for (const auto &[from, to, weight] : edgesList.edges)
        out << from << " - " << to << ": " << weight << "\n";
    return out;
}

private:
void handleDataStream(std::istream &dataStream){
    std::string curEdge;
    std::stringstream iss;

    while (std::getline(dataStream, curEdge)){
        iss << curEdge;
        std::string from;
        std::string to;
        int defaultEdgeLength = 1;

        iss >> from >> to >> defaultEdgeLength;
        assertm(from.size() != 0 and to.size() != 0,"Sizes must be not zeros");
        
        addEdge(Edge{std::move(from), std::move(to), defaultEdgeLength});
        iss.clear();
    }
}
        // Если будем преобразовывать в невзвешенный граф, то важно само наличие ребра, его вес даже не пробуем читать.
        // Если преобразуем во взвешенный, то вес будет 0. - всё ок.
        // Можно добавить спец флаг, взвеш/не_взвеш/дефолт, вручную ставит его.
        // и/Или сделать более строгий метод чтения данных, который бы не пропустил отсутствие весов при чтении для взвеш. графа.
};