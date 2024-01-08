#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

class logger {
public:
    enum class Level {
        INFO,
        ERROR
    };

    static void log(Level level, const std::string& message);
};

#endif // LOGGER_H
