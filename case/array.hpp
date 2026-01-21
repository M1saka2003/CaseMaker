//
// Created by M1saka on 2026/1/14.
//

#ifndef CASEMAKER_ARRAY_HPP
#define CASEMAKER_ARRAY_HPP

#include <random>
#include <ranges>
#include <numeric>
#include <iostream>

#include "core/integer.hpp"
/**
 * 生成一个长度为 n + 1 的 vector
 * index 0 = 0
 * index 1 ~ n = 1 ~ n 的随机排列
 */
template<std::integral T>
constexpr std::vector<T> get_random_permutation(T n) {
    std::vector<T> res(n + 1);
    std::ranges::iota(res, 0);

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::ranges::shuffle(res | std::views::drop(1), gen);
    return res;
}

/**
 * 生成一个长度为 n + 1 的 vector
 * index 0 = 0
 * index 1 ~ n = [min, max] 范围内的随机数
 */
template<std::integral T>
constexpr std::vector<T> get_random_integral_array(T n,
                                                   T min = std::numeric_limits<T>::min(),
                                                   T max = std::numeric_limits<T>::max()) {
    std::vector<T> arr(n + 1);
    std::ranges::for_each(arr | std::views::drop(1), [min,max](T &item) {
        item = get_random_integer<T>(min, max);
    });
    return arr;
}

/**
 * 生成一个长度为 n + 1 的 vector 且 index 1 ~ n 的累加和是 n 的倍数
 * index 0 = 0
 * index 1 ~ n = [min, max] 范围内的随机数
 */
template<std::integral T>
constexpr std::vector<T> get_random_integral_array_sum_multipleOfn(
    T n,
    T min = std::numeric_limits<T>::min(),
    T max = std::numeric_limits<T>::max()) {
    if (max - min + 1 < n) {
        std::cerr << "max - min + 1 must be >= n to ensure a valid solution." << std::endl;
        std::abort();
    }

    std::vector<T> arr(n + 1);

    while (true) {
        T sum = 0;

        std::ranges::for_each(arr | std::views::drop(2), [min,max,&sum](T &item) {
            item = get_random_integer<T>(min, max);
            sum += item;
        });

        T current_rem = (sum % n + n) % n;
        T target_rem = (n - current_rem) % n;

        T min_rem = (min % n + n) % n;
        T diff = (target_rem - min_rem + n) % n;
        T first_valid = min + diff;

        if (first_valid > max) continue;

        T count = (max - first_valid) / n;
        T random_step = get_random_integer<T>(0, count);

        arr[1] = first_valid + random_step * n;

        break;
    }

    for (size_t i = n; i > 1; --i) {
        auto j = get_random_integer<size_t>(1, i);
        std::swap(arr[i], arr[j]);
    }
    return arr;
}

#endif //CASEMAKER_ARRAY_HPP
