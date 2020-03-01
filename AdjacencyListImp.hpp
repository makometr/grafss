#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <cassert>



// Список смежности
class AdjacencyListImp {
private:
    std::map<VertexName, std::list<SemiEdge>> AdjList;
    // std::list<std::pair<VertexName, std::list<SemiEdge>> AdjList_Alt;

public:
    AdjacencyListImp() = default;
    AdjacencyListImp(const EdgesList &graf_repr){
        auto allVertices = graf_repr.getVertices();
        for (auto vertex : allVertices)
            AdjList[vertex].clear(); // Костыль для инициализации всех значений
        
        for (auto [from, to, weight]: graf_repr){
            AdjList[from].emplace_back(SemiEdge{std::move(to), std::move(weight)});
        }
    }

    void addAdjVertex(VertexName mainV, VertexName adjV, EdgeWeight weight = 1){
        AdjList[mainV].push_back({std::move(adjV), weight});
    }

    bool isVertexAdj(VertexName mainV, VertexName checkedV) const {
        // Except on wrong mainV
        auto res = std::find_if(std::begin(AdjList.at(mainV)), std::end(AdjList.at(mainV)),
                [&checkedV](const SemiEdge& sem_edge){ return sem_edge.first == checkedV; }
        );
        return !(res == std::end(AdjList.at(mainV)));
    }

    void makeUndirected(){
        for (const auto &[curV, adjVsOfCur] : AdjList){
            for (const auto& [adjV, weight] : adjVsOfCur){
                if (!isVertexAdj(adjV, curV)){
                    addAdjVertex(adjV, curV);
                }
            }
        }
    }

    ListOfVertices recursiveDFS(){
        auto firstVertex = AdjList.begin()->first;
        ListOfVertices result;

        dfs(result, firstVertex);
        return result;
    }

    ListOfVertices iterativeDFS(){
        auto firstVertex = AdjList.begin()->first;
        ListOfVertices result;
        std::stack<VertexName> stack;
        stack.push(firstVertex);

        while (stack.empty() == false){
            auto vertex = stack.top();
            stack.pop();
            // std::cout << "Pop " << vertex << "\n";

            if (std::find(std::begin(result), std::end(result), vertex) == std::end(result)){
                result.push_back(vertex);
            }
            for (auto it = AdjList[vertex].rbegin(); it != AdjList[vertex].rend(); ++it){
                auto [adj_vertex, _] = *it;
                if (std::find(std::begin(result), std::end(result), adj_vertex) == std::end(result)){
                    // std::cout << "Push " << adj_vertex << "\n";
                    stack.push(adj_vertex);
                }
            }
        }
        return result;
    }

    // Новая реализация для ненаправленных графов. Теперь в dfs_cycle передается
    // ешё также название вызывающей вершины для того, чтобы корректно обрабатывать 
    // случай со смежной прошлой вершиной. Без этого функция будет корректно работать только на 
    // строго направленных графах.
    enum class Color { WHITE, GREY, BLACK };
    ListOfVertices findCycleByDFS(VertexName firstVertex = {}){
        if (firstVertex == VertexName{})
            firstVertex = AdjList.begin()->first;
        
        ListOfVertices visited;
        std::map<VertexName, Color> colored;
        for (const auto &[vertex, _] : AdjList) // Красим все вершины в белые
            colored[vertex] = Color::WHITE;

        auto isFinded = dfs_cycle(visited, colored, firstVertex, "");

        // Формируем цепочку вершин, которые состоят в цикле.
        ListOfVertices VsInCycle; // Объявлена заранее для улучшения работы RVO.
        if (isFinded){
            auto firstVertexInCycle = visited.back(); // Начинаем с последней в цикле.
            VsInCycle.push_back(firstVertexInCycle);
            visited.pop_back();
            // И последовательно ищем последнюю, промежуточно запихивая в ответ промежуточные.
            while (visited.size()){
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

void dfs(ListOfVertices& visited, VertexName vertex){
    visited.push_back(vertex);
    for (const auto [adjV, _] : AdjList[vertex]){
        if (std::find(std::begin(visited),
                std::end(visited), adjV) == std::end(visited)){
            dfs(visited, adjV);
        }
    }
}

    bool dfs_cycle(ListOfVertices& visited, std::map<VertexName, Color>& colored, VertexName curV, VertexName fromVertex){
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