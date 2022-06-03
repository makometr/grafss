#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cassert>

#include <algorithm>
#include <iterator>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <map>
#include <list>
#include <stack>

#define assertm(exp, msg) assert(((void)msg, exp))

using VertexID = int;

using Vertex = std::string;
using EdgeWeight = int;
using Edge = std::tuple<Vertex, Vertex, EdgeWeight>;

using SemiEdge = std::pair<Vertex, EdgeWeight>;
using VerticesVector = std::vector<Vertex>;
using EdgesVector = std::vector<Edge>;

