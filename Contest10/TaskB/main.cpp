#include <iostream>

void findCountBridges(int count_islands, int count_bridges) {
    int color = 1;
    int counter_different_colors = 0;
    int counter_bridges = 0;
    int counter_painted_bridges = 0;
    int painted_bridges[200000]{};

    while (counter_bridges < count_bridges) {
        int side_first_island;
        int side_second_island;
        std::cin >> side_first_island >> side_second_island;

        if (side_first_island == side_second_island) {
            ++counter_bridges;
            continue;
        }

        if (painted_bridges[side_first_island] + painted_bridges[side_second_island] == 0) {
            painted_bridges[side_first_island] = color;
            painted_bridges[side_second_island] = color;
            counter_painted_bridges += 2;
            ++color;
            ++counter_different_colors;
        } else if (painted_bridges[side_first_island] == painted_bridges[side_second_island]) {
            ++counter_bridges;
            continue;
        } else if (painted_bridges[side_first_island] == 0) {
            painted_bridges[side_first_island] = painted_bridges[side_second_island];
            ++counter_painted_bridges;
        } else if (painted_bridges[side_second_island] == 0) {
            painted_bridges[side_second_island] = painted_bridges[side_first_island];
            ++counter_painted_bridges;
        } else {
            int color_first_side = painted_bridges[side_first_island];
            int color_second_side = painted_bridges[side_second_island];

            for (int i = 0; i < count_islands; ++i) {
                if (painted_bridges[i] == color_first_side) {
                    painted_bridges[i] = color_second_side;
                }
            }
            --counter_different_colors;
        }

        if (counter_painted_bridges == count_islands && counter_different_colors == 1) {
            std::cout << counter_bridges + 1;
            return;
        }

        ++counter_bridges;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int count_islands;
    int count_bridges;
    std::cin >> count_islands >> count_bridges;

    if (count_islands == 1) {
        std::cout << 0;
        return 0;
    }

    findCountBridges(count_islands, count_bridges);
    return 0;
}
