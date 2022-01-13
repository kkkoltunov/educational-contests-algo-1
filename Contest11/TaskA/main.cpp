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

void findMinimum(Edge *edges, int *parent, int count_edges, int count_vertex) {
    quickSort(edges, 0, count_edges - 1);

    int result = 0;
    int counter = 0;
    for (int i = 0; i < count_edges; ++i) {
        if (unions(edges[i].firstVertex, edges[i].secondVertex, parent)) {
            result += edges[i].distance;
            ++counter;
        }

        if (counter + 1 == count_vertex) {
            break;
        }
    }
    std::cout << result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Edge edges[100001]{};
    int parent[100001]{};

    int count_vertex;
    int count_edges;
    std::cin >> count_vertex >> count_edges;

    for (int i = 1; i <= count_vertex; ++i) {
        parent[i] = i;
    }

    for (int i = 0; i < count_edges; ++i) {
        std::cin >> edges[i].firstVertex >> edges[i].secondVertex >> edges[i].distance;
    }

    findMinimum(edges, parent, count_edges, count_vertex);
    return 0;
}
