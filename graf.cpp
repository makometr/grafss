#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <tuple>
#include <memory>
#include <list>
#include <map>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "EdgesList.hpp"
#include "AdjacencyListImp.hpp"
#include "AdjacencyMatrixImp.hpp"
// Задание - сделать класс граф с использованием паттерна мост (с двумя реализациями).
// Затем какой-нибудь порождающий паттерн.

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

    EdgesList obj(stream);
    std::cout << obj;

    std::cout << std::endl;

    AdjacencyListImp graf(obj);
    graf.makeUndirected();
    std::cout << graf;



    auto result_1 = graf.recursiveDFS();
    std::cout << "Rec DFS: ";
    for (const auto &elem : result_1)
        std::cout << elem << " ";
    std::cout << std::endl;


    auto result_2 = graf.iterativeDFS();
    std::cout << "It  DFS: ";
    for (const auto &elem : result_2)
        std::cout << elem << " ";
    std::cout << std::endl;

    auto visited = graf.findCycleByDFS();
    if (!visited.empty()){
        std::cout << "Cycle:   ";
        for (const auto &elem : visited)
            std::cout << elem << " ";
        std::cout << std::endl;
    }
    else 
        std::cout << "Cycle is not found!" << std::endl;
}
