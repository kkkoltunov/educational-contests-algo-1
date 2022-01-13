#include <iostream>
#include <queue>
#include <iterator>

void findWinner(std::queue<int> *first_player, std::queue<int> *second_player) {
    int counter_iterations = 0;

    while (!first_player->empty() && !second_player->empty()) {
        if (counter_iterations > 1e6) {
            std::cout << "botva";
            return;
        }

        int first_player_card = first_player->front();
        int second_player_card = second_player->front();
        first_player->pop();
        second_player->pop();

        if (first_player_card == 0 && second_player_card == 9) {
            first_player->push(first_player_card);
            first_player->push(second_player_card);
        } else if (first_player_card == 9 && second_player_card == 0) {
            second_player->push(first_player_card);
            second_player->push(second_player_card);
        } else if (first_player_card > second_player_card) {
            first_player->push(first_player_card);
            first_player->push(second_player_card);
        } else {
            second_player->push(first_player_card);
            second_player->push(second_player_card);
        }

        ++counter_iterations;

        if (first_player->empty()) {
            std::cout << "second " << counter_iterations;
            return;
        } else if (second_player->empty()) {
            std::cout << "first " << counter_iterations;
            return;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::queue<int> first_player;
    std::queue<int> second_player;

    for (int i = 0; i < 5; ++i) {
        int number;
        std::cin >> number;
        first_player.push(number);
    }

    for (int i = 0; i < 5; ++i) {
        int number;
        std::cin >> number;
        second_player.push(number);
    }

    findWinner(&first_player, &second_player);

    return 0;
}
