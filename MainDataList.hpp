#pragma once
#include <iostream>
#include <algorithm>
#include <cctype>
#include <locale>
#include <set>
#include <iterator>
#include <vector>
#include <string>
#include "User.hpp"
using namespace std;

class MainDataList
{

private:
    struct node
    {
        User user;
        node *nextNode;
        node *previousNode;
    } *firstNode;

public:
    MainDataList()
    {
        firstNode = nullptr;
    }

    void insertAtEnd(User user)
    {
        node *newNode = new node;
        newNode->user = user;
        newNode->nextNode = nullptr;

        if (!firstNode)
        {
            firstNode = newNode;
            firstNode->previousNode = nullptr;
        }
        else
        {
            node *currentNode = firstNode;
            while (currentNode->nextNode)
            {
                currentNode = currentNode->nextNode;
            }
            currentNode->nextNode = newNode;
            newNode->previousNode = currentNode;
        }
    }

    void deleteNode(string email, string password)
    {
        if (!firstNode)
        {
            return; // Empty list
        }

        node *currentNode = firstNode;

        // Special case: deleting the only node in the list
        if (compareUser(currentNode->user, email, password) && currentNode->nextNode == nullptr)
        {
            delete currentNode;
            firstNode = nullptr;
            return;
        }

        // Delete the first node
        if (compareUser(currentNode->user, email, password))
        {
            firstNode = currentNode->nextNode;
            if (firstNode)
            {
                firstNode->previousNode = nullptr;
            }
            delete currentNode;
            return;
        }

        while (currentNode != nullptr)
        {
            if (compareUser(currentNode->user, email, password))
            {
                // Delete node from between
                currentNode->previousNode->nextNode = currentNode->nextNode;
                if (currentNode->nextNode)
                {
                    currentNode->nextNode->previousNode = currentNode->previousNode;
                }
                delete currentNode;
                return;
            }
            currentNode = currentNode->nextNode;
        }
    }

    User &findUser(const string &email, const string &password)
    {
        node *currentNode = firstNode;
        while (currentNode != nullptr)
        {
            if (compareUser(currentNode->user, email, password))
            {
                return currentNode->user;
            }
            currentNode = currentNode->nextNode;
        }
        static User invalidUser;
        return invalidUser;
    }

    bool compareUser(const User &user, const string &email, const string &password)
    {
        return user.getEmail() == email && user.getPassword() == password;
    }

    // Function to convert a string to lowercase
    string toLowerCase(const string &str)
    {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

    // Function to calculate the Jaccard similarity index
    double jaccardSimilarity(const string &str1, const string &str2)
    {
        set<char> set1(str1.begin(), str1.end());
        set<char> set2(str2.begin(), str2.end());

        set<char> intersectionSet;
        set<char> unionSet;

        set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                         inserter(intersectionSet, intersectionSet.begin()));
        set_union(set1.begin(), set1.end(), set2.begin(), set2.end(),
                  inserter(unionSet, unionSet.begin()));

        if (unionSet.empty())
            return 0.0;
        return static_cast<double>(intersectionSet.size()) / unionSet.size();
    }

   vector<User*> searchSimilarUsernames(const string& enteredUsername) {
    const double SIMILARITY_THRESHOLD = 0.7;
    vector<User*> similarUsers;
    node* currentNode = firstNode;

    // Convert entered username to lowercase
    string lowerEnteredUsername = toLowerCase(enteredUsername);

    while (currentNode != nullptr) {
        User& user = currentNode->user;
        string currUserName = toLowerCase(user.getName());

        // Calculate Jaccard similarity
        double similarity = jaccardSimilarity(lowerEnteredUsername, currUserName);

        if (similarity >= SIMILARITY_THRESHOLD) {
            similarUsers.push_back(&user);
        }

        currentNode = currentNode->nextNode;
    }

    return similarUsers;
}

    void display()
    {

        node *iterativeNode;
        iterativeNode = firstNode;
        if (firstNode == nullptr)
        {
            cout << "\nList Empty" << endl;
            return;
        }

        // Just iterating and printing the values not much to see here
        while (iterativeNode != nullptr)
        {
            cout << endl;
            iterativeNode->user.displayUserInfo();
            iterativeNode = iterativeNode->nextNode;
        }
    };
    vector<User*> findFriends(User& user) {
    vector<User*> friendsList;
    queue<string> emails = user.getFriends();
    vector<string> emailsVector;

    // Convert queue to vector
    while (!emails.empty()) {
        emailsVector.push_back(emails.front());
        emails.pop();
    }

    // Find and collect users based on emails
    for (const auto& email : emailsVector) {
        node* currentNode = firstNode;
        while (currentNode != nullptr) {
            if (currentNode->user.getEmail() == email) {
                friendsList.push_back(&(currentNode->user)); // Pushing address of the user
            }
            currentNode = currentNode->nextNode;
        }
    }

    return friendsList;
}
    bool isEmailExiting(const string email){
        node *currentNode = firstNode;
        while (currentNode != nullptr)
        {
            if (email == currentNode->user.getEmail())
            {
                return true;
            }
            currentNode = currentNode->nextNode;
        }
        return false;
    }
};