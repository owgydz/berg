

#ifndef BTB_RUNNER_H
#define BTB_RUNNER_H

#include <string>
#include <vector>

namespace BTB {

class Runner {
public:
    // Runs a build command, returns true if successful, false otherwise.
    bool runBuildCommand(const std::string& command);

    // Logs each build step for tracking purposes.
    void logBuildStep(const std::string& step);

    // Clean up the build artifacts.
    bool cleanBuildArtifacts();

    // Optionally, checks if a specific target exists, for example, a binary or library.
    bool targetExists(const std::string& target);

    // Optionally, runs pre-build tasks or checks before invoking the actual build command.
    bool preBuildChecks(const std::vector<std::string>& sources);

    // Executes the build process, including command execution and logging.
    bool executeBuild(const std::string& command, const std::string& target);

private:
    std::vector<std::string> buildLogs;
};

} // namespace BTB

#endif // BTB_RUNNER_H
