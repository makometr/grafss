#pragma once
#include <iostream>

template <class T>
static inline void hash_combine(std::size_t & seed, const T & v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename T> struct vertex_hasher;

template <typename NameT>
class Vertex {
public:
    Vertex() = default;
    Vertex(NameT name) : name(name) {};
    Vertex(const Vertex<NameT> &vertex) = default;

    static std::size_t hasher(const Vertex<NameT> &vertex);

    // static size_t hasher(const Vertex<NameT> &vertex) const noexcept {
    //     std::size_t seed = 0;
    //     hash_combine(seed, vertex.name);
    //     return seed;
    // }

    friend std::ostream& operator << (std::ostream &out, const Vertex &vertex) {
        out << vertex.name;
        return out;
    }
    friend std::istream& operator >> (std::istream &in, Vertex &vertex) {
        in >> vertex.name;
        return in;
    }
    bool operator <(const Vertex& rhs) const {
        return name < rhs.name;
    }
    bool operator==(const Vertex& rhs) const {
        return name == rhs.name;
    }
    friend vertex_hasher<NameT>;

private:
    NameT name;
};

template <typename T>
std::size_t Vertex<T>::hasher(const Vertex<T> &vertex) {
    std::size_t seed = 0;
    hash_combine(seed, vertex.name);
    return seed;
}

template <typename T>
struct vertex_hasher {
    std::size_t operator() (const Vertex<T> &vertex) const {
        std::size_t seed = 0;
        hash_combine(seed, vertex.name);
        return seed;
    }
};
