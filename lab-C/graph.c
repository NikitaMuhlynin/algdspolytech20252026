#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#pragma warning(disable: 4996)

void initialize_graph(Graph* graph, int vertices) {
    if (graph == NULL || vertices <= 0 || vertices > MAX_VERTICES) {
        return;
    }

    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->matrix[i][j] = 0;
        }
    }
}

int is_valid_vertex(const Graph* graph, int vertex) {
    return (graph != NULL && vertex >= 1 && vertex <= graph->vertices);
}

int add_edge(Graph* graph, int v1, int v2) {
    if (graph == NULL || !is_valid_vertex(graph, v1) || !is_valid_vertex(graph, v2)) {
        return 0;
    }

    graph->matrix[v1 - 1][v2 - 1] = 1;
    graph->matrix[v2 - 1][v1 - 1] = 1;
    return 1;
}

int get_edge(const Graph* graph, int v1, int v2) {
    if (graph == NULL || !is_valid_vertex(graph, v1) || !is_valid_vertex(graph, v2)) {
        return -1;
    }

    return graph->matrix[v1 - 1][v2 - 1];
}

int count_edges(const Graph* graph) {
    if (graph == NULL) return 0;

    int count = 0;
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = i + 1; j < graph->vertices; j++) {
            if (graph->matrix[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}

int read_adjacency_list(const char* filename, Graph* graph) {
    if (filename == NULL || graph == NULL) {
        return 0;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    int vertices;
    if (fscanf(file, "%d", &vertices) != 1) {
        fclose(file);
        return 0;
    }

    fgetc(file);

    if (vertices <= 0 || vertices > MAX_VERTICES) {
        fclose(file);
        return 0;
    }

    initialize_graph(graph, vertices);

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ":");
        if (token == NULL) continue;

        int vertex = atoi(token);
        if (!is_valid_vertex(graph, vertex)) continue;

        token = strtok(NULL, ":");
        if (token != NULL) {
            char* neighbor_token = strtok(token, " \n");
            while (neighbor_token != NULL) {
                int neighbor = atoi(neighbor_token);
                if (is_valid_vertex(graph, neighbor)) {
                    add_edge(graph, vertex, neighbor);
                }
                neighbor_token = strtok(NULL, " \n");
            }
        }
    }

    fclose(file);
    return 1;
}

void print_adjacency_matrix(const Graph* graph) {
    if (graph == NULL) return;

    printf("Матрица смежностей (%d вершин):\n", graph->vertices);
    printf("   ");
    for (int i = 0; i < graph->vertices; i++) {
        printf("%2d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < graph->vertices; i++) {
        printf("%2d:", i + 1);
        for (int j = 0; j < graph->vertices; j++) {
            printf("%2d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

int save_adjacency_matrix(const char* filename, const Graph* graph) {
    if (filename == NULL || graph == NULL) {
        return 0;
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return 0;
    }

    fprintf(file, "Матрица смежностей (%d вершин):\n", graph->vertices);
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            fprintf(file, "%d ", graph->matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 1;
}