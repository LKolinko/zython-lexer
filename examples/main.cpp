import lexer;
#include <vector>

int main() {
    Lexer lexer("../../../huy.txt");
    std::vector<lexem> result = lexer.Scan();
    for (auto& u : result) {
        u.Print();
    }    
}
