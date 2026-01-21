//
// Created by 32965 on 2026/1/21.
//

#ifndef CASEMAKER_STRING_HPP
#define CASEMAKER_STRING_HPP

#include <random>
#include <string>
#include <vector>
#include <functional>

/**
 * 随机生成合法表达式序列 如 (1+(1*1))
 * @param operands   操作数集合如 {"a", "1"}
 * @param operators  运算符集合如 {"+", "-"}
 * @param brackets   括号对集合如 {{"(", ")"}, {"[", "]"}}
 * @param n          生成表达式的最大长度
 */
template<typename T>
std::string generate_expression(
    const std::vector<std::string> &operands,
    const std::vector<std::string> &operators,
    const std::vector<std::pair<std::string, std::string>> &brackets,
    const T &n
) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    auto pick = [&](const auto &vec) -> const std::string& {
        return vec[std::uniform_int_distribution<size_t>(0, vec.size() - 1)(gen)];
    };

    size_t max_operand_len = 0;
    for(const auto& s : operands) max_operand_len = std::max(max_operand_len, s.length());

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

#endif //CASEMAKER_STRING_HPP
