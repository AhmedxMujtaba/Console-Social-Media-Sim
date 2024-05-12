#pragma once
#include <iostream>
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>
using namespace std;

class SystemFunctions {
public:
    static bool compareDates(const std::string& date1, const std::string& date2) {
        std::tm timeinfo1 = parseDate(date1);
        std::tm timeinfo2 = parseDate(date2);
        auto timepoint1 = std::chrono::system_clock::from_time_t(std::mktime(&timeinfo1));
        auto timepoint2 = std::chrono::system_clock::from_time_t(std::mktime(&timeinfo2));
        return timepoint1 > timepoint2;
    }

    static bool compareTimes(const std::string& time1, const std::string& time2) {
        std::tm timeinfo1 = parseTime(time1);
        std::tm timeinfo2 = parseTime(time2);
        auto timepoint1 = std::chrono::system_clock::from_time_t(std::mktime(&timeinfo1));
        auto timepoint2 = std::chrono::system_clock::from_time_t(std::mktime(&timeinfo2));
        return timepoint1 > timepoint2;
    }

    static std::string getCurrentDate() {
        auto now = std::chrono::system_clock::now();
        time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm* timeinfo = std::localtime(&currentTime);
        std::ostringstream oss;
        oss << std::put_time(timeinfo, "%Y-%m-%d");
        return oss.str();
    }

    static std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm* timeinfo = std::localtime(&currentTime);
        std::ostringstream oss;
        oss << std::put_time(timeinfo, "%H:%M:%S");
        return oss.str();
    }

    static string generateID(string idType){
        /*
        id types:
        Main Stacks: New stack is names after it is created and is named after calculating
        which number of stack is it E.g MS1, MS2 ...(MN)n
        Users: Users are named after the MS and then the user no in the stack E.g MS1-U1, MS2-U2 ... (MS)n-(U)n
        Posts: Post are named after Stack, then user and then the post number of the user.
        E.g: MS1U1P1, MS2-U1-P2 ... (MS)n-(U)n-(P)n
        Chats: Named after the two user ids MSn-Un-MSn-Un
        */
        

    }
private:
    static std::tm parseDate(const std::string& date) {
        std::tm timeinfo = {};
        std::istringstream(date) >> std::get_time(&timeinfo, "%Y-%m-%d");
        return timeinfo;
    }

    static std::tm parseTime(const std::string& time) {
        std::tm timeinfo = {};
        std::istringstream(time) >> std::get_time(&timeinfo, "%H:%M:%S");
        return timeinfo;
    }
};