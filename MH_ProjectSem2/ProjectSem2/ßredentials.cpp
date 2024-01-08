#include "�redentials.h"
#include "logger.h"
#include <fstream>

�redentials::�redentials(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> username >> password;
        logger::log(logger::Level::INFO, "Credentials loaded successfully");
    }
    else {
        logger::log(logger::Level::ERROR, "Unable to open file");
    }
}

std::string �redentials::getUsername() const {
    return username;
}

std::string �redentials::getPassword() const {
    return password;
}
