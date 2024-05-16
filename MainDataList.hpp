#pragma once
#include <iostream>
#include "User.hpp"
using namespace std;

class MainDataList {

private:
    struct node {
        User user;
        node* nextNode;
        node* previousNode;
    }*firstNode;

public:
    MainDataList() {
        firstNode = nullptr;
    }

    void insertAtEnd(User user) {
        node* newNode = new node;
        newNode->user = user;
        newNode->nextNode = nullptr;

        if (!firstNode) {
            firstNode = newNode;
            firstNode->previousNode = nullptr;
        }
        else {
            node* currentNode = firstNode;
            while (currentNode->nextNode) {
                currentNode = currentNode->nextNode;
            }
            currentNode->nextNode = newNode;
            newNode->previousNode = currentNode;
        }
    }

    void deleteNode(string email, string password) {
        if (!firstNode) {
            return; // Empty list
        }

        node* currentNode = firstNode;

        // Special case: deleting the only node in the list
        if (compareUser(currentNode->user,email,password) && currentNode->nextNode == nullptr) {
            delete currentNode;
            firstNode = nullptr;
            return;
        }

        // Delete the first node
        if (compareUser(currentNode->user,email,password)) {
            firstNode = currentNode->nextNode;
            if (firstNode) {
                firstNode->previousNode = nullptr;
            }
            delete currentNode;
            return;
        }

        while (currentNode != nullptr) {
            if (compareUser(currentNode->user,email,password)) {
                // Delete node from between
                currentNode->previousNode->nextNode = currentNode->nextNode;
                if (currentNode->nextNode) {
                    currentNode->nextNode->previousNode = currentNode->previousNode;
                }
                delete currentNode;
                return;
            }
            currentNode = currentNode->nextNode;
        }
    }

    bool compareUser(User user1, string email, string password){
        if (user1.getEmail() == email && user1.getPassword() == password)
        {
            return true;
        }
        return false;
    };

   User findUser(string email, string password) {
    node* currentNode = firstNode;
    while (currentNode != nullptr) {
        if (compareUser(currentNode->user, email, password)) {
            return currentNode->user;
        }
        currentNode = currentNode->nextNode;
    }
   
    return User();
}

    void display() {

        node* iterativeNode;
        iterativeNode = firstNode;
        if (firstNode == nullptr)
        {
            cout << "List Empty" << endl;
            return;
        }

        //Just iterating and printing the values not much to see here
        cout << "[ ";
        while (iterativeNode != nullptr)
        {
            cout << iterativeNode->user.getName() << " ";
            iterativeNode = iterativeNode->nextNode;
        }
        cout << "]" << endl;

    };
};