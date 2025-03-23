#include "../btbh/depend.h"
#include <iostream>
#include <sys/stat.h>

namespace BTB {

bool DependencyManager::resolveDependencies(const std::vector<std::string>& sources) {
    for (const auto& source : sources) {
        std::cout << "Checking dependency for source: " << source << std::endl;
    }
    return true;
}

bool DependencyManager::needsRebuild(const std::vector<std::string>& sources, const std::string& target) {
    time_t targetTime = getFileModificationTime(target);
    for (const auto& source : sources) {
        time_t sourceTime = getFileModificationTime(source);
        if (sourceTime > targetTime) {
            return true;  // Source file is newer than the target
        }
    }
    return false;
}

time_t DependencyManager::getFileModificationTime(const std::string& filePath) {
    struct stat fileStat;
    if (stat(filePath.c_str(), &fileStat) != 0) {
        std::cerr << "Error: Could not get modification time for file " << filePath << std::endl;
        return 0;
    }
    return fileStat.st_mtime;
}

bool DependencyManager::isBuildUpToDate(const std::vector<std::string>& sources, const std::string& target) {
    struct stat targetStat;
    if (stat(target.c_str(), &targetStat) != 0) {
        std::cerr << "Error: Could not stat target file: " << target << std::endl;
        return false;  // If the target doesn't exist, we need to rebuild
    }

    time_t targetTime = targetStat.st_mtime;

    for (const auto& source : sources) {
        struct stat sourceStat;
        if (stat(source.c_str(), &sourceStat) != 0) {
            std::cerr << "Error: Could not stat source file: " << source << std::endl;
            return false;  // If any source is missing, rebuild is required
        }

        time_t sourceTime = sourceStat.st_mtime;
        if (sourceTime > targetTime) {
            return false;  // If any source is newer than the target, rebuild is required
        }
    }

    return true;  // No sources are newer, so the build is up to date
}

} // namespace BTB
