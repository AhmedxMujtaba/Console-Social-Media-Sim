#pragma once
#include <iostream>
#include <string>
#include "Post.hpp"
#include <stack>

using namespace std;

class User {
private:
    string name;
    string password;
    string email;
    int phoneNumber;
    string username;
    bool isValid = false;
    stack<Post> posts;
    int totalPosts;

public:
    User() {}
    User(string name1, string password1, string email1,
         int phoneNumber1, bool isValid)
        : name(name1), password(password1), email(email1), phoneNumber(phoneNumber1), isValid(isValid) {
        this->username = generateUserName();
        this->totalPosts = 0;
    }

    string generateUserName() {
        string uName = "niga";
        // Your logic to generate a username
        return uName;
    }

    string getEmail() {
        return this->email;
    }
    string getPassword() {
        return this->password;
    }
    string getName() {
        return this->name;
    }
    bool isValidCheck() {
        return isValid;
    }
    stack<Post> getPosts() {
        return posts;
    }
    int incrementTotalPosts() {
        this->totalPosts++;
        return totalPosts;
    }

    void addPost(const Post& post) {
        posts.push(post);     
    }
};
