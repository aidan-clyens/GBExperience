#include "logger.h"


Logger logger;


void Logger::log(LogType_t log_type, bool newline, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    std::string msg = this->str_format(fmt, args);
    va_end(args);

    if (newline) {
        fprintf(stdout, "%s\n", msg.c_str());
    }
    else {
        fprintf(stdout, "%s", msg.c_str());
    }
}

std::string Logger::str_format(const char *fmt, va_list args) {
    char buf[8192];
    vsnprintf(buf, 8192, fmt, args);
    return std::string(buf);
}