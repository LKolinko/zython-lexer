#pragma once

#include <array>
#include <memory>
#include <string>
#include <fstream>

class Bor {
public:
    Bor();
    bool find(const std::string &str) const;
    void insert(const std::string &str);
private:
    struct Node {
        Node();
        bool term;
        std::array<std::unique_ptr<Node>, 26> alph;
    };
    std::unique_ptr<Node> root_;
};
