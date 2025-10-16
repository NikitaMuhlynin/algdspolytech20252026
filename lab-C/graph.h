#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES 100

typedef struct {
    int vertices;
    int matrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

int read_adjacency_list(const char* filename, Graph* graph);
void print_adjacency_matrix(const Graph* graph);
int save_adjacency_matrix(const char* filename, const Graph* graph);

void initialize_graph(Graph* graph, int vertices);
int add_edge(Graph* graph, int v1, int v2);
int get_edge(const Graph* graph, int v1, int v2);
int count_edges(const Graph* graph);
int is_valid_vertex(const Graph* graph, int vertex);

#endif