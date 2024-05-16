#pragma once
#include "User.hpp"
#include "UserMenu.hpp"
#include "Console.hpp"
#include "SystemFunctions.hpp"
#include "UserData.hpp"
#include <iostream>
#include <string>
using namespace std;

class MainMenu {
public:
    static void mainMenuOptions() {
        string option = Console::promptWithChoices("Welcome To Social Media Simulator", {"Login", "Sign Up", "Exit"});

        if (option == "Login") {
            User usr = login();
            if (usr.isValidCheck())
                {UserMenu::showUserMenu(usr);}
            else
                {Console::printSpaced("Invalid Username or Password");}
            
        } else if (option == "Sign Up") {
            signUp();

        } else if (option == "Exit") {
            Console::printSpaced("Thank You for using Social Media Simulator, see you again!");
            exit(0);
        } else {
            Console::printSpaced("Invalid Input");
        }
    }

    static User login() {
        string email = Console::promptSpaced("Enter Your Email");
        string password = Console::promptSpaced("Enter Your Password");

        // Use the singleton instance of UserData
        UserData& userDataInstance = UserData::getInstance();
        User currUser = userDataInstance.getUserData().findUser(email, password);
        return currUser;
    }

    static void signUp() {
        string name, password, email;
        name = Console::promptSpaced("Enter Your Name");
        email = Console::promptSpaced("Enter Your Email");

        while (!validateEmail(email)) {
            email = Console::promptSpaced("Enter Correct email, include '@'");
        }

        password = Console::promptSpaced("Enter Your Password");
        int phoneNumber = getPhoneNumber();
        User user(name, password, email, phoneNumber, true);

        // Save user in the database using the singleton instance of UserData
        UserData& userDataInstance = UserData::getInstance();
        userDataInstance.getUserData().insertAtEnd(user);

        Console::printSpaced("User signed up successfully. Returning to main menu...");
        mainMenuOptions();
    }

    static bool validateEmail(const string& email) {
        return email.find('@') != string::npos;
    }

    static int getPhoneNumber() {
        string phNoStr = Console::promptSpaced("Enter Phone Number: ");
        int phoneNoInt;

        while (true) {
            try {
                phoneNoInt = stoi(phNoStr);
                break;
            } catch (const invalid_argument& e) {
                cerr << "Invalid, Enter Digits Only: " << e.what() << endl;
                phNoStr = Console::promptSpaced("Enter Phone Number: ");
            } catch (const out_of_range& e) {
                cerr << "Out of range error: " << e.what() << endl;
                phNoStr = Console::promptSpaced("Enter Phone Number: ");
            }
        }
        return phoneNoInt;
    }
};
