#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>


class TimingAnalyzer {
    public:
        TimingAnalyzer(const std::string &);
        virtual ~TimingAnalyzer();

        void get_start_time();
        float get_time_difference_ms();

        void log_cycle_time(uint8_t, long int);
        void save_cycle_times();

    private:
        std::chrono::steady_clock::time_point m_last_time;
        std::unordered_map<uint8_t, long int> m_operation_times;

        std::string m_file_name;

        std::chrono::steady_clock::time_point get_time();
};
