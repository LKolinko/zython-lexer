#include "lexer.h"

int main() {
    Lexer lexer("huy.txt");
    auto result = lexer.Scan();
    for (auto& u : result) {
        u.Print();
    }    
}