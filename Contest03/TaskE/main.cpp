/*E. Спиральное заполнение матрицы*/

#include <iostream>
#include <vector>

int64_t findSumInTriangle(const std::vector<std::vector<int64_t>> &matrix) {
    int64_t counter = 0;
    int counter_lines = 0;

    bool restart = false;

    for (unsigned int j = 0, i = 0;; ++j) {
        if (j + 1 == matrix.size()) {
            ++counter_lines;
            restart = true;
        }
        if (counter_lines == matrix.size()) {
            break;
        }
        if (j > i && j < matrix.size() - i - 1) {
            counter += matrix[i][j];
        }
        if (i > j && j > matrix.size() - i - 1) {
            counter += matrix[i][j];
        }

        if (restart) {
            j = -1;
            ++i;
            restart = false;
        }
    }

    return counter;
}

void printResults(const std::vector<std::vector<int64_t>> &matrix) {
    int64_t a = findSumInTriangle(matrix);
    std::cout << a << std::endl;

    if (matrix.size() > 20) {
        return;
    }

    for (unsigned int i = 0; i < matrix.size(); ++i) {
        for (unsigned int j = 0; j < matrix.size(); ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void fillingMatrix(const unsigned int &count_lines_and_columns, int64_t &a1, const int64_t &d) {
    std::vector<std::vector<int64_t>> matrix;

    for (unsigned int i = 0; i < count_lines_and_columns; ++i) {
        matrix.push_back(std::vector<int64_t>(count_lines_and_columns, 0));
    }

    int i = 0;
    int j = 0;

    matrix[0][0] = a1;
    a1 += d;

    if (count_lines_and_columns > 1) {
        while (true) {
            if (j == 0 && i != count_lines_and_columns - 1) {
                matrix[++i][j] = a1;
                a1 += d;

                do {
                    matrix[--i][++j] = a1;
                    a1 += d;
                } while (i != 0);
            }

            if (i == 0 && j != count_lines_and_columns - 1) {
                matrix[i][++j] = a1;
                a1 += d;

                do {
                    matrix[++i][--j] = a1;
                    a1 += d;
                } while (j != 0);
            }

            if (i == count_lines_and_columns - 1) {
                matrix[i][++j] = a1;
                a1 += d;

                do {
                    matrix[--i][++j] = a1;
                    a1 += d;
                } while (j != count_lines_and_columns - 1);
            }

            if (j == count_lines_and_columns - 1) {
                matrix[++i][j] = a1;
                a1 += d;

                if (i == j) {
                    break;
                }

                do {
                    matrix[++i][--j] = a1;
                    a1 += d;
                } while (i != count_lines_and_columns - 1);
            }
        }
    }

    printResults(matrix);
}

int main() {
    unsigned int count_lines_and_columns;
    std::cin >> count_lines_and_columns;

    int64_t a1;
    int64_t d;

    std::cin >> a1 >> d;

    fillingMatrix(count_lines_and_columns, a1, d);

    return 0;
}