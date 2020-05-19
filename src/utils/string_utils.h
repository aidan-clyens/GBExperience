#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>


const std::string WHITESPACE = " \n\r\t\f\v";


std::string ltrim(const std::string &);
std::string rtrim(const std::string &);
std::string trim(const std::string &);

std::vector<std::string> get_input_words_list();
uint16_t get_input_hex(const std::string &);