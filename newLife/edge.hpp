#pragma once
#include <iostream>

template <typename NameT, typename WeightType>
class Edge {
    Edge(NameT from, NameT to, WeightType weight) : from(from), to(to), weight(weight) {};

    friend std::ostream& operator << (std::ostream &out, const Edge &edge) {
        out << edge.from <<  " " << edge.to << " " << edge.weight;
        return out;
    }

private:
    NameT from;
    NameT to;
    WeightType weight;
};