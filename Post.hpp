#pragma once
#include <iostream>
#include <string>
#include <stack>
#include "User.hpp"


using namespace std;

class Post
{
private:
    int id;
    string content;
    string title;
    string date;
    string time;
    bool isEdited;
    stack<string> likes;

public:
    // Constructor
    Post(int id, string content, string title, const string &date, const string &time)
        : id(id), content(std::move(content)), title(std::move(title)), date(date), time(time), isEdited(false) {}

    // Getter and setter for isEdited
    void setIsEdited(bool value)
    {
        isEdited = value;
    }

    bool getIsEdited() const
    {
        return isEdited;
    }

    // Getter for likes stack
    const stack<string> &getLikes() const
    {
        return likes;
    }

    // Method to add a like
    void addLike(const string &userEmail)
    {
        likes.push(userEmail);
    }

    // Method to remove a like (optional)
    void removeLike()
    {
        if (!likes.empty())
        {
            likes.pop();
        }
    }

    // Getter for id
    int getId() const
    {
        return id;
    }

    // Getter and setter for content
    const string &getContent() const
    {
        return content;
    }

    void setContent(const string &content)
    {
        this->content = content;
    }

    // Getter and setter for title
    const string &getTitle() const
    {
        return title;
    }

    void setTitle(const string &title)
    {
        this->title = title;
    }

    // Getter and setter for date
    const string &getDate() const
    {
        return date;
    }

    void setDate(const string &date)
    {
        this->date = date;
    }

    // Getter and setter for time
    const string &getTime() const
    {
        return time;
    }

    void setTime(const string &time)
    {
        this->time = time;
    }
    void displayPost()const
    {
        cout << "\n------------------------------------------" << endl;
        cout << "Title: " << title << endl;
        cout << "Date: " << date << "            ";
        cout << "Time: " << time << endl;
        cout << "\n" << content << endl;
        //cout << "Likes: " << likes << endl;
        cout << "------------------------------------------";
        cout << endl;
    }
};
