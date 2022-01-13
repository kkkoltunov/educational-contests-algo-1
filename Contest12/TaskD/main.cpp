#include <iostream>
#include <vector>

void findRelocation(int number_of_cities, std::vector<int> *cities) {
    for (int index = 0; index < number_of_cities; ++index) {
        int index_city;

        for (index_city = index + 1; index_city < number_of_cities; ++index_city) {
            if (cities->operator[](index_city) < cities->operator[](index)) {
                cities->operator[](index) = index_city;
                break;
            }
        }

        if (index_city == number_of_cities) {
            cities->operator[](index) = -1;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_cities;
    std::cin >> number_of_cities;
    std::vector<int> cities(number_of_cities);

    for (int i = 0; i < number_of_cities; ++i) {
        std::cin >> cities[i];
    }

    findRelocation(number_of_cities, &cities);

    for (int i = 0; i < number_of_cities; ++i) {
        std::cout << cities[i] << " ";
    }

    return 0;
}
