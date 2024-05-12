#pragma once
#include<iostream>
#include<string>
#include<Stack>
#include<User.hpp>
using namespace std;

class IDStack{
private:
//Stack id ranges are 100 create a new stack after 100 is complete;
    string stackId;
    stack<User> userStack;
    
public:
 void addNewStack(){}
};

