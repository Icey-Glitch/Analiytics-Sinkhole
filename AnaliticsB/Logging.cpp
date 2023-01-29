#include "Logging.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <future>
#include <iomanip>

#include "time.h"

std::ofstream logfile("logfile.txt", std::ios::app | std::ios::out);

void logging::write_to_console(const std::string& log_entry) {
    try {
        std::clog << log_entry;
    } catch (const std::exception& e) {
        std::cerr << "Error writing to console: " << e.what() << std::endl;
    }
}

static void clear_log_file(const std::string& file_name) {
    logfile.close();
    std::ofstream log_file(file_name, std::ios::trunc);
    if (!log_file.is_open()) {
        std::cerr << "Error: failed to open log file '" << file_name << "'" << std::endl;
    }
    log_file.close();
    logfile.open(file_name, std::ios::app | std::ios::out);
}

void logging::log_init(const std::string& message) {
    clear_log_file("logfile.txt");
    std::ofstream log_file("logfile.txt", std::ios::app);
    if (!log_file.is_open()) {
        std::cerr << "Error: failed to open log file" << std::endl;
        logging::write_to_console("Error: failed to open log file\n");
        return;
    }
    log_file << "[" << time::get_current_time() << "] " << message << std::endl;
}

void logging::log(const std::string& message) {
    std::ofstream logfile("logfile.txt", std::ios_base::app | std::ios_base::out);
    if (!logfile.is_open()) {
        std::cerr << "Error opening logfile" << std::endl;
        return;
    }
    std::string log_entry = "[" + time::get_current_time() + "] " + message + "\n";
    logfile << log_entry;
    
    std::thread t1(write_to_console, log_entry);
    logfile.flush();
    logfile.close();
    t1.join();
}

