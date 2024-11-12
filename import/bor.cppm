module;

#include <array>
#include <memory>
#include <string>
#include <fstream>

export module bor;

export class Bor {
public:
    Bor() : root_(std::make_unique<Node>()) {
        std::ifstream in("token.txt");
        std::string token;
        while (in >> token) {
            Insert(token);
        }
    }

    bool Find(const std::string &str) const {
        if (str == ":") {
            return true;
        }
        Node *tec_root = root_.get();
        for (auto &elem : str) {
            if (!(elem >= 'a' && elem <= 'z')) {
                return false;
            }
            if (!tec_root->alph[elem - 'a']) {
                return false;
            }
            tec_root = tec_root->alph[elem-'a'].get();
        }
        return tec_root->is_term;
    }
    void Insert(const std::string &str) {
        if (str == ":") {
            return;
        }
        Node *tec_root = root_.get();
        for (auto &elem : str) {
            if (!tec_root->alph[elem - 'a'].get()) {
                tec_root->alph[elem - 'a'] = std::make_unique<Node>();
            }
            tec_root = tec_root->alph[elem - 'a'].get();
        }
        tec_root->is_term = true;
    }
private:
    struct Node {
        Node() : is_term(false) {}
        bool is_term;
        std::array<std::unique_ptr<Node>, 26> alph;
    };
    std::unique_ptr<Node> root_;
};
