#include<iostream>
#include"MainMenu.hpp"
#include"MainDataList.hpp"

int main(){
    //create a main data list in global var?
    //pass it arround to cause modifications in it  
    while (true)
    {
    MainMenu::mainMenuOptions();
    UserData::getInstance().getUserData().display();
    }
    return 0;
}