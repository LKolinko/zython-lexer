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
    Lexem(Lex type, std::string data, int line, int index) : type_(type), data_(std::move(data)),
    line_(line), index_(index) {}

    void Print() {
        std::cout << static_cast<std::underlying_type_t<Lex>>(type_) << ' ' << line_ << ' ' << index_ << ' ' << data_  << '\n';
    }
    
    std::string GetData() const {
        return data_;
    }
    
    Lex GetType() const {
        return type_;
    }

    std::pair<int32_t, int32_t> GetPosition() const {
        return std::make_pair(line_, index_);
    }

private:
    Lex type_;
    std::string data_;
    int32_t line_, index_;
};
