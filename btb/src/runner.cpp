#include "../btbh/runner.h"
#include <iostream>
#include <cstdlib>

namespace BTB {

bool Runner::runBuildCommand(const std::string& command) {
    logBuildStep("Running build command: " + command);
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Error: Build failed with command: " << command << std::endl;
        return false;
    }
    logBuildStep("Build completed successfully.");
    return true;
}

void Runner::logBuildStep(const std::string& step) {
    std::cout << "[BTB Build Log] " << step << std::endl;
}

bool Runner::executeBuild(const std::string& command, const std::string& target) {
    logBuildStep("Starting build process for target: " + target);
    
    if (!preBuildChecks({})) {
        std::cerr << "Pre-build checks failed." << std::endl;
        return false;
    }

    if (runBuildCommand(command)) {
        logBuildStep("Build for " + target + " completed successfully.");
        return true;
    } else {
        logBuildStep("Build for " + target + " failed.");
        return false;
    }
}

} // namespace BTB
