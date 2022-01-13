#include <iostream>
#include <map>
#include <vector>
#include <string>

void findCommandWinner(int number_of_tryings, std::map<std::string, int> *commands_score,
                       std::vector<int> *answers) {
    for (int i = 0; i < number_of_tryings; ++i) {
        int number_of_command;
        std::string word;
        std::cin >> number_of_command >> word;
        commands_score->operator[](word) = number_of_command;
    }

    for (auto iterator = commands_score->begin(); iterator != commands_score->end(); ++iterator) {
        ++answers->operator[](iterator->second - 1);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::map<std::string, int> commands_score;

    int number_of_commands;
    int number_of_tryings;
    std::cin >> number_of_commands >> number_of_tryings;
    std::vector<int> answers(number_of_commands);

    findCommandWinner(number_of_tryings, &commands_score, &answers);

    for (int i = 0; i < number_of_commands; ++i) {
        std::cout << answers[i] << " ";
    }

    return 0;
}
