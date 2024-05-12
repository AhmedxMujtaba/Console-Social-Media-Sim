#pragma once
#include "User.hpp"
#include "Console.hpp"
#include <iostream>
#include <string>
using namespace std;

class MainMenu{
    public:
        static void mainMenuOptions(){
            string option = Console.promptWithChoices("Welcome To Social Media Simulator", {"Login","Sign Up","Exit"});
            if (option == "Login")
            {
                /* code */
            }
            else if (option == Sign Up)
            {
                /* code */
            }
            else
            {
                Console.printSpaced("Thank You for using Social Media Simulator, see you again!")
                exit(0);
            }
            
            
        }
};
