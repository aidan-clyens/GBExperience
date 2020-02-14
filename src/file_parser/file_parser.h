#pragma once

#include <fstream>
#include <iostream>
#include <string>

class FileParser {
    public:
        FileParser(int);
        virtual ~FileParser();
    
        bool load_rom(const std::string &);

        uint8_t get_byte(int) const;
        int get_buffer_size() const;

        void print_to_file();
    
    private:
        int m_buffer_size;
        uint8_t *m_buffer;
};