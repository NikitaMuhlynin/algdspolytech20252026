#include <gtest/gtest.h>
#include <fstream>
#include "graph.h"

class GraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ofstream file("test_graph.txt");
        file << "3\n";
        file << "1:2 3\n";
        file << "2:1\n";
        file << "3:1\n";
        file.close();
    }

    void TearDown() override {
        remove("test_graph.txt");
        remove("test_output.txt");
    }

    Graph graph;
};

// Тест 1: Инициализация графа
TEST_F(GraphTest, InitializeGraph) {
    initialize_graph(&graph, 5);
    EXPECT_EQ(graph.vertices, 5);
    EXPECT_EQ(get_edge(&graph, 1, 2), 0);
}

// Тест 2: Добавление ребра
TEST_F(GraphTest, AddEdge) {
    initialize_graph(&graph, 3);
    EXPECT_TRUE(add_edge(&graph, 1, 2));
    EXPECT_EQ(get_edge(&graph, 1, 2), 1);
    EXPECT_EQ(get_edge(&graph, 2, 1), 1); // Проверка симметричности
}

// Тест 3: Добавление невалидного ребра
TEST_F(GraphTest, AddInvalidEdge) {
    initialize_graph(&graph, 3);
    EXPECT_FALSE(add_edge(&graph, 0, 2));  // Вершина 0 невалидна
    EXPECT_FALSE(add_edge(&graph, 1, 5));  // Вершина 5 невалидна
    EXPECT_FALSE(add_edge(&graph, -1, 2)); // Отрицательная вершина
}

// Тест 4: Проверка валидности вершин
TEST_F(GraphTest, IsValidVertex) {
    initialize_graph(&graph, 3);
    EXPECT_TRUE(is_valid_vertex(&graph, 1));
    EXPECT_TRUE(is_valid_vertex(&graph, 3));
    EXPECT_FALSE(is_valid_vertex(&graph, 0));
    EXPECT_FALSE(is_valid_vertex(&graph, 4));
    EXPECT_FALSE(is_valid_vertex(NULL, 1)); // NULL граф
}

// Тест 5: Чтение из файла
TEST_F(GraphTest, ReadFromFile) {
    EXPECT_TRUE(read_adjacency_list("test_graph.txt", &graph));
    EXPECT_EQ(graph.vertices, 3);
    EXPECT_EQ(get_edge(&graph, 1, 2), 1);
    EXPECT_EQ(get_edge(&graph, 1, 3), 1);
    EXPECT_EQ(get_edge(&graph, 2, 3), 0); // Нет прямого соединения
}

// Тест 6: Чтение несуществующего файла
TEST_F(GraphTest, ReadNonExistentFile) {
    EXPECT_FALSE(read_adjacency_list("non_existent.txt", &graph));
}

// Тест 7: Подсчет ребер
TEST_F(GraphTest, CountEdges) {
    initialize_graph(&graph, 3);
    EXPECT_EQ(count_edges(&graph), 0);

    add_edge(&graph, 1, 2);
    EXPECT_EQ(count_edges(&graph), 1);

    add_edge(&graph, 1, 3);
    EXPECT_EQ(count_edges(&graph), 2);
}

// Тест 8: Получение ребра
TEST_F(GraphTest, GetEdge) {
    initialize_graph(&graph, 3);
    add_edge(&graph, 1, 2);

    EXPECT_EQ(get_edge(&graph, 1, 2), 1);
    EXPECT_EQ(get_edge(&graph, 2, 1), 1);
    EXPECT_EQ(get_edge(&graph, 1, 3), 0);
    EXPECT_EQ(get_edge(&graph, 3, 3), 0); // Петля отсутствует
}

// Тест 9: Сохранение матрицы
TEST_F(GraphTest, SaveMatrix) {
    initialize_graph(&graph, 2);
    add_edge(&graph, 1, 2);
    EXPECT_TRUE(save_adjacency_matrix("test_output.txt", &graph));

    // Проверяем что файл создан
    std::ifstream file("test_output.txt");
    EXPECT_TRUE(file.good());
}

// Тест 10: Работа с NULL
TEST_F(GraphTest, NullSafety) {
    EXPECT_FALSE(read_adjacency_list(NULL, &graph));
    EXPECT_FALSE(read_adjacency_list("test_graph.txt", NULL));
    EXPECT_FALSE(save_adjacency_matrix(NULL, &graph));
    EXPECT_FALSE(save_adjacency_matrix("test.txt", NULL));

    print_adjacency_matrix(NULL); // Не должно падать
}

// Тест 11: Симметричность матрицы для неориентированного графа
TEST_F(GraphTest, MatrixSymmetry) {
    read_adjacency_list("test_graph.txt", &graph);

    for (int i = 0; i < graph.vertices; i++) {
        for (int j = 0; j < graph.vertices; j++) {
            EXPECT_EQ(graph.matrix[i][j], graph.matrix[j][i]);
        }
    }
}

// Тест 12: Большой граф
TEST_F(GraphTest, LargeGraph) {
    initialize_graph(&graph, MAX_VERTICES);
    EXPECT_TRUE(add_edge(&graph, 1, MAX_VERTICES));
    EXPECT_EQ(get_edge(&graph, 1, MAX_VERTICES), 1);
}