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
    bool isValid = false;
    queue<Post> posts;
    queue<string> friends;
    int totalPosts;

public:
    User() {}
    User(string name1, string password1, string email1, int phoneNumber1, bool isValid)
        : name(name1), password(password1), email(email1), phoneNumber(phoneNumber1), isValid(isValid) {
        this->totalPosts = 0;
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
    queue<string> getFriends(){
        return friends;
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
        cout << "\nName: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Number of Posts: " << totalPosts << endl;
        cout << "Number of Friends: " << friends.size() << endl;
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
        cout << "Posts:" << endl;
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
            cout << "Post '" << postTitle << "' not found." << endl;
        }
    }

    void addFriend(string email){
        friends.push(email);
    }

    void displayFriends() {
        queue<string> tempQueue = friends;
        while (!tempQueue.empty()) {
            cout << tempQueue.front() << endl;
            tempQueue.pop();
        }
    }
    
    void removeFriend(const string& email) {
        queue<string> tempQueue;
        bool found = false;

        while (!friends.empty()) {
            string currentFriend = friends.front();
            friends.pop();

            if (currentFriend != email) {
                tempQueue.push(currentFriend);
            } else {
                found = true;
            }
        }
        friends = tempQueue;
    }
};
