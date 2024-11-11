#pragma once

#include "lexem.h"
#include "Bor.h"

#include <vector>

class Lexer {
public:
    Lexer() = default;
    Lexer(const std::string& file_name);
    std::vector<lexem> Scan();
private:
    void id_();
    void string_literal_();
    void number_literal_();
    void float_literal_(std::string& data);
    void operator_();
    void comment_();

    void get_char();

    bool end_of_file_ = false;
    char tec_char_{};
    std::ifstream in_;
    Bor bor_;
    std::vector<lexem> data_;

    static bool is_operator_(char c);
    static bool is_letter_(char c);
    static bool is_number_(char c);

    static bool is_letter_or_number_(char c);
    static bool is_separator_(char c);
};
