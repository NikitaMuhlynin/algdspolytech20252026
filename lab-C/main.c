#include <stdio.h>
#include <locale.h>
#include "graph.h"

int main() {
    setlocale(LC_CTYPE, "Russian");
    Graph graph;

    if (!read_adjacency_list("graph.txt", &graph)) {
        printf("Ошибка чтения файла graph.txt\n");
        return 1;
    }

    printf("Успешно прочитан граф из файла\n");
    print_adjacency_matrix(&graph);

    if (save_adjacency_matrix("adjacency_matrix.txt", &graph)) {
        printf("Матрица сохранена в файл 'adjacency_matrix.txt'\n");
    }
    else {
        printf("Ошибка сохранения матрицы в файл\n");
    }

    return 0;
}