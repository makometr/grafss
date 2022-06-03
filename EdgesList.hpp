#pragma once
#include "meta.hpp"

// Список рёбер.
// Промежуточное стандартное простое представление.
// Также хорошо подходит для разреженных графов.

class EdgesList {
    std::vector<Edge> edges;
public:
    EdgesList() = default;
    EdgesList(std::istream &dataStream);
    ~EdgesList() noexcept = default;

    void addEdge(Edge edge);

    VerticesVector getVertices() const;
    EdgesVector getEdges() const;
    
    std::vector<Edge>::const_iterator begin() const;
    std::vector<Edge>::const_iterator end() const;

    friend std::ostream& operator<<(std::ostream &out, const EdgesList& edgesList);
};