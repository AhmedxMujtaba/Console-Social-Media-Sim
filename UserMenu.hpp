#pragma once
#include "User.hpp"
#include "Console.hpp"
#include "Post.hpp"
#include "SystemFunctions.hpp"

class UserMenu{

public:
    UserMenu(){};
    static void showUserMenu(User user){
         string option = Console::promptWithChoices("Welcome " + user.getName(), {"Home Page","Post","Add Freinds","View Freinds","Profile","Log Out"});
           
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
            }
            else if (option == "Post")
            {
                /* 
                1- Show options to add title, content and then post.
                2- Save post in the users posts stack
                */
               makePost(user);
               
              
            }
            else if (option == "Add Friends")
            {
                /* 
                1- enter friend name,
                2- return array of the most similar looking names
                3- select the person and add as friend
                */
            }
            else if (option == "View Posts")
            {
                /* 1- take in a user and show all their posts*/
            }
            else if (option == "View Friends")
            {
                /* 1- take user and show all their friends */
            }
            else if (option == "Profile")
            {
                /* 1- take user and show name, friends, their posts 
                   2- also show menu to change name, password and delete posts, 
                      remove friends etc
                */
            }
            else if(option == "Log Out")
            {
                Console::printSpaced("Logging Out...");
                //code to return to main menu
            }
    }

 static void makePost(User& user) // Pass User by reference
{
    string title = Console::prompt("Title: ");
    string content = Console::prompt("Content: ");
    string dateCreated = SystemFunctions::getCurrentDate();
    string timeCreated = SystemFunctions::getCurrentTime();
    // Generate ID for the post
    const int id = generateId(user);
    Post post(id, title, content, dateCreated, timeCreated);
    user.addPost(post);
}

static int generateId(User& user) 
{
    return user.incrementTotalPosts(); 
}

};