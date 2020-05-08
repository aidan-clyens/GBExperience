#pragma once

#include <iostream>
#include <cstdarg>
#include <string>


#define CPU_DEBUG
#define INTERRUPT_DEBUG
#define IO_DEBUG
#define VIDEO_DEBUG
#define MEMORY_DEBUG


typedef enum LogType {
    LOG_CPU,
    LOG_INTERRUPTS,
    LOG_IO,
    LOG_VIDEO,
    LOG_MEMORY
} LogType_t;


class Logger {
    public:
        Logger() = default;

        void log(LogType_t, bool, const char *, ...);

        std::string str_format(const char *, va_list);
};


extern Logger logger;


#define log_cpu(...) logger.log(LOG_CPU, true, ##__VA_ARGS__);
#define log_cpu_no_new_line(...) logger.log(LOG_CPU, false, ##__VA_ARGS__);
#define log_interrupts(...) logger.log(LOG_INTERRUPTS, true, ##__VA_ARGS__);
#define log_interrupts_no_new_line(...) logger.log(LOG_INTERRUPTS, false, ##__VA_ARGS__);
#define log_io(...) logger.log(LOG_IO, true, ##__VA_ARGS__);
#define log_io_no_new_line(...) logger.log(LOG_IO, false, ##__VA_ARGS__);
#define log_video(...) logger.log(LOG_VIDEO, true, ##__VA_ARGS__);
#define log_video_no_new_line(...) logger.log(LOG_VIDEO, false, ##__VA_ARGS__);
#define log_memory(...) logger.log(LOG_MEMORY, true, ##__VA_ARGS__);
#define log_memory_no_new_line(...) logger.log(LOG_MEMORY, false, ##__VA_ARGS__);