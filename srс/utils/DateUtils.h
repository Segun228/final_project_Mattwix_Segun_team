#pragma once
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>

namespace DateUtils {

inline std::string formatTimePoint(const std::chrono::system_clock::time_point& tp) {
    auto time_t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

} // namespace DateUtils