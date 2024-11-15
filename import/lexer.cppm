module;

#include <fstream>
#include <vector>

export module lexer;

export import lexem;
import bor;


export class Lexer {
public:
    Lexer() = default;

    Lexer(const std::string& file_name, const std::string& token_file_name) : bor_(token_file_name) {
        in_.open(file_name);
    }

    std::vector<Lexem> Scan() {
        GetChar();
        while (!end_of_file_) {
            if (IsLetter(tec_char_) || tec_char_ == ':') {
                GetId();
            } else if (IsNumber(tec_char_)) {
                GetNumberLiteral();
            } else if (IsOperator(tec_char_)) {
                GetOperator();
            } else if (tec_char_ == '"') {
                GetStringLiteral();
            } else if (IsSeparator(tec_char_)) {
                std::string data;
                while (tec_char_ == ' ' && !end_of_file_) {
                    data.push_back(tec_char_);
                    GetChar();
                }
                data_.emplace_back(Lex::kSeparator, data, line_, position_ - static_cast<int>(data.size()));
                if (IsSeparator(tec_char_)) {
                    GetChar();
                }
            } else if (tec_char_ == '#') {
                GetComment();
            } else if (tec_char_ == '\n') {
                std::string data = "\n";
                data_.emplace_back(Lex::kEndLine, data, line_, position_ - static_cast<int>(data.size()));
                GetChar();
                position_ = 1;
                ++line_;
            } else {
                std::string ans = "unresolved external character: ";
                ans.push_back(tec_char_);
                throw std::runtime_error(ans);
            }
        }
        return data_;
    }

private:

    bool end_of_file_ = false;
    uint64_t line_ = 1, position_ = 1;
    char tec_char_{};
    std::ifstream in_;
    Bor<bool> bor_;
    std::vector<Lexem> data_;

    void GetId() {
        std::string name;
        name.push_back(tec_char_);
        GetChar();
        while (IsLetterOrNumber(tec_char_) && !end_of_file_) {
            name.push_back(tec_char_);
            GetChar();
        }
        if (bor_.Find(name)) {
            data_.emplace_back(Lex::kKeyworkd, name, line_, position_ - static_cast<int>(name.size()));
        } else {
            data_.emplace_back(Lex::kId, name, line_, position_ - static_cast<int>(name.size()));
        }
    }

    void GetStringLiteral() {
        std::string data;
        GetChar();
        while (tec_char_ != '"') {
            data.push_back(tec_char_);
            GetChar();
        }
        GetChar();
        data_.emplace_back(Lex::kStringLiter, data, line_, position_ - static_cast<int>(data.size()));
    }

    void GetNumberLiteral() {
        std::string data;
        while (IsLetterOrNumber(tec_char_) && !end_of_file_) {
            data.push_back(tec_char_);
            GetChar();
        }
        if (tec_char_ == '.') {
            GetFloatLiteral(data);
        } else {
            data_.emplace_back(Lex::kIntLiter, data, line_, position_ - static_cast<int>(data.size()));
        }
    }

    void GetFloatLiteral(std::string& data) {
        data.push_back(tec_char_);
        GetChar();
        while (IsLetterOrNumber(tec_char_) && !end_of_file_) {
            data.push_back(tec_char_);
            GetChar();
        }
        data_.emplace_back(Lex::kFloatLiter, data, line_, position_ - static_cast<int>(data.size()));
    }

    void GetOperator() {
        std::string data;
        data.push_back(tec_char_);
        if (tec_char_ == '*' && in_.peek() == '*') {
            GetChar();
            data.push_back(tec_char_);
        }
        if (tec_char_ == '=' && in_.peek() == '=') {
            GetChar();
            data.push_back(tec_char_);
        }
        if (tec_char_ == '/' && in_.peek() == '/') {
            GetChar();
            data.push_back(tec_char_);
        }
        GetChar();
        data_.emplace_back(Lex::kOperator, data, line_, position_ - static_cast<int>(data.size()));
    }

    void GetComment() {
        while (tec_char_ != '\n' && tec_char_ != std::ifstream::traits_type::eof() && !end_of_file_) {
            GetChar();
        }
    }

    void GetChar()  {
        if (!in_.get(tec_char_)) {
            end_of_file_ = true;
        }
        ++position_;
    }

    static bool IsOperator(char c) {
        return c == '+' || c == '-' || c == '*'
            || c == '/' || c == '%' || c == '>'
            || c == '<' || c == '=' || c == '!'
            || c == '(' || c == ')' || c == '.'
            || c == '[' || c == ']' || c == ',';
    }

    static bool IsLetter(char c) {
        return (c >= 'a' && c <= 'z')
            || (c >= 'A' && c <= 'Z');
    }

    static bool IsNumber(char c) {
        return c >= '0' && c <= '9';
    }

    static bool IsLetterOrNumber(char c) {
        return IsLetter(c) || IsNumber(c);
    }

    static bool IsSeparator(char c) {
        return c == ' ' || c == std::ifstream::traits_type::eof();
    }
};
