//
// Created by M1saka on 2026/1/14.
//

#ifndef CASEMAKER_TREE_HPP
#define CASEMAKER_TREE_HPP

#include <algorithm>

#include "core/graph.hpp"
#include "core/integer.hpp"

/**
 * 生成一个有 n 个节点的随机树
 * 返回值为边的列表
 * 采用随机父亲算法生成的树倾向于矮胖，即更接近星形
 */
template<std::integral T>
constexpr std::vector<Edge> get_random_tree(T n) {
    if (n <= 1) {
        return {};
    }
    std::vector<Edge> edges;

    for (int i = 2; i <= n; i++) {
        T u = i, v = get_random_integer(1, i - 1);
        if (get_random_integer(0, 1)) {
            std::swap(u, v);
        }
        edges.emplace_back(u, v);
    }

    std::ranges::shuffle(edges, std::mt19937(std::random_device()()));
    return edges;
}


#endif //CASEMAKER_TREE_HPP
