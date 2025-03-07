#include "../bergh/fs.h"
#include <sys/stat.h>
#include <stdexcept>

bool fileExists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

time_t getFileModificationTime(const std::string& filename) {
    struct stat buffer;
    if (stat(filename.c_str(), &buffer) != 0) {
        throw std::runtime_error("File not found: " + filename);
    }
    return buffer.st_mtime;
}
