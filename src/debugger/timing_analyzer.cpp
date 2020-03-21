#include "timing_analyzer.h"

TimingAnalyzer::TimingAnalyzer(const std::string &file_name):
m_last_time(get_time()),
m_file_name(file_name)
{

}

TimingAnalyzer::~TimingAnalyzer() {

}

void TimingAnalyzer::get_start_time() {
    m_last_time = get_time();
}

float TimingAnalyzer::get_time_difference_us() {
    std::chrono::steady_clock::time_point end = get_time();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - m_last_time).count();    
}

std::chrono::steady_clock::time_point TimingAnalyzer::get_time() {
    return std::chrono::steady_clock::now();
}

void TimingAnalyzer::log_cycle_time(uint8_t opcode, long int dt) {
    m_operation_times.emplace(opcode, dt);
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