// We already have a runner in BTB but it's fine. 
// Only for target commands

#ifndef RUNNER_H
#define RUNNER_H

#include "interpretor.h"
#include <string>
#include <vector>
#include <thread>

namespace Berg {

class Runner {
public:
    explicit Runner(Interpreter& interpreter);

    // Executes a specific build target
    bool executeTarget(const std::string& target);

    // Runs the default build target (first one in the file)
    bool executeDefault();

    // Executes a specific build target in parallel
    bool executeTargetParallel(const std::string& target, unsigned numThreads);

private:
    // Executes a specific command
    bool executeCommand(const std::string& command);

    Interpreter& interpreter;
    std::vector<std::string> buildLogs;
};

} // namespace Berg

#endif // RUNNER_H
