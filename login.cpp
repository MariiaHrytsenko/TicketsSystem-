#include <iostream>
#include <fstream>

enum LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    Logger(std::string filename) {
        log_file.open(filename.c_str(), std::ios::out | std::ios::app);
        if (!log_file) {
            std::cerr << "File could not be opened\n";
            exit(1);
        }
    }

    ~Logger() {
        if (log_file) {
            log_file.close();
        }
    }

    void Log(LogLevel level, std::string message) {
        if (!log_file) {
            std::cerr << "File not open\n";
            return;
        }

        switch (level) {
        case INFO:
            log_file << "INFO: ";
            break;
        case WARNING:
            log_file << "WARNING: ";
            break;
        case ERROR:
            log_file << "ERROR: ";
            break;
        }

        log_file << message << std::endl;
    }

private:
    std::ofstream log_file;
};

int main() {
    Logger logger("log.txt");
    logger.Log(INFO, "Program started");
    logger.Log(WARNING, "This is a warning");
    logger.Log(ERROR, "This is an error");

    return 0;
}
