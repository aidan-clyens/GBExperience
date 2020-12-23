#include "timing_analyzer.h"

TimingAnalyzer::TimingAnalyzer(const std::string &file_name):
m_file_name(file_name)
{

}

TimingAnalyzer::~TimingAnalyzer() {

}

void TimingAnalyzer::log_cycle_time(uint8_t opcode, long int dt) {
    m_operation_times.emplace(opcode, dt);
}

void TimingAnalyzer::log_time(long int dt) {
    m_times.push_back(dt);
}

void TimingAnalyzer::save_cycle_times() {
    std::unordered_map<uint8_t, long int>::iterator it;

    std::ofstream result_file;
    result_file.open(m_file_name);

    for (it = m_operation_times.begin(); it != m_operation_times.end(); it++) {
        uint8_t opcode = it->first;
        long int dt = it->second;

        result_file << static_cast<int>(opcode) << "," << dt << "\n";
    }

    result_file.close();

    std::cout << "Saved timing analysis to: " << m_file_name << std::endl;
}

void TimingAnalyzer::save_times() {
    std::ofstream result_file;
    result_file.open(m_file_name);

    for (auto it = m_times.begin(); it != m_times.end(); it++) {
        long int dt = *it;
        result_file << dt << "\n";
    }

    result_file.close();

    std::cout << "Saved timing analysis to: " << m_file_name << std::endl;
}