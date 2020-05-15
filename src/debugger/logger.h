#pragma once

#include <iostream>
#include <cstdarg>
#include <string>


typedef enum LogType {
    LOG_WARN,
    LOG_DEBUG,
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

        void enable_logging(LogType_t, bool);

        std::string str_format(const char *, va_list);
    
    private:
        bool m_warn_logging_enabled = false;
        bool m_debug_logging_enabled = false;
        bool m_cpu_logging_enabled = false;
        bool m_interrupt_logging_enabled = false;
        bool m_io_logging_enabled = false;
        bool m_video_logging_enabled = false;
        bool m_memory_logging_enabled = false;
};


extern Logger logger;


#define log_warn(...) logger.log(LOG_WARN, true, ##__VA_ARGS__);
#define log_warn_no_new_line(...) logger.log(LOG_WARN, false, ##__VA_ARGS__);
#define log_debug(...) logger.log(LOG_DEBUG, true, ##__VA_ARGS__);
#define log_debug_no_new_line(...) logger.log(LOG_DEBUG, false, ##__VA_ARGS__);
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

#define enable_warn_logging() logger.enable_logging(LOG_WARN, true);
#define disable_warn_logging() logger.enable_logging(LOG_WARN, false);
#define enable_debug_logging() logger.enable_logging(LOG_DEBUG, true);
#define disable_debug_logging() logger.enable_logging(LOG_DEBUG, false);
#define enable_cpu_logging() logger.enable_logging(LOG_CPU, true);
#define disable_cpu_logging() logger.enable_logging(LOG_CPU, false);
#define enable_interrupt_logging() logger.enable_logging(LOG_INTERRUPTS, true);
#define disable_interrupt_logging() logger.enable_logging(LOG_INTERRUPTS, false);
#define enable_io_logging() logger.enable_logging(LOG_IO, true);
#define disable_io_logging() logger.enable_logging(LOG_IO, false);
#define enable_video_logging() logger.enable_logging(LOG_VIDEO, true);
#define disable_video_logging() logger.enable_logging(LOG_VIDEO, false);
#define enable_memory_logging() logger.enable_logging(LOG_MEMORY, true);
#define disable_memory_logging() logger.enable_logging(LOG_MEMORY, false);