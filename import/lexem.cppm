module;

#include <string>
#include <iostream>

export module lexem;

export namespace lex {
    enum type {
        STRING_LITER,
        INT_LITER,
        FLOAT_LITER,
        ID,
        KEYWORD,
        SEPARATOR,
        ENDLINE,
        OPERATOR
    };
} // namespace lex

export class lexem {
public:
    lexem(lex::type type, const std::string& data) : type_(type), data_(data) {}
    lex::type type_;
    std::string data_;
    void Print() {
        std::cout << type_ << ' ' << data_  << '\n';
    }
};
