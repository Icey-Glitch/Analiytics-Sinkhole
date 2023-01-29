#pragma once
#include <string>

class logging
{
public:
    static void write_to_console(const std::string& log_entry);
    static void log_init(const std::string& message);
    static void log(const std::string& message);
};
