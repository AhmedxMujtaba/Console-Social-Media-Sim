#pragma once
#include <iostream>
#include <string>
#include <vector>

class Console {
public:
    static void print(const std::string& message) {
        std::cout << message << std::endl;
    }

    static void printSpaced(const std::string& message) {
        print(message + '\n');
    }

    static std::string prompt(const std::string& prompt) {
        std::cout << prompt << std::endl;
        std::string answer;
        std::getline(std::cin, answer);
        return answer;
    }

    static std::string promptSpaced(const std::string& prmpt) {
        std::string answer = prompt(prmpt);
        std::cout << std::endl;
        return answer;
    }

    static void printSpace() {
        std::cout << std::endl;
    }

    static std::string promptWithChoices(const std::string& prompt, const std::vector<std::string>& choices) {
        std::cout << prompt << std::endl;
        return getValidAnswer(choices);
    }

    static std::string promptWithChoicesSpaced(const std::string& prompt, const std::vector<std::string>& choices) {
        std::string choice = promptWithChoices(prompt, choices);
        std::cout << std::endl;
        return choice;
    }

private:
    static std::string getValidAnswer(const std::vector<std::string>& choices) {
        std::string chosenAnswer;
        while (true) {
            std::cout << formatAnswers(choices) << std::endl;
            std::string userInput;
            std::getline(std::cin, userInput);
            chosenAnswer = parseAnswer(userInput, choices);
            if (!chosenAnswer.empty()) {
                break;
            }
            std::cout << "\nIncorrect choice. Please enter the corresponding number or the choice text." << std::endl;
        }
        return chosenAnswer;
    }

    static std::string parseAnswer(const std::string& input, const std::vector<std::string>& choices) {
        for (const auto& answer : choices) {
            if (input == answer) {
                return answer;
            }
        }
        return "";
    }

    static std::string formatAnswers(const std::vector<std::string>& answers) {
        std::string validAnswers;
        for (size_t i = 0; i < answers.size(); ++i) {
            validAnswers += std::to_string(i + 1) + ". " + answers[i];
            if (i != answers.size() - 1) {
                validAnswers += '\n';
            }
        }
        return validAnswers;
    }
};

int main() {
    Console::print("Hello, world!");
    std::string input = Console::prompt("Enter something:");
    Console::print("You entered: " + input);

    std::vector<std::string> choices = {"Choice 1", "Choice 2", "Choice 3"};
    std::string chosen = Console::promptWithChoices("Choose an option:", choices);
    Console::print("You chose: " + chosen);

    return 0;
}
