#include "utils.hpp"
#include <fstream>

void Error_(const std::string& message, const char* file, int line) {
    std::cout << TEXT_RED << "error: " << TEXT_YELLOW << message << TEXT_RESET << " | " << file << " (" << line << ")" << std::endl;
}

void Warning_(const std::string& message, const char* file, int line) {
    std::cout << TEXT_YELLOW << "warning: " << TEXT_WHITE << message << TEXT_RESET << " | " << file << " (" << line << ")" << std::endl;
}

void Log_(const std::string& message) {
    std::cout << TEXT_GREEN << "LOG: " << message << TEXT_RESET << std::endl;
}