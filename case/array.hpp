//
// Created by M1saka on 2026/1/14.
//

#ifndef CASEMAKER_ARRAY_HPP
#define CASEMAKER_ARRAY_HPP

#include <random>
#include <ranges>
#include <numeric>

/**
 * 生成一个长度为 n + 1 的 vector
 * index 0 = 0
 * index 1 ~ n = 1 ~ n 的随机排列
 */
template<std::integral T>
std::vector<T> get_random_permutation(T n) {
    std::vector<T> res(n + 1);
    std::ranges::iota(res, 0);

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::ranges::shuffle(res | std::views::drop(1), gen);
    return res;
}

template<std::integral T>
constexpr std::vector<T> get_random_integral_array(T n,
                                      T min = std::numeric_limits<T>::min(),
                                      T max = std::numeric_limits<T>::max()) {
    std::vector<T> arr(n + 1);
    std::ranges::for_each(arr, [min,max](T &item) {
        item = get_random_integer<T>(min, max);
    });
    return arr;
}
#endif //CASEMAKER_ARRAY_HPP
