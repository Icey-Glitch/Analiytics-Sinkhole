#include "Logging.h"

#include "time.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>

std::ofstream logfile("logfile.txt", std::ios_base::app | std::ios_base::out);

void clear_log_file(const std::string& file_name) {
    std::ofstream log_file(file_name, std::ios::trunc);
    if (!log_file.is_open()) {
        std::cerr << "Error: failed to open log file '" << file_name << "'" << std::endl;
    }
}

void logging::logInit(const std::string& message) {
    clear_log_file("logfile.txt");
    std::ofstream log_file("logfile.txt", std::ios::app);
    if (!log_file.is_open()) {
        std::cerr << "Error: failed to open log file" << std::endl;
        return;
    }
    log_file << "[" << time::get_current_time() << "] " << message << std::endl;
}

void logging::Log(const std::string& message) {
    std::ofstream logfile("logfile.txt", std::ios_base::app | std::ios_base::out);
    std::stringstream ss;
    if (!logfile.is_open()) {
        std::cout << "Error opening logfile" << std::endl;
        return;
    }
    ss << "[" << time::get_current_time() << "] " << message << std::endl;
    std::cout << ss.str();
    logfile << "[" << time::get_current_time() << "] " << message << std::endl;
    logfile.close();
}

