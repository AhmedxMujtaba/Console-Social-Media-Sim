#pragma once
#include "User.hpp"
#include "Console.hpp"
#include "Post.hpp"
#include "SystemFunctions.hpp"

class UserMenu
{

public:
    UserMenu(){};
    static void showUserMenu(User& user)
    {
        while (true)
        {
            string option = Console::promptWithChoices("\nWelcome " + user.getName(), {"Home Page", "Post", "Add Freinds", "View Posts", "View Freinds", "Profile", "Log Out"});

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
               //stacks are over rated, user a function to 
            }
            else if (option == "Post")
            {
                makePost(user);
            }
            else if (option == "Add Friends")
            {
                /*
                1- enter friend name,
                2- return array of the most similar looking names
                3- select the person and add as friend
                */
               //fuck
            }
            else if (option == "View Posts")
            {
                user.displayAllPosts();
            }
            else if (option == "View Friends")
            {
                /* 1- take user and show all their friends */
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

    static void makePost(User &user) // Pass User by reference
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
};