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

/*!
 * Класс лексемы. Содержит тип, позицию и дату
 */
export class Lexem {
public:
    Lexem(Lex type, std::string data, int line, int index) : type_(type), data_(std::move(data)),
    pos_(line, index) {}

    void Print() {
        std::cout << static_cast<std::underlying_type_t<Lex>>(type_) << ' ' << (data_ == "\n" ? "Endl" : data_) << '\n';
    }

    /// get для даты
    std::string GetData() const {
        return data_;
    }

    /// get для типа
    Lex GetType() const {
        return type_;
    }

    /// get для позиции
    auto GetPosition() const {
        return pos_;
    }

private:
    Lex type_;
    std::string data_;
    struct {
        uint64_t line, index;
    } pos_;
};
