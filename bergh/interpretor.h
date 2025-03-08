#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <vector>
#include <unordered_map>

namespace Berg {

class Interpreter {
public:
    Interpreter(const std::vector<std::string>& files);
    bool parse();
    bool isValid() const;
    std::unordered_map<std::string, std::vector<std::string>> getTargets() const;

private:
    std::vector<std::string> files;
    bool isValidFile(const std::string& file);
    bool parseFile(const std::string& file);
    std::string trim(const std::string& str);
    bool parseTargetLine(const std::string& line, const std::string& target);
    bool isParsed;
    std::unordered_map<std::string, std::vector<std::string>> targets;
};

} // namespace Berg

#endif // INTERPRETER_H
