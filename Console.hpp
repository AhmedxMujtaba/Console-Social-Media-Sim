#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Console {
public:
    static void print(const string& message) {
        cout << message << endl;
    }

    static void printSpaced(const string& message) {
        print(message + '\n');
    }

    static string prompt(const string& prompt) {
        cout << prompt << endl;
        string answer;
        getline(cin, answer);
        return answer;
    }

    static string promptSpaced(const string& prmpt) {
        string answer = prompt(prmpt);
        cout << endl;
        return answer;
    }

    static void printSpace() {
        cout << endl;
    }

    static string promptWithChoices(const string& prompt, const vector<string>& choices) {
        cout << prompt << endl;
        return getValidAnswer(prompt, choices);
    }

    static string promptWithChoicesSpaced(const string& prompt, const vector<string>& choices) {
        string choice = promptWithChoices(prompt, choices);
        cout << endl;
        return choice;
    }

private:
    static string getValidAnswer(const string& prompt, const vector<string>& choices) {
        string chosenAnswer;
        while (true) {
            cout << formatAnswers(choices) << endl;
            string userInput;
            getline(cin, userInput);

            // Check if user input is a number
            if (all_of(userInput.begin(), userInput.end(), ::isdigit)) {
                int choiceNum = stoi(userInput);
                if (choiceNum >= 1 && choiceNum <= choices.size()) {
                    chosenAnswer = choices[choiceNum - 1];
                    break;
                }
            }

            // Check if user input matches any of the choices
            for (const auto& answer : choices) {
                if (userInput == answer) {
                    chosenAnswer = answer;
                    break;
                }
            }

            if (!chosenAnswer.empty()) {
                break;
            }

            cout << "\nIncorrect choice. Please enter the corresponding number or the choice text." << endl;
        }
        return chosenAnswer;
    }

    static string formatAnswers(const vector<string>& answers) {
        string validAnswers;
        for (size_t i = 0; i < answers.size(); ++i) {
            validAnswers += to_string(i + 1) + ". " + answers[i];
            if (i != answers.size() - 1) {
                validAnswers += '\n';
            }
        }
        return validAnswers;
    }
};
