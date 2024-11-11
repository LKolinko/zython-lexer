#include "Bor.h"

Bor::Bor() : root_(std::make_unique<Node>()) {
    std::ifstream in("token.txt");
    std::string token;
    while (in >> token) {
        insert(token);
    }
}

Bor::Node::Node() : term(false) {}

bool Bor::find(const std::string &str) const {
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
    return tec_root->term;
}

void Bor::insert(const std::string &str) {
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
    tec_root->term = true;
}
