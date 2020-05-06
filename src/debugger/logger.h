#pragma once

#include <iostream>
#include <cstdarg>
#include <string>


#define CPU_DEBUG
#define INTERRUPT_DEBUG
#define IO_DEBUG
#define VIDEO_DEBUG


typedef enum LogLevel {
    LOG_INFO
} LogLevel_t;


class Logger {
    public:
        Logger() = default;

        void log(LogLevel_t, bool, const char *, ...);

        std::string str_format(const char *, va_list);
};


extern Logger logger;


#define log_info(...) logger.log(LOG_INFO, true, ##__VA_ARGS__);
#define log_info_no_new_line(...) logger.log(LOG_INFO, false, ##__VA_ARGS__);