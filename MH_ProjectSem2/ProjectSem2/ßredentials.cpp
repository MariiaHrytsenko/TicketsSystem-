#include "ñredentials.h"
#include "logger.h"
#include <fstream>

ñredentials::ñredentials(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> username >> password;
        logger::log(logger::Level::INFO, "Credentials loaded successfully");
    }
    else {
        logger::log(logger::Level::ERROR, "Unable to open file");
    }
}

std::string ñredentials::getUsername() const {
    return username;
}

std::string ñredentials::getPassword() const {
    return password;
}
