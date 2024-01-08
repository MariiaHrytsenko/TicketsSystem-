#include "logger.h"

void logger::log(Level level, const std::string& message) {
    switch (level) {
    case Level::INFO:
        std::cout << "[INFO] " << message << std::endl;
        break;
    case Level::ERROR:
        std::cerr << "[ERROR] " << message << std::endl;
        break;
    }
}
