#include "time.h"
#include <ctime>
#include <stdexcept>

#include "Logging.h"

auto time::get_current_time() -> std::string
{
    try {
        const std::time_t now = std::time(nullptr);
        tm timelines{};
        char buffer[80];
        if (localtime_s(&timelines, &now) != 0) {
            throw std::runtime_error("Failed to get current time");
        }
        if (strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", &timelines) == 0) {
            throw std::runtime_error("Failed to format current time");
        }
        return buffer;
    } catch (const std::exception& e) {
        logging::log(e.what());
        throw;
    }
}
