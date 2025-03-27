#include "../btbh/cli.h"
#include <iostream>
#include <cstdlib>
#include "../btbh/runner.h"   
#include "../btbh/depend.h"
#include "../btbh/parser.h"  
#include "../btbh/sandbox.h"

namespace BTB {
namespace CLI {

void showHelp() {
    std::cout << "Usage: btb <command>\n"
              << "Commands:\n"
              << "  build    - Build the project\n"
              << "  help     - Show this help message\n"
              << "  status   - Check status of build\n"
              << "  clean    - Clean build artifacts\n"
              << "  ver  - Show version\n"
              << "Use 'btb <command> help' for more details on each command.\n";
}

void showCommandHelp(const std::string& command) {
    if (command == "build") {
        std::cout << "build: Builds the project from the .berg file.\n";
        std::cout << "Usage: btb build\n";
    } else if (command == "help") {
        std::cout << "help: Shows help information.\n";
        std::cout << "Usage: btb help\n";
    } else if (command == "status") {
        std::cout << "status: Checks the status of the build.\n";
        std::cout << "Usage: btb status\n";
    } else if (command == "clean") {
        std::cout << "clean: Cleans the build artifacts.\n";
        std::cout << "Usage: btb clean\n";
    } else if (command == "ver") {
        std::cout << "ver: Shows the version of the tool.\n";
        std::cout << "Usage: btb ver\n";
    } else {
        std::cout << "Unknown command: " << command << "\n";
    }
}

void build() {
    std::cout << "Building the project...\n";
    Runner runner;
    BergParser parser;
    if (!parser.parseFile("build.berg")) {
        std::cerr << "Error: Could not read build.berg" << std::endl;
        return;
    }

    std::string buildCommand = parser.getValue("buildCommand");
    if (buildCommand.empty()) {
        std::cerr << "Error: No build command specified in build.berg" << std::endl;
        return;
    }

    if (!isCommandSafe(buildCommand)) {
        std::cerr << "Error: Unsafe build command detected. Aborting build: " << buildCommand << std::endl;
        return;
    }

    if (runner.runBuildCommand(buildCommand)) {
        std::cout << "The build was completed successfully. It should now be an executable.\n";
    } else {
        std::cerr << "ERR! Build failed\n";
    }
}

void status() {
    std::cout << "Checking build status...\n";

    // Parse the build.berg file to get sources and target
    BergParser parser;
    if (!parser.parseFile("build.berg")) {
        std::cerr << "Error: Could not read build.berg" << std::endl;
        return;
    }

    std::string target = parser.getValue("target");
    std::vector<std::string> sources = parser.getSources();

    // Integrate with DependencyManager to check if the project is up-to-date
    DependencyManager depManager;
    if (depManager.isBuildUpToDate(sources, target)) {
        std::cout << "Build is up-to-date.\n";
    } else {
        std::cout << "Build is outdated, needs updating.\n";
    }
}

void clean() {
    std::cout << "Cleaning build artifacts...\n";

    // Trigger the clean process via Runner
    Runner runner;
    if (runner.cleanBuildArtifacts()) {
        std::cout << "Build artifacts cleaned successfully.\n";
    } else {
        std::cerr << "Failed to clean build artifacts.\n";
    }
}

void version() {
    std::cout << "Build the Berg (BTB) version v0.6.12137.2\n";
    std::cout << "Part of the Berg project.\n";
    std::cout << "Meta-build system for .berg Berg files\n";
    std::cout << "This project was led by Owen Gaydosz and the Bluegill Studios Berg team.\n";
    std::cout << "For more information, visit the link https://github.com/owgydz/berg for more information on the Berg project.\n";
}

} // namespace CLI
} // namespace BTB
