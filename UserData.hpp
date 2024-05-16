#pragma once
#include "MainDataList.hpp"

class UserData {
private:
    MainDataList userData;  

    // Private constructor to prevent direct instantiation
    UserData() {}

public:
    // Delete copy constructor and assignment operator to prevent copying
    UserData(const UserData&) = delete;
    UserData& operator=(const UserData&) = delete;

    // Static method to get the singleton instance
    static UserData& getInstance() {
        static UserData instance;
        return instance;
    }

    // Accessor method for userData
    MainDataList& getUserData() {
        return userData;
    }
};
