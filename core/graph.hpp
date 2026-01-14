//
// Created by M1saka on 2026/1/14.
//

#ifndef CASEMAKER_GRAPH_HPP
#define CASEMAKER_GRAPH_HPP

#include <concepts>

struct Edge {
    int u, v;
};

template <std::integral T>
struct EdgeWithWeight : Edge {
    T weight;
};

#endif //CASEMAKER_GRAPH_HPP