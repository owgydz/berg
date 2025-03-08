#include "../bergh/runner.h"
#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>

namespace Berg {

Runner::Runner(Interpreter& interpreter) : interpreter(interpreter) {}

bool Runner::executeTarget(const std::string& target) {
    auto targets = interpreter.getTargets();
    if (targets.find(target) == targets.end()) {
        std::cerr << "Error: Target not found\n";
        return false;
    }

    std::cout << "Executing target: " << target << "\n";
    for (const auto& command : targets[target]) {
        if (!executeCommand(command)) {
            return false;
        }
    }
    return true;
}

bool Runner::executeTargetParallel(const std::string& target, unsigned numThreads) {
    auto targets = interpreter.getTargets();
    if (targets.find(target) == targets.end()) {
        std::cerr << "Error: Target not found\n";
        return false;
    }

    std::cout << "Executing target in parallel: " << target << "\n";
    std::vector<std::thread> threads;
    for (const auto& command : targets[target]) {
        if (threads.size() >= numThreads) {
            threads[0].join();
            threads.erase(threads.begin());
        }
        threads.push_back(std::thread(&Runner::executeCommand, this, command));
    }

    for (auto& t : threads) {
        t.join();
    }

    return true;
}

bool Runner::executeCommand(const std::string& command) {
    std::cout << "Running: " << command << "\n";
    return system(command.c_str()) == 0;
}

} // namespace Berg
