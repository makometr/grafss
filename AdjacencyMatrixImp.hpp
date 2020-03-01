#pragma once
#include "meta.hpp"

// Матрица смежности
class AdjacencyMatrixImp {
private:
    std::map<VertexName, int> VertexIds; // Хранение пар имя - id
    // std::vector<std::pair<VertexName, std::int>> VertexIds; // можно ещё так
    std::vector<std::vector<int>> AdjMatrix; // Сама матрица

public:
    AdjacencyMatrixImp() = default;
    AdjacencyMatrixImp(const EdgesList &graf_repr){
        // Создадим id для каждой именованной вершины.
        auto allVertices = graf_repr.getVertices();
        size_t currentIndex = 0;
        for (const auto &vertex: allVertices)
            VertexIds[vertex] = currentIndex++;
        
        // Создаём пустой двумерный массив нужной длины.
        AdjMatrix.resize(allVertices.size());
        for (auto &vector : AdjMatrix)
            vector.resize(allVertices.size(), 0);
        
        for (const auto &[from, to, weight]: graf_repr){
            // Мы уверены, что найдем их, поэтому не проверяем возвращаемое значение.
            auto [_, id_from] = *VertexIds.find(from);
            auto [__,  id_to] = *VertexIds.find(to);
            AdjMatrix[id_from][id_to] = weight;
        }
    }

    // EdgesList getUnifiedRepr() const override {
    //     EdgesList repr;
    //     return repr;
    // }
    friend std::ostream& operator<<(std::ostream &out, const AdjacencyMatrixImp& list);
};

std::ostream& operator<<(std::ostream &out, const AdjacencyMatrixImp& list){
    out << "IDs: ";
    for (const auto& [vertex_name, id] : list.VertexIds)
        out << "(" << vertex_name << " - " << id << ") ";
    out << std::endl;

    out << "Matrix:\n";
    for (const auto& row : list.AdjMatrix){
        for (const auto& elem : row)
            out << std::setw(2) << elem << " ";
        out << std::endl;
    }
    return out;
}