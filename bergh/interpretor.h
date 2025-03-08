
#ifndef BERG_INTERPRETER_H
#define BERG_INTERPRETER_H

#include <string>
#include <vector>
#include <unordered_map>

namespace Berg {

class Interpreter {
public:
    explicit Interpreter(const std::string& filename);

    bool parse();
    std::unordered_map<std::string, std::vector<std::string>> getTargets() const;
    bool isValid() const;

private:
    std::string filename;
    std::unordered_map<std::string, std::vector<std::string>> targets;
    bool valid;

    // Helper function to trim whitespace
    std::string trim(const std::string& str);
};

} // namespace Berg

#endif // BERG_INTERPRETER_H
