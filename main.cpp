#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

int main()
{
    std::unordered_map<std::string, std::list<int>> testmap;

    std::list<int> templist;

    templist.push_front( 10 );
    templist.push_front( 5 );

    testmap["First"] = templist;

    for ( const auto &item : testmap["First"] ) std::cout << item << ' ';
    std::cout << '\n';

    testmap["First"].push_front( 0 );

    for ( const auto &item : testmap["First"] ) std::cout << item << ' ';
    std::cout << '\n';
}