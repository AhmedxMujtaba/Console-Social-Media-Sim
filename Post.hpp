#pragma once
#include <iostream>
#include <string>
#include <stack>   
#include "User.hpp"   
#include "Comment.hpp"   

using namespace std;

class Post {
private:
    string id;
    string content;
    string date;
    string time;
    stack<User> likes;
    stack<Comment> comments;

public:
   
    Post(string id, string content, string date, string time) {
        this->id = id;
        this->content = content;
        this->date = date;
        this->time = time;
    }


    string getId() const {
        return id;
    }

    void setId(const string& id) {
        this->id = id;
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

    void editPost(const string& content) {
        this->content = content;
    }
};
