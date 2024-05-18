#pragma once
#include "User.hpp"
#include "Console.hpp"
#include "Post.hpp"
#include "SystemFunctions.hpp"
#include "UserData.hpp"

class UserMenu
{

public:
    UserMenu(){};
    static void showUserMenu(User &user)
    {
        while (true)
        {
            string option = Console::promptWithChoices("\nWelcome " + user.getName(), {"Home Page", "Post", "Add Friends", "View Posts", "View Friends", "Profile", "Log Out"});

            if (option == "Home Page")
            {
                /*
                show posts of friends
                1- make a function to get the recent three posts of friends and
                 display them. No need for a extra fyp, just make a new stack for
                 everytime user logs in and display the stack
                2- Stack is destroyed as soon as user exits the home page to see the
                  posts

                */
                viewHomePage(user);
            }
            else if (option == "Post")
            {
                makePost(user);
            }
            else if (option == "Add Friends")
            {
                selectFriend(user);
            }
            else if (option == "View Posts")
            {
                user.displayAllPosts();
            }
            else if (option == "View Friends")
            {
                viewAllFriends(user);
            }
            else if (option == "Profile")
            {
                showProfile(user);
            }
            else if (option == "Log Out")
            {
                Console::printSpaced("Logging Out...");
                break;
            }
        }
    }

    static void makePost(User &user)
    {
        string title = Console::prompt("Title: ");
        string content = Console::prompt("Content: ");
        string dateCreated = SystemFunctions::getCurrentDate();
        string timeCreated = SystemFunctions::getCurrentTime();
        // Generate ID for the post
        int id = generateId(user);
        Post post(id, content, title, dateCreated, timeCreated);
        user.addPost(post);
        post.displayPost();
        Console::printSpaced("Post " + title + " has been created successfully");

        // add function to display the newly created post
    }
    static int generateId(User &user)
    {
        return user.incrementTotalPosts();
    }
    static void showProfile(User &user)
    {
        user.displayUserInfo();
        user.displayAllPostTitles();
        string subOption = Console::promptWithChoices("", {"Change Name", "Change Password", "Delete Post", "View a Post", "Menu"});
        if (subOption == "Change Name" || subOption == "1")
        {
            user.changeName();
        }
        else if (subOption == "Change Password" || subOption == "2")
        {
            user.changePassword();
        }
        else if (subOption == "Delete Post" || subOption == "3")
        {
            user.deletePost();
        }
        else if (subOption == "View a Post" || subOption == "4")
        {
            user.showSelectedPost();
        }
        else if (subOption == "Menu" || subOption == "5")
        {
            return;
        }
        else
        {
            cout << "Invalid option selected." << endl;
        }
    }
    static void selectFriend(User &user)
    {
        UserData &userDataInstance = UserData::getInstance();
        MainDataList &dataList = userDataInstance.getUserData();
        string friendName = Console::promptSpaced("\nEnter Name to Search: ");
        vector<User *> matchingUsers = dataList.searchSimilarUsernames(friendName);
        vector<string> matchingUserNames;

        if (matchingUsers.empty())
        {
            Console::printSpaced("No matching users found.");
            return;
        }

        matchingUserNames.reserve(matchingUsers.size());

        for (const auto &userPtr : matchingUsers)
        {
            // making sure that the user dont find himself here
            if (userPtr->getName() != user.getName())
            {
                matchingUserNames.push_back(userPtr->getName());
            }
        }

        string selectedUserName = Console::promptWithChoices("Select: ", matchingUserNames);
        User *selectedUserPtr = nullptr;

        for (auto &userPtr : matchingUsers)
        {
            if (userPtr->getName() == selectedUserName)
            {
                selectedUserPtr = userPtr;
                userPtr->displayUserInfo();
                break;
            }
        }

        if (!selectedUserPtr)
        {
            Console::printSpaced("Error: Selected user not found.");
            return;
        }

        string option = Console::promptWithChoices("Options: ", {"Add as Friend", "Back"});
        if (option == "Add as Friend")
        {
            // Check if they are already friends
            queue<string> currentFriends = user.getFriends();
            bool alreadyFriend = false;

            queue<string> tempQueue = currentFriends;
            while (!tempQueue.empty())
            {
                if (tempQueue.front() == selectedUserPtr->getEmail())
                {
                    alreadyFriend = true;
                    break;
                }
                tempQueue.pop();
            }

            if (alreadyFriend)
            {
                Console::printSpaced("User is already your friend.");
            }
            else
            {
                user.addFriend(selectedUserPtr->getEmail());
                selectedUserPtr->addFriend(user.getEmail());
                Console::printSpaced("You and " + selectedUserName + " are now friends.");
            }
        }
        else if (option == "Back")
        {
            return;
        }
    }

    static void viewAllFriends(User &user)
    {
        if (user.getFriends().empty())
        {
            Console::printSpaced("No Friends? Try manking some!");
            return;
        }

        UserData &userDataInstance = UserData::getInstance();
        MainDataList &dataList = userDataInstance.getUserData();
        vector<User *> friends = dataList.findFriends(user);
        vector<string> friendsNames;
        // Get the names of all friends
        for (size_t i = 0; i < friends.size(); i++)
        {
            friendsNames.push_back(friends[i]->getName());
        }

        // Display the names of all friends
        string selectedUserName = Console::promptWithChoices("Select: ", friendsNames);
        User *selectedUserPtr = nullptr;

        // Find the selected user from the list of friends
        for (auto &friendPtr : friends)
        {
            if (friendPtr->getName() == selectedUserName)
            {
                selectedUserPtr = friendPtr;
                break;
            }
        }

        // Check if the selected user exists
        if (!selectedUserPtr)
        {
            Console::printSpaced("Error: Selected user not found.");
            return;
        }

        
        while (true)
        {
            // Display the selected user's information
            selectedUserPtr->displayUserInfo();
            vector<string> options = {"Remove as Friend", "View Posts", "Back"};
            string option = Console::promptWithChoices("Options: ", options);

            if (option == "Remove as Friend")
            {
                // remove email of user and friend from thier friend email list and vice versa
                user.removeFriend(selectedUserPtr->getEmail());
                selectedUserPtr->removeFriend(user.getEmail());
                Console::printSpaced("You have removed " + selectedUserName + " as a friend.");
                break;
            }
            else if (option == "View Posts")
            {
                // later add option to like post, for that make sure you are passing the post as reference to
                // ensure the changes are occurring in the pist and not  Fucking copy
                selectedUserPtr->showSelectedPost();
            }
            else if (option == "Back")
            {
                break;
            }
        }
    }
    static void viewHomePage(User &user)
    {
        struct PostWithOwner
        {
            Post post;
            std::string ownerName;

            PostWithOwner(const Post &post, const std::string &ownerName)
                : post(post), ownerName(ownerName) {}
        };

        UserData &userDataInstance = UserData::getInstance();
        MainDataList &dataList = userDataInstance.getUserData();
        vector<User *> friends = dataList.findFriends(user);
        stack<PostWithOwner> postsStack;

        for (auto &friendPtr : friends)
        {
            queue<Post> friendPosts = friendPtr->getPosts();
            while (!friendPosts.empty() && postsStack.size() < 10)
            {
                postsStack.push(PostWithOwner(friendPosts.front(), friendPtr->getName()));
                friendPosts.pop();
            }
            if (postsStack.size() >= 10)
            {
                break;
            }
        }

        if (postsStack.empty())
        {
            Console::printSpaced("No posts to display.");
        }
        else
        {
            while (!postsStack.empty())
            {
                PostWithOwner postWithOwner = postsStack.top();
                Console::printSpaced(postWithOwner.ownerName);
                postWithOwner.post.displayPost();
                postsStack.pop();
            }
        }

        string option = Console::promptWithChoices("Options: ", {"Back"});
        if (option == "Back")
        {
            return;
        }
    }
};