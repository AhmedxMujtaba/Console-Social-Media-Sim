#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "Post.hpp"
#include "Console.hpp"

using namespace std;

class User {
private:
    string name;
    string password;
    string email;
    int phoneNumber;
    string username;
    bool isValid = false;
    queue<Post> posts;
    int totalPosts;

public:
    User() {}
    User(string name1, string password1, string email1, int phoneNumber1, bool isValid)
        : name(name1), password(password1), email(email1), phoneNumber(phoneNumber1), isValid(isValid) {
        this->username = generateUserName();
        this->totalPosts = 0;
    }

    string generateUserName() {
        string uName = "user123"; // Placeholder logic for username generation
        return uName;
    }

    string getEmail() const {
        return this->email;
    }
    string getPassword() const {
        return this->password;
    }
    string getName() const {
        return this->name;
    }
    bool isValidCheck() const {
        return isValid;
    }
    const queue<Post>& getPosts() const {
        return posts;
    }
    int incrementTotalPosts() {
        return ++totalPosts;
    }
    void addPost(const Post &post) {
        posts.push(post);
    }
    void displayUserInfo() const {
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Number of Posts: " << totalPosts << endl;
    }
    void changeName() {
        string newName = Console::prompt("Enter new name: ");
        this->name = newName;
        cout << "Name changed to: " << name << endl;
    }
    void changePassword() {
        string newPassword = Console::prompt("Enter new password: ");
        this->password = newPassword;
        cout << "Password changed to: " << password << endl;
    }
    void displayAllPosts() const {
        cout << "\nYour Posts:" << endl;
        if (posts.empty()) {
            cout << "\nNo posts available." << endl;
        } else {
            queue<Post> tempQueue = posts;
            while (!tempQueue.empty()) {
                const Post &post = tempQueue.front();
                post.displayPost();
                cout << endl;
                tempQueue.pop();
            }
        }
    }
    vector<string> getAllPostsTitles() const {
        vector<string> titles;
        queue<Post> tempQueue = posts;
        while (!tempQueue.empty()) {
            const Post &post = tempQueue.front();
            titles.push_back(post.getTitle());
            tempQueue.pop();
        }
        return titles;
    }
    void displayAllPostTitles() const {
        cout << "All Post Titles:" << endl;
        if (posts.empty()) {
            cout << "No posts available." << endl;
        } else {
            int i = 1;
            queue<Post> tempQueue = posts;
            while (!tempQueue.empty()) {
                const Post &post = tempQueue.front();
                cout << i << "- " << post.getTitle() << endl;
                tempQueue.pop();
                i++;
            }
        }
    }

    void deletePost() {
        vector<string> titles = getAllPostsTitles(); // Vector to store titles of all posts
        if (titles.empty()) {
            cout << "No posts available to delete." << endl;
            return;
        }

        string postToDelete = Console::promptWithChoices("Select Post to Delete", titles);

        queue<Post> tempQueue; // Temporary queue to store posts
        bool postFound = false;

        while (!posts.empty()) {
            Post post = posts.front();
            posts.pop();
            if (post.getTitle() == postToDelete) {
                postFound = true;
                totalPosts--; // Decrement the total number of posts
            } else {
                tempQueue.push(post); // Restore non-deleted posts to the temporary queue
            }
        }

        while (!tempQueue.empty()) {
            posts.push(tempQueue.front());
            tempQueue.pop();
        }

        if (!postFound) {
            cout << "Post '" << postToDelete << "' not found." << endl;
        } else {
            cout << "Post '" << postToDelete << "' deleted successfully." << endl;
        }
    }

    void showSelectedPost() const {
        vector<string> titles = getAllPostsTitles();
        if (titles.empty()) {
            cout << "No posts available to view." << endl;
            return;
        }

        string postTitle = Console::promptWithChoices("Select a post to view:", titles);

        queue<Post> tempQueue = posts;
        bool postFound = false;
        while (!tempQueue.empty()) {
            const Post &post = tempQueue.front();
            if (post.getTitle() == postTitle) {
                post.displayPost();
                postFound = true;
                break;
            }
            tempQueue.pop();
        }

        if (!postFound) {
            cout << "Post with title '" << postTitle << "' not found." << endl;
        }
    }
};
