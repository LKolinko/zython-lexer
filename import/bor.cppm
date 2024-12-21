module;

#include <map>
#include <memory>
#include <string>
#include <fstream>

export module bor;

/*!
 *  Класс словаря, хранит шаблонную дату по ключу string
 */
export template<typename T>
class Bor {
public:
    Bor() : root_(std::make_unique<Node>()) {}

    /// Создание с парсингом слов из файла (используется для ключевых слов)
    Bor(const std::string& file_name) : root_(std::make_unique<Node>()) {
        std::ifstream in(file_name);
        std::string token;
        while (in >> token) {
            Insert(token);
        }
    }

    /// поиск по бору
    bool Find(const std::string &str) const {
        Node *tec_root = root_.get();
        for (auto &elem : str) {
            if (tec_root->alph.find(elem) == tec_root->alph.end()) {
                return false;
            }
            tec_root = tec_root->alph[elem].get();
        }
        return tec_root->is_term;
    }

    /// поиск по бору с возвратом даты
    T& GetData(const std::string &str) const {
        Node *tec_root = root_.get();
        for (auto &elem : str) {
            tec_root = tec_root->alph[elem].get();
        }
        return tec_root->data_;
    }

    /// вставка в бор с датой
    void Insert(const std::string &str, T data) {
        Node *tec_root = root_.get();
        for (auto &elem : str) {
            if (tec_root->alph.find(elem) == tec_root->alph.end()) {
                tec_root->alph[elem] = std::make_unique<Node>();
            }
            tec_root = tec_root->alph[elem].get();
        }
        tec_root->is_term = true;
        tec_root->data_ = data;
    }

    /// вставка в бор без даты
    void Insert(const std::string &str) {
        Node *tec_root = root_.get();
        for (auto &elem : str) {
            if (tec_root->alph.find(elem) == tec_root->alph.end()) {
                tec_root->alph[elem] = std::make_unique<Node>();
            }
            tec_root = tec_root->alph[elem].get();
        }
        tec_root->is_term = true;
    }

private:
    struct Node {
        Node() : is_term(false) {}
        Node(T data) : is_term(false), data_(std::move(data)) {}
        bool is_term;
        T data_;
        std::map<char, std::unique_ptr<Node>> alph;
    };
    std::unique_ptr<Node> root_;
};
