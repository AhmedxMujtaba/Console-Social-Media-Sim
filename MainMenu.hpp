#pragma once
#include "User.hpp"
#include "UserMenu.hpp"
#include "Console.hpp"
#include "SystemFunctions.hpp"
#include "UserData.hpp"
#include <iostream>
#include <string>
using namespace std;

class MainMenu
{
public:
    static void mainMenuOptions()
    {
        string option = Console::promptWithChoices("\nWelcome To Social Media Simulator", {"Login", "Sign Up", "Exit", "Display"});

        if (option == "Login")
        {
            User &usr = login();
            if (usr.isValidCheck())
            {
                UserMenu::showUserMenu(usr);
            }
            else
            {
                Console::printSpaced("Invalid Username or Password");
            }
        }
        else if (option == "Sign Up")
        {
            signUp();
        }
        else if (option == "Exit")
        {
            Console::printSpaced("Thank You for using Social Media Simulator, see you again!");
            exit(0);
        }
        else if (option == "Display")
        {
            UserData::getInstance().getUserData().display();
        }
        else
        {
            Console::printSpaced("Invalid Input");
        }
    }

    static User &login()
    {
        string email = Console::promptSpaced("Enter Your Email");
        string password = Console::promptSpaced("Enter Your Password");

        // Use the singleton instance of UserData
        UserData &userDataInstance = UserData::getInstance();
        User &currUser = userDataInstance.getUserData().findUser(email, password);
        return currUser;
    }

    static void signUp()
    {
        string name, password, email;
        name = Console::promptSpaced("Enter Your Name");
        email = Console::promptSpaced("Enter Your Email");

        while (!validateEmail(email))
        {
            email = Console::promptSpaced("Enter Email Again: ");
        }

        password = Console::promptSpaced("Enter Your Password");
        while (!validatePassword(password))
        {
            password = Console::promptSpaced("Enter Password Again: ");
        }
        string op = Console::promptWithChoices("Enter Phone Number? ", {"Yes", "No"});
        int phoneNumber;
        if (op == "Yes")
        {
            phoneNumber = getPhoneNumber();
        }
        else if (op == "No")
        {
            phoneNumber = 00000000000;
        }
        else
        {
            phoneNumber = 00000000000;
            cout << "Invalid Option" << endl;
        }

        User user(name, password, email, phoneNumber, true);

        // Save user in the database using the singleton instance of UserData
        UserData &userDataInstance = UserData::getInstance();
        userDataInstance.getUserData().insertAtEnd(user);

        Console::printSpaced("User signed up successfully. Returning to main menu...");
        mainMenuOptions();
    }

    static bool validateEmail(const string &email)
    {
        if (emailAlreadyExist(email))
        {
            Console::printSpaced("Email Already Exists!");
            return false;
        }
        else if (email.find('@') == string::npos)
        {
            Console::printSpaced("Email must include '@'");
            return false;
        }

        return true;
    }

    static bool emailAlreadyExist(const string &email)
    {
        // check if the email already exits within the data list if it does return a error.
        UserData &userDataInstance = UserData::getInstance();
        MainDataList &dataList = userDataInstance.getUserData();
        return dataList.isEmailExiting(email);
    }

    static long long int getPhoneNumber()
{
    string phNoStr;
    long long int phoneNoInt;

    while (true)
    {
        phNoStr = Console::promptSpaced("Enter Phone Number: ");

        if (phNoStr.length() != 11)
        {
            cout << "Enter exactly 11 digits for the Phone Number: " << endl;
            continue;
        }

        bool isValid = true;
        for (char c : phNoStr)
        {
            if (!isdigit(c))
            {
                isValid = false;
                break;
            }
        }

        if (!isValid)
        {
            cout << "Invalid input. Please enter digits only: " << endl;
        }
        else
        {
            try
            {
                phoneNoInt = stoll(phNoStr);
                break;
            }
            catch (const out_of_range &e)
            {
                cout << "Out of range error. Please enter a smaller number: " << endl;
            }
            catch (const invalid_argument &e)
            {
                cout << "Invalid input. Please enter digits only: " << endl;
            }
        }
    }

    return phoneNoInt;
}


    static bool validatePassword(const string &password)
    {

        if (password.length() < 8 && !password.empty())
        {
            Console::printSpaced("Password must include at least 8 characters");
            return false;
        }

        return true;
    }
};
