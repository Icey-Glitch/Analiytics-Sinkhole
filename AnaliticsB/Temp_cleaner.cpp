#include "Temp_cleaner.h"

#include <filesystem>

#include "Logging.h"

#include <iostream>
#include <fstream>
#include <future>
#include <string>
#include <windows.h>

std::mutex mtx;

void deleteFile(const std::string &path) {
    std::lock_guard<std::mutex> lock(mtx);
    logging::log("Deleting file: " + path);
    std::ifstream file(path);
    file.close();
    std::remove(path.c_str());
}

void Temp_cleaner::delete_temp_files(const std::string &temp_folder) {
    std::vector<std::future<void>> futures;
    for (const auto &entry : std::filesystem::directory_iterator(temp_folder)) {
        if (entry.is_regular_file()) {
            futures.emplace_back(std::async(std::launch::async, deleteFile, entry.path().string()));
        } else if (entry.is_directory()) {
            futures.emplace_back(std::async(std::launch::async, delete_temp_files, entry.path().string()));
        }
    }
    for (auto &f : futures) {
        f.get();
    }
}

std::string Temp_cleaner::get_temp_folder()
{
    char* buffer;
    size_t buffer_size;
    if (const errno_t error = _dupenv_s(&buffer, &buffer_size, "TEMP"); error == 0) {
        std::string temp_folder(buffer);
        free(buffer);
        logging::log("Got TEMP folder: " + temp_folder);
        return temp_folder;
    }
    logging::log("Error getting TEMP folder");
    return "";
}