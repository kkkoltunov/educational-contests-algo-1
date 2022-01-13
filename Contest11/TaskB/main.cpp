#include <iostream>

struct Edge {
    Edge() {
    }

    int firstVertex;
    int secondVertex;
    int distance;
};

int find(int index, int *parent) {
    if (index == parent[index]) {
        return index;
    }

    return parent[index] = find(parent[index], parent);
}

bool unions(int first_node, int second_node, int *parent) {
    first_node = find(first_node, parent);
    second_node = find(second_node, parent);

    if (first_node == second_node) {
        return false;
    }

    parent[second_node] = first_node;
    return true;
}

void mySwap(Edge *first, Edge *second) {
    Edge temp = *first;
    *first = *second;
    *second = temp;
}

int partition(Edge *array, int low, int high) {
    int pivot = array[high].distance;
    int index = (low - 1);

    for (int j = low; j <= high - 1; ++j) {
        if (array[j].distance < pivot) {
            ++index;
            mySwap(&array[index], &array[j]);
        }
    }
    mySwap(&array[index + 1], &array[high]);
    return (index + 1);
}

void quickSort(Edge *array, int low, int high) {
    if (low < high) {
        int middle = partition(array, low, high);
        quickSort(array, low, middle - 1);
        quickSort(array, middle + 1, high);
    }
}

void findSecondMinimum(Edge *edges, int *parent, int *already_use_edges, int *answers_second_min,
                       int counter_use_edges, int count_edges, int count_vertex) {
    for (int index = 0; index < counter_use_edges; ++index) {
        for (int j = 1; j <= count_vertex; ++j) {
            parent[j] = j;
        }
        int second_result = 0;
        int counter_connect_vertex = 0;

        for (int second_index = 0; second_index < count_edges; ++second_index) {
            if (already_use_edges[index] == second_index) {
                continue;
            }

            if (unions(edges[second_index].firstVertex, edges[second_index].secondVertex, parent)) {
                second_result += edges[second_index].distance;
                ++counter_connect_vertex;
            }

            if (counter_connect_vertex + 1 == count_vertex) {
                break;
            }
        }
        answers_second_min[index] = second_result;
    }
}

void findFirstMinimum(Edge *edges, int *parent, int count_edges, int count_vertex) {
    int counter_use_edges = 0;
    int already_use_edges[2001]{};
    int answers_second_min[2001]{};

    quickSort(edges, 0, count_edges - 1);

    int first_result = 0;
    int counter_connect_vertex = 0;
    for (int i = 0; i < count_edges; ++i) {
        if (unions(edges[i].firstVertex, edges[i].secondVertex, parent)) {
            already_use_edges[counter_use_edges++] = i;
            first_result += edges[i].distance;
            ++counter_connect_vertex;
        }

        if (counter_connect_vertex + 1 == count_vertex) {
            break;
        }
    }

    findSecondMinimum(edges, parent, already_use_edges, answers_second_min, counter_use_edges,
                      count_edges, count_vertex);

    int index_second_minimum = 0;
    int second_minimum = 2147483647;

    for (int index = 0; index < counter_use_edges; ++index) {
        if (answers_second_min[index] >= first_result &&
            answers_second_min[index] < second_minimum) {
            index_second_minimum = index;
            second_minimum = answers_second_min[index];
        }
    }

    std::cout << first_result << " " << answers_second_min[index_second_minimum];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Edge edges[2001]{};
    int parent[101]{};

    int count_vertex;
    int count_edges;
    std::cin >> count_vertex >> count_edges;

    for (int i = 1; i <= count_vertex; ++i) {
        parent[i] = i;
    }

    for (int i = 0; i < count_edges; ++i) {
        std::cin >> edges[i].firstVertex >> edges[i].secondVertex >> edges[i].distance;
    }

    findFirstMinimum(edges, parent, count_edges, count_vertex);
    return 0;
}
