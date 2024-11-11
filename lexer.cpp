#include "lexer.h"

Lexer::Lexer(const std::string& file_name) {
    in_.open(file_name);
}

void Lexer::get_char() {
    if (!in_.get(tec_char_)) {
        end_of_file_ = true;
    }
}

bool Lexer::is_operator_(char c) {
    return c == '+' || c == '-' || c == '*'
        || c == '/' || c == '%' || c == '>' 
        || c == '<' || c == '=' || c == '!'
        || c == '(' || c == ')' || c == '.'
        || c == '[' || c == ']' || c == ',';
}

bool Lexer::is_letter_(char c) {
    return (c >= 'a' && c <= 'z') 
        || (c >= 'A' && c <= 'Z');
}

bool Lexer::is_number_(char c) {
    return c >= '0' && c <= '9';
}

bool Lexer::is_letter_or_number_(char c) {
    return is_letter_(c) || is_number_(c);
}

bool Lexer::is_separator_(char c) {
    return c == ' ' || c == EOF;
}

void Lexer::id_() {
    std::string name;
    name.push_back(tec_char_);
    get_char();
    while (is_letter_or_number_(tec_char_) && !end_of_file_) {
        name.push_back(tec_char_);
        get_char();
    }
    if (bor_.find(name)) {
        data_.emplace_back(lex::KEYWORD, name);
    } else {
        data_.emplace_back(lex::ID, name);
    }
}

void Lexer::string_literal_() {
    std::string data;
    get_char();
    while (tec_char_ != '"') {
        data.push_back(tec_char_);
        get_char();
    }
    get_char();
    data_.emplace_back(lex::STRING_LITER, data);
}

void Lexer::float_literal_(std::string& data) {
    data.push_back(tec_char_);
    get_char();
    while (is_letter_or_number_(tec_char_) && !end_of_file_) {
        data.push_back(tec_char_);
        get_char();
    }
    data_.emplace_back(lex::FLOAT_LITER, data);
}

void Lexer::number_literal_() {
    std::string data;
    while (is_letter_or_number_(tec_char_) && !end_of_file_) {
        data.push_back(tec_char_);
        get_char();
    }
    if (tec_char_ == '.') {
        float_literal_(data);
    } else {
        data_.emplace_back(lex::INT_LITER, data);
    }
}

void Lexer::comment_() {
    while (tec_char_ != '\n' && tec_char_ != EOF && !end_of_file_) {
        get_char();
    }
}

void Lexer::operator_() {
    std::string data;
    data.push_back(tec_char_);
    if (tec_char_ == '+' && in_.peek() == '+') {
        get_char();
        data.push_back(tec_char_);
    }
    if (tec_char_ == '-' && in_.peek() == '-') {
        get_char();
        data.push_back(tec_char_);
    }
    if (tec_char_ == '*' && in_.peek() == '*') {
        get_char();
        data.push_back(tec_char_);
    }
    if (tec_char_ == '=' && in_.peek() == '=') {
        get_char();
        data.push_back(tec_char_);
    }
    if (tec_char_ == '/' && in_.peek() == '/') {
        get_char();
        comment_();
        return;
    }
    get_char();
    data_.emplace_back(lex::OPERATOR, data);
}

std::vector<lexem> Lexer::Scan() {
    get_char();
    while (!end_of_file_) {
        if (is_letter_(tec_char_) || tec_char_ == ':') {
            id_();
        } else if (is_number_(tec_char_)) {
            number_literal_();
        } else if (is_operator_(tec_char_)) {
            operator_();
        } else if (tec_char_ == '"') {
            string_literal_();
        } else if (is_separator_(tec_char_)) {
            std::string data;
            while (tec_char_ == ' ' && !end_of_file_) {
                data.push_back(tec_char_);
                get_char();
            }
            data_.emplace_back(lex::SEPARATOR, data);
            if (is_separator_(tec_char_)) {
                get_char();
            }
        } else if (tec_char_ == '\n') {
            std::string data = "\n";
            data_.emplace_back(lex::ENDLINE, data);
            get_char();
            while (tec_char_ == ' ' && !end_of_file_) {
                get_char();
            }
        } else {
            std::string ans = "unresolved external character: ";
            ans.push_back(tec_char_);
            throw std::runtime_error(ans);
        }
    }
    return data_;
}
