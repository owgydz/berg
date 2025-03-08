// We already have a runner in BTB but it's fine. 
// Only for target commands

#ifndef BERG_RUNNER_H
#define BERG_RUNNER_H

#include "interpreter.h"
#include <string>

namespace Berg {

class Runner {
public:
    explicit Runner(Interpreter& interpreter);

    // Executes a specific build target
    bool executeTarget(const std::string& target);

    // Runs the default build target (first one in the file)
    bool executeDefault();

private:
    Interpreter& interpreter;
};

} // namespace Berg

#endif // BERG_RUNNER_H
