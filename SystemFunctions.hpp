#pragma once

#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>

class SystemFunctions {
public:
    static bool compareDates(const std::string &date1, const std::string &date2) {
        std::tm timeinfo1 = parseDate(date1);
        std::tm timeinfo2 = parseDate(date2);
        auto timepoint1 = std::chrono::system_clock::from_time_t(std::mktime(&timeinfo1));
        auto timepoint2 = std::chrono::system_clock::from_time_t(std::mktime(&timeinfo2));
        return timepoint1 > timepoint2;
    }

    static bool compareTimes(const std::string &time1, const std::string &time2) {
        std::tm timeinfo1 = parseTime(time1);
        std::tm timeinfo2 = parseTime(time2);
        auto timepoint1 = std::chrono::system_clock::from_time_t(std::mktime(&timeinfo1));
        auto timepoint2 = std::chrono::system_clock::from_time_t(std::mktime(&timeinfo2));
        return timepoint1 > timepoint2;
    }

    static std::string getCurrentDate() {
        auto now = std::chrono::system_clock::now();
        time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm *timeinfo = std::localtime(&currentTime);
        std::ostringstream oss;
        oss << std::put_time(timeinfo, "%Y-%m-%d");
        return oss.str();
    }

    static std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm *timeinfo = std::localtime(&currentTime);
        std::ostringstream oss;
        oss << std::put_time(timeinfo, "%H:%M:%S");
        return oss.str();
    }

private:
    static std::tm parseDate(const std::string &date) {
        std::tm timeinfo = {};
        std::istringstream(date) >> std::get_time(&timeinfo, "%Y-%m-%d");
        return timeinfo;
    }

    static std::tm parseTime(const std::string &time) {
        std::tm timeinfo = {};
        std::istringstream(time) >> std::get_time(&timeinfo, "%H:%M:%S");
        return timeinfo;
    }
};
