#include "../bergh/interpreter.h"
#include <iostream>

int main() {
    Berg::Interpreter interpreter("build.berg");
    
    // If it can't parse:
    if (!interpreter.parse()) {
        std::cerr << "Failed to parse the .berg file. Test failed.\n";
        return 1;
    }
    // Now get the targets.
    auto targets = interpreter.getTargets();
    for (const auto& [target, commands] : targets) {
        std::cout << "Target: " << target << "\n";
        for (const auto& cmd : commands) {
            std::cout << "  - " << cmd << "\n";
        }
    }

    return 0;
}
