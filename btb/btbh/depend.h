#ifndef BTB_DEPENDENCY_H
#define BTB_DEPENDENCY_H

#include <vector>
#include <string>
#include <ctime>

namespace BTB {

class DependencyManager {
public:
    bool resolveDependencies(const std::vector<std::string>& sources);
    bool needsRebuild(const std::vector<std::string>& sources, const std::string& target);
    bool isBuildUpToDate(const std::vector<std::string>& sources, const std::string& target);
private:
    time_t getFileModificationTime(const std::string& filePath);
};

} // namespace BTB

#endif // BTB_DEPENDENCY_H
