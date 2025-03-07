#ifndef BTB_INTERPRETER_H
#define BTB_INTERPRETER_H

#include <vector>
#include <string>

namespace BTB {

class Interpreter {
public:
    bool parseFile(const std::string& filePath);
    std::vector<std::string> getSources() const;
    std::string getBuildCommand() const;
    std::vector<std::string> getTargets() const;

private:
    std::vector<std::string> sources;
    std::string buildCommand;
    std::vector<std::string> targets;
};

} // namespace BTB

#endif // BTB_INTERPRETER_H
