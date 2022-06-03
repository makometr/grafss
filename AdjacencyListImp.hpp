#pragma once
#include "meta.hpp"

bool isVertexAlreadyVisited(const VerticesVector &visited, Vertex checked) {
    auto it_result = std::find(std::begin(visited), std::end(visited), checked);
    if (it_result == std::end(visited))
        return false;
    return true;
}

class AdjacencyListImp {
private:
    std::map<Vertex, std::map<Vertex, EdgeWeight>> AdjList;

public:
    AdjacencyListImp() = default;
    AdjacencyListImp(const EdgesList &graf_repr) : AdjList() {
        for (auto &edge: graf_repr) {
            addEdge(edge);
        }
    }

    void addEdge(const Edge &newEdge) {
        auto [from, to, weight] = newEdge;
        AdjList[from][to] = weight;
    }

    bool isVertexAdj(Vertex mainV, Vertex checkedV) const {
        auto findedMain = AdjList.find(mainV);
        if (findedMain == std::end(AdjList))
            return false;

        const auto &adjVertices = AdjList.at(mainV);
        auto findedChecked = adjVertices.find(checkedV);
        if (findedChecked == std::end(adjVertices))
            return false;
        return true;
    }

    void makeUndirected() {
        EdgesVector newEdges;
        for (const auto &[fromVertex, listOfAdjVertices] : AdjList) {
            for (const auto& [adjVertex, weight] : listOfAdjVertices) {
                if (!isVertexAdj(adjVertex, fromVertex)) {
                    newEdges.push_back({adjVertex, fromVertex, weight});
                }
            }
        }
        for (auto newEdge : newEdges) {
            addEdge(newEdge);
        }
    }

    void printUnweighted(std::ostream &out) {
        out << "Adj List:\n";
        for (const auto& [main_vertex, adjVs] : AdjList){
            out << main_vertex << ": ";
            for (const auto& [adj_vertex, _] : adjVs)
                out << adj_vertex << " ";
            out << "\n";
        }
        out << std::endl;
    }












VerticesVector BFS(Vertex start) {
    VerticesVector vsVisited {start};
    std::queue<Vertex> vsQueue {};
    vsQueue.push(start);
    
    while (!vsQueue.empty()) {
        Vertex newVisited = vsQueue.front();
        vsQueue.pop();

        for (const auto &[adjV, _] : AdjList[newVisited]) {
            if (!isVertexAlreadyVisited(vsVisited, adjV)) {
                vsQueue.push(adjV);
                vsVisited.push_back(adjV);
            }
        }
    }
    return vsVisited;
}

    VerticesVector recursiveDFS(Vertex start) {
        VerticesVector result;
        dfs(result, start);
        return result;
    }

    VerticesVector iterativeDFS(Vertex startVertex) {
        // // auto firstVertex = AdjList.begin()->first;
        // VerticesVector result;
        // std::stack<Vertex> stack;
        // stack.push(firstVertex);

        // while (stack.empty() == false){
        //     auto vertex = stack.top();
        //     stack.pop();
        //     // std::cout << "Pop " << vertex << "\n";

        //     if (std::find(std::begin(result), std::end(result), vertex) == std::end(result)){
        //         result.push_back(vertex);
        //     }
        //     for (auto it = AdjList[vertex].rbegin(); it != AdjList[vertex].rend(); ++it){
        //         auto [adj_vertex, _] = *it;
        //         if (std::find(std::begin(result), std::end(result), adj_vertex) == std::end(result)){
        //             // std::cout << "Push " << adj_vertex << "\n";
        //             stack.push(adj_vertex);
        //         }
        //     }
        // }
        // return result;
    }

    // Новая реализация для ненаправленных графов. Теперь в dfs_cycle передается
    // ешё также название вызывающей вершины для того, чтобы корректно обрабатывать 
    // случай со смежной прошлой вершиной. Без этого функция будет корректно работать только на 
    // строго направленных графах.
    enum class Color { WHITE, GREY, BLACK };
    VerticesVector findCycleByDFS(Vertex firstVertex = {}){
        if (firstVertex == Vertex{})
            firstVertex = AdjList.begin()->first;
        
        VerticesVector visited;
        std::map<Vertex, Color> colored;
        for (const auto &[vertex, _] : AdjList) // Красим все вершины в белые
            colored[vertex] = Color::WHITE;

        auto isFinded = dfs_cycle(visited, colored, firstVertex, "");

        // Формируем цепочку вершин, которые состоят в цикле.
        VerticesVector VsInCycle; // Объявлена заранее для улучшения работы RVO.
        if (isFinded){
            auto firstVertexInCycle = visited.back(); // Начинаем с последней в цикле.
            VsInCycle.push_back(firstVertexInCycle);
            visited.pop_back();
            // И последовательно ищем последнюю, промежуточно запихивая в ответ промежуточные.
            while (!visited.empty()) {
                auto lastVertex = visited.back();
                VsInCycle.push_back(lastVertex);
                visited.pop_back();
                if (lastVertex == firstVertexInCycle)
                    break;
            }
        }
        return VsInCycle;
    }



    // EdgesList getUnifiedRepr() const override {
    //     EdgesList repr;
    //     for (const auto &[from, AdjVertices] : AdjList)
    //         for (const auto &[to, weight] : AdjVertices)
    //             repr.addEdge(Edge{from, to, weight});
    //     return repr;
    // }
    friend std::ostream& operator<<(std::ostream &out, const AdjacencyListImp& list);

private:

void dfs(VerticesVector& visitedVs, Vertex vertex) {
    visitedVs.push_back(vertex);
    for (const auto &[adjV, _] : AdjList[vertex]) {
        if (!isVertexAlreadyVisited(visitedVs, adjV)) {
            dfs(visitedVs, adjV);
        }
    }
}

    bool dfs_cycle(VerticesVector& visited, std::map<Vertex, Color>& colored, Vertex curV, Vertex fromVertex){
        static bool isCycleFinded = false;
        colored[curV] = Color::GREY;
        visited.push_back(curV);

        for (const auto [adjV, _] : AdjList[curV]){
            if (isCycleFinded) // Для досрочного выхода из рекурсии при нахождении цикла
                break;
            if (colored[adjV] == Color::WHITE){
                if (std::find(std::begin(visited), std::end(visited), adjV) == std::end(visited)){
                    dfs_cycle(visited, colored, adjV, curV);
                }
            }
            if ((colored[adjV] == Color::GREY) && (fromVertex != adjV)){
                if (!isCycleFinded){
                    // std::cout << "Cycle! from " << curV << " ";
                    visited.push_back(adjV);
                    // std::cout << "Push " << adjV << " " << visited.size() - 1 << "\n";
                }
                isCycleFinded = true;
            }
        }
        colored[curV] = Color::BLACK;
        return isCycleFinded;
    }
};  


std::ostream& operator<<(std::ostream &out, const AdjacencyListImp& adj_list){
    out << "Adj List:\n";
    for (const auto& [main_vertex, list] : adj_list.AdjList){
        out << main_vertex << ": ";
        for (const auto& [adj_vertex, weight] : list)
            out << "(" << adj_vertex << " - " << weight << ") ";
        out << "\n";
    }
    out << std::endl;
    return out;
}