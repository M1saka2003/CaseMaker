//
// Created by M1saka on 2026/1/14.
//

#ifndef CASEMAKER_INTEGER_HPP
#define CASEMAKER_INTEGER_HPP
#include <random>

#include "core/integer.hpp"

/**
 * 生成 [min, max] 范围内的随机整数
 */
template<std::integral T>
constexpr T get_random_integer(T min, T max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<T> dist(min, max);

    return dist(gen);
}

#endif //CASEMAKER_INTEGER_HPP
