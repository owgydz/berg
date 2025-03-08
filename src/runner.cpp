// We already have a runner in BTB but it is fine :)

#include "../bergh/runner.h"
#include <iostream>
#include <cstdlib>

namespace Berg {

Runner::Runner(Interpreter& interpreter) : interpreter(interpreter) {}

bool Runner::executeTarget(const std::string& target) {
    if (!interpreter.isValid()) {
        std::cerr << "Error: Interpreter failed to parse the .berg file.\n";
        return false;
    }

    auto targets = interpreter.getTargets();
    if (targets.find(target) == targets.end()) {
        std::cerr << "Error: Target '" << target << "' not found in .berg file.\n";
        return false;
    }

    std::cout << "Executing target: " << target << "\n";
    for (const auto& command : targets[target]) {
        std::cout << "Running: " << command << "\n";
        if (std::system(command.c_str()) != 0) {
            std::cerr << "Error: Command failed: " << command << "\n";
            return false;
        }
    }

    return true;
}

} // namespace Berg
