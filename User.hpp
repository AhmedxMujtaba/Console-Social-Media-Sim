#pragma once
#include<iostream>
#include<string>
#include"DoubleLinkedList.hpp"
#include"Post.hpp"
#include"Chat.hpp"
#include<stack>
#include"ForYouPage.hpp"
using namespace std;

class User{
    private:
    string id;
    string name;
    string password;
    string email;
    int phoneNumber;
    string username;
    DoubleLinkedList<User> friends;
    DoubleLinkedList<Post> posts;
    stack<Chat> chats;

    public:
    User(string id, string name, string password, string email,
     int phoneNumber)
     {
        this->id = id;
        this->name = name;
        this->password = password;
        this->email = email;
        this->phoneNumber = phoneNumber;
        this->username = generateUserName();
     };

    
    
    string generateUserName(){
        string username = "niga";
        //to generate username we need the stack we are storing the
        //user and use the stack id and user id altogeather
        //but how? make user name while storing the stack?
        return username;
    }
};