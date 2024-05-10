#include "User.hpp"
using namespace std;

class Comment {
private:
    string content;
    string date;
    string time;
    User user;

public:
    Comment(User user, string content, string date, string time) {
        this->user = user;
        this->content = content;
        this->date = date;
        this->time = time;
    }

    string getContent() const {
        return content;
    }

    void setContent(const string& content) {
        this->content = content;
    }

    string getDate() const {
        return date;
    }

    void setDate(const string& date) {
        this->date = date;
    }

    string getTime() const {
        return time;
    }

    void setTime(const string& time) {
        this->time = time;
    }

    User getUser() const {
        return user;
    }

    void setUser(const User& user) {
        this->user = user;
    }
};
