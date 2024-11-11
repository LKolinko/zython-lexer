#pragma once

#include <string>
#include <iostream>

namespace lex {
    enum type {STRING_LITER, INT_LITER, FLOAT_LITER, ID, KEYWORD, SEPARATOR, ENDLINE, OPERATOR};
}

class lexem {
public:
    lexem(lex::type type, const std::string& data) : type_(type), data_(data) {}
    lex::type type_;
    std::string data_;
    void Print() {
        std::cout << type_ << ' ' << data_  << '\n';
    }
};