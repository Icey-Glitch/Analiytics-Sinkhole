#pragma once
#include <string>

class logging
{
public:
    static void logInit(const std::string& message);
    static void Log(const std::string& message);
};
