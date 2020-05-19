#include "string_utils.h"


std::string ltrim(const std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

std::vector<std::string> get_input_words_list() {
    std::string buf;
    std::getline(std::cin, buf);
    std::istringstream iss(buf);
    std::vector<std::string> args = {
        std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>()
    };

    return args;
}

uint16_t get_input_hex(const std::string &arg) {
    uint16_t num;
    std::stringstream ss;
    ss << std::hex << arg;
    ss >> num;

    return num;
}
