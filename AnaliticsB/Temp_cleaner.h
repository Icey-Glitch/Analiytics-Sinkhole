#pragma once
#include <xstring>

class Temp_cleaner
{
public:
    static std::string get_temp_folder();
    static void delete_temp_files(const std::string& temp_folder);
};
