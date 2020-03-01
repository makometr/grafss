#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cassert>

#include <algorithm>
#include <iterator>
#include <vector>
#include <tuple>
#include <map>
#include <list>
#include <stack>

#define assertm(exp, msg) assert(((void)msg, exp))

using VertexName = std::string;
using VertexID = int;
using EdgeWeight = int;
using Edge = std::tuple<VertexName, VertexName, EdgeWeight>;
using SemiEdge = std::pair<VertexName, EdgeWeight>;
using ListOfVertices = std::vector<VertexName>;