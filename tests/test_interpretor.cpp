#include "../bergh/interpreter.h"
#include <iostream>

int main() {
    Berg::Interpreter interpreter("build.berg");
    
    if (!interpreter.parse()) {
        std::cerr << "Failed to parse the .berg file.\n";
        return 1;
    }

    auto targets = interpreter.getTargets();
    for (const auto& [target, commands] : targets) {
        std::cout << "Target: " << target << "\n";
        for (const auto& cmd : commands) {
            std::cout << "  - " << cmd << "\n";
        }
    }

    return 0;
}
