#include "meta.hpp"

#include "EdgesList.hpp"
#include "AdjacencyListImp.hpp"
#include "AdjacencyMatrixImp.hpp"
// Задание - сделать класс граф с использованием паттерна мост (с двумя реализациями).
// Затем какой-нибудь порождающий паттерн.

void checkBFS();
void checkDFS();

int main(){

    // std::stringstream stream{"A B\nA C\nB D\nC F\nD E\nD F\nE C\n"};
    // std::stringstream stream{"A B\nB C\nB D\nD E\nE G\nG D\n"};
    // std::stringstream stream{"A B\nA C\nB D\nC F\nD E\nD F\nE C\nF A\nE B\n"};
    std::stringstream stream{"A B\nB C\nC D\nB D\nA C\n"};

    // std::string inputLine;
    // std::stringstream stream;
    // while (std::getline(std::cin, inputLine)){
    //     stream << inputLine << "\n";
    // }

    // EdgesList obj(stream);
    // std::cout << obj;
    // std::cout << std::endl;

    // AdjacencyListImp graf(obj);
    // graf.makeUndirected();
    // std::cout << graf;

    // checkBFS();
    checkDFS();
    return 0;

    // auto result_1 = graf.recursiveDFS();
    // std::cout << "Rec DFS: ";
    // for (const auto &elem : result_1)
    //     std::cout << elem << " ";
    // std::cout << std::endl;


    // auto result_2 = graf.iterativeDFS({"S"});
    // std::cout << "It  DFS: ";
    // for (const auto &elem : result_2)
    //     std::cout << elem << " ";
    // std::cout << std::endl;

    // auto visited = graf.findCycleByDFS();
    // if (!visited.empty()){
    //     std::cout << "Cycle:   ";
    //     for (const auto &elem : visited)
    //         std::cout << elem << " ";
    //     std::cout << std::endl;
    // }
    // else 
    //     std::cout << "Cycle is not found!" << std::endl;
}


void checkDFS() {
    std::stringstream stream{"0 1\n1 5\n5 3\n5 6\n6 2\n6 4\n4 7\n"};

    EdgesList obj(stream);
    AdjacencyListImp graf(obj);
    graf.makeUndirected();
    graf.printUnweighted(std::cout);

    Vertex start = {"5"};
    auto dfs_result = graf.recursiveDFS(start);
    std::cout << "DFS from " << start << ": " << "\n";
    for (const auto &elem : dfs_result)
        std::cout << elem << " ";
    std::cout << std::endl;
}

void checkBFS() {
    std::stringstream stream{"0 1\n1 2\n2 4\n4 0\n1 3\n1 5\n1 6\n5 7\n3 7\n"};

    EdgesList obj(stream);
    AdjacencyListImp graf(obj);
    graf.makeUndirected();
    graf.printUnweighted(std::cout);

    Vertex start = {"2"};
    auto bfs_result = graf.BFS(start);
    std::cout << "BFS from " << start << ": " << "\n";
    for (const auto &elem : bfs_result)
        std::cout << elem << " ";
    std::cout << std::endl;
}
