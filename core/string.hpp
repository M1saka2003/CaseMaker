//
// Created by 32965 on 2026/1/21.
//

#ifndef CASEMAKER_CORE_STRING_HPP
#define CASEMAKER_CORE_STRING_HPP

#include <string>

struct charset {
    inline static std::string digits = "0123456789";
    inline static std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    inline static std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
};

#endif //CASEMAKER_CORE_STRING_HPP
