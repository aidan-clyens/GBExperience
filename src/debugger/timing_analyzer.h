#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>


class TimingAnalyzer {
    public:
        TimingAnalyzer(const std::string &);
        virtual ~TimingAnalyzer();

        void log_cycle_time(uint8_t, long int);
        void log_time(long int, long int);
        void save_cycle_times();
        void save_times();

    private:
        std::unordered_map<uint8_t, long int> m_operation_times;
        std::list<std::pair<long int, long int>> m_times;

        std::string m_file_name;
};
