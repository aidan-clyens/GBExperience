#include "logger.h"


Logger logger;


void Logger::log(LogType_t log_type, bool newline, const char *fmt, ...) {
    switch (log_type) {
        case LOG_WARN:
            if (!m_warn_logging_enabled) return;
            break;
        case LOG_CPU:
            if (!m_cpu_logging_enabled) return;
            break;
        case LOG_INTERRUPTS:
            if (!m_interrupt_logging_enabled) return;
            break;
        case LOG_IO:
            if (!m_io_logging_enabled) return;
            break;
        case LOG_VIDEO:
            if (!m_video_logging_enabled) return;
            break;
        case LOG_MEMORY:
            if (!m_memory_logging_enabled) return;
            break;
    }

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

void Logger::enable_logging(LogType_t log_type, bool enable) {
    switch (log_type) {
        case LOG_WARN:
            m_warn_logging_enabled = enable;
            break;
        case LOG_CPU:
            m_cpu_logging_enabled = enable;
            break;
        case LOG_INTERRUPTS:
            m_interrupt_logging_enabled = enable;
            break;
        case LOG_IO:
            m_io_logging_enabled = enable;
            break;
        case LOG_VIDEO:
            m_video_logging_enabled = enable;
            break;
        case LOG_MEMORY:
            m_memory_logging_enabled = enable;
            break;
    }
}
