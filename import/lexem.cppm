module;

#include <string>
#include <iostream>

export module lexem;

export enum class Lex {
    kStringLiter,
    kIntLiter,
    kFloatLiter,
    kId,
    kKeyworkd,
    kSeparator,
    kEndLine,
    kOperator
};

export class Lexem {
public:
    Lexem(Lex type, std::string data) : type_(type), data_(std::move(data)) {}

    void Print() {
        std::cout << static_cast<std::underlying_type_t<Lex>>(type_) << ' ' << data_  << '\n';
    }
private:
    Lex type_;
    std::string data_;
};
