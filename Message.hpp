#pragma once
#include <iostream>
#include "User.hpp"
using namespace std;

class Message {
private:
    string message;
    User user;
    string timeSent;
    string dateSent;

public:
    Message(string message, User user, string timeSent, string dateSent) {
        this->message = message;
        this->user = user;
        this->timeSent = timeSent;
        this->dateSent = dateSent;
    }

    string getMessage() const {
        return message;
    }

    void setMessage(const string& message) {
        this->message = message;
    }

    User getUser() const {
        return user;
    }

    void setUser(const User& user) {
        this->user = user;
    }

    string getTimeSent() const {
        return timeSent;
    }

    void setTimeSent(const string& timeSent) {
        this->timeSent = timeSent;
    }

    string getDateSent() const {
        return dateSent;
    }

    void setDateSent(const string& dateSent) {
        this->dateSent = dateSent;
    }
};
