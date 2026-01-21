//
// Created by 32965 on 2026/1/21.
//

#ifndef CASEMAKER_STRING_HPP
#define CASEMAKER_STRING_HPP

#include <random>
#include <string>
#include <vector>
#include <functional>

#include "core/string.hpp"

/**
 * 随机生成合法表达式序列 如 (1+(1*1))
 * @param operands   操作数集合如 {"a", "1"}
 * @param operators  运算符集合如 {"+", "-"}
 * @param brackets   括号对集合如 {{"(", ")"}, {"[", "]"}}
 * @param n          生成表达式的最大长度
 */
template<std::integral T>
constexpr std::string generate_expression(
    const std::vector<std::string> &operands,
    const std::vector<std::string> &operators,
    const std::vector<std::pair<std::string, std::string> > &brackets,
    const T &n
) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    auto pick = [&](const auto &vec) -> const std::string & {
        return vec[std::uniform_int_distribution<size_t>(0, vec.size() - 1)(gen)];
    };

    size_t max_operand_len = 0;
    for (const auto &s: operands) max_operand_len = std::max(max_operand_len, s.length());

    std::function<std::string(size_t)> solve = [&](size_t target_len) -> std::string {
        if (target_len <= max_operand_len + 1) {
            return pick(operands);
        }

        std::vector<int> actions;
        if (!brackets.empty()) actions.push_back(1);
        actions.push_back(2);

        int action = actions[std::uniform_int_distribution<size_t>(0, actions.size() - 1)(gen)];

        if (action == 1) {
            const auto &[fst, snd] = brackets[std::uniform_int_distribution<size_t>(0, brackets.size() - 1)(gen)];
            size_t wrap_len = fst.length() + snd.length();

            if (target_len > wrap_len + 1) {
                return fst + solve(target_len - wrap_len) + snd;
            }
            action = 2;
        }

        if (action == 2) {
            const std::string &op = pick(operators);
            if (target_len > op.length() + 2) {
                size_t avail = target_len - op.length();

                std::uniform_int_distribution<size_t> split_dist(1, avail - 1);
                size_t target_left = split_dist(gen);
                size_t target_right = avail - target_left;

                std::string left = solve(target_left);
                std::string right = solve(target_right);

                return left + op + right;
            }
        }

        return pick(operands);
    };

    return solve(n);
}

/**
 * 生成一个长度接近 n 的随机字符串，且包含 subs 中的若干子串
 * @param charset 可选字符集
 * @param subs 需要包含的子串集合
 * @param n 目标字符串长度
 * @return 生成的字符串
 */
template<std::integral T>
constexpr std::string generate_random_mixed_string(
    const std::string &charset,
    const std::vector<std::string> &subs,
    T n
) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<size_t> char_dist(0, charset.size() - 1);

    auto gen_random = [&](const size_t len) {
        std::string s;
        for (size_t i = 0; i < len; ++i) s += charset[char_dist(gen)];
        return s;
    };

    size_t initial_len = n / 2;
    std::string result = gen_random(initial_len);

    size_t min_sub_len = n + 1;
    for (const auto &s: subs) if (s.length() < min_sub_len) min_sub_len = s.length();

    if (!subs.empty() && min_sub_len <= n) {
        std::uniform_int_distribution<size_t> sub_dist(0, subs.size() - 1);
        int attempts = 0;

        while (result.length() + min_sub_len <= n && attempts < 50) {
            const std::string &target = subs[sub_dist(gen)];

            if (result.length() + target.length() <= n) {
                std::uniform_int_distribution<size_t> pos_dist(0, result.length());
                result.insert(pos_dist(gen), target);
                attempts = 0;
            } else {
                attempts++;
            }
        }
    }

    if (result.length() < n) {
        result += gen_random(n - result.length());
    }

    return result;
}
#endif //CASEMAKER_STRING_HPP
