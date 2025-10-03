#include <gtest/gtest.h>
#include <cstring>
#include "temperature.h"

// Вспомогательные функции для тестов
TemperatureList* create_sample_list() {
    TemperatureList* list = create_temperature_list();
    add_temperature(list, "2024-01-15", -5.0f);
    add_temperature(list, "2024-02-20", 10.0f);
    add_temperature(list, "2024-03-10", 15.0f);
    return list;
}

// Тест 1: Создание списка
TEST(TemperatureTest, CreateTemperatureList_ValidCreation_no1) {
    TemperatureList* list = create_temperature_list();
    ASSERT_NE(list, nullptr);
    EXPECT_EQ(list->size, 0);
    EXPECT_GE(list->capacity, 1);
    destroy_temperature_list(list);
}

// Тест 2: Добавление в пустой список
TEST(TemperatureTest, AddTemperature_ToEmptyList_ReturnTrue_no2) {
    TemperatureList* list = create_temperature_list();
    int result = add_temperature(list, "2024-01-01", 5.0f);
    EXPECT_TRUE(result);
    EXPECT_EQ(list->size, 1);
    EXPECT_STREQ(list->data[0].date, "2024-01-01");
    EXPECT_FLOAT_EQ(list->data[0].avg_temp, 5.0f);
    destroy_temperature_list(list);
}

// Тест 3: Добавление с невалидными параметрами
TEST(TemperatureTest, AddTemperature_NullParameters_ReturnFalse_no3) {
    TemperatureList* list = create_temperature_list();
    int result = add_temperature(nullptr, "2024-01-01", 5.0f);
    EXPECT_FALSE(result);

    result = add_temperature(list, nullptr, 5.0f);
    EXPECT_FALSE(result);
    destroy_temperature_list(list);
}

// Тест 4: Парсинг валидной строки
TEST(TemperatureTest, ParseTemperatureLine_ValidLine_ReturnTrue_no4) {
    char date[MAX_DATE_LENGTH];
    float temp;
    const char* valid_line = "2024-01-15 -5.5";
    int result = parse_temperature_line(valid_line, date, &temp);
    EXPECT_TRUE(result);
    EXPECT_STREQ(date, "2024-01-15");
    EXPECT_FLOAT_EQ(temp, -5.5f);
}

// Тест 5: Парсинг невалидной строки
TEST(TemperatureTest, ParseTemperatureLine_InvalidLine_ReturnFalse_no5) {
    char date[MAX_DATE_LENGTH];
    float temp;
    const char* invalid_line = "invalid data";
    int result = parse_temperature_line(invalid_line, date, &temp);
    EXPECT_FALSE(result);
}

// Тест 6: Подсчет отрицательных температур
TEST(TemperatureTest, CountNegativeTemperatures_MixedTemperatures_ReturnCorrectCount_no6) {
    TemperatureList* list = create_sample_list();
    int count = count_negative_temperatures(list);
    EXPECT_EQ(count, 1);
    destroy_temperature_list(list);
}

// Тест 7: Подсчет в пустом списке
TEST(TemperatureTest, CountNegativeTemperatures_EmptyList_ReturnZero_no7) {
    TemperatureList* list = create_temperature_list();
    int count = count_negative_temperatures(list);
    EXPECT_EQ(count, 0);
    destroy_temperature_list(list);
}

// Тест 8: Поиск существующей температуры
TEST(TemperatureTest, FindTemperature_ExistingTemperature_ReturnTrue_no8) {
    TemperatureList* list = create_sample_list();
    int found = find_temperature(list, 10.0f);
    EXPECT_TRUE(found);
    destroy_temperature_list(list);
}

// Тест 9: Поиск несуществующей температуры
TEST(TemperatureTest, FindTemperature_NonExistingTemperature_ReturnFalse_no9) {
    TemperatureList* list = create_sample_list();
    int found = find_temperature(list, 999.0f);
    EXPECT_FALSE(found);
    destroy_temperature_list(list);
}

// Тест 10: Сортировка температур
TEST(TemperatureTest, SortTemperatures_UnsortedList_SortedCorrectly_no10) {
    TemperatureList* list = create_temperature_list();
    add_temperature(list, "2024-03-01", 15.0f);
    add_temperature(list, "2024-01-01", -5.0f);
    add_temperature(list, "2024-02-01", 10.0f);

    sort_temperatures(list);

    EXPECT_FLOAT_EQ(list->data[0].avg_temp, -5.0f);
    EXPECT_FLOAT_EQ(list->data[1].avg_temp, 10.0f);
    EXPECT_FLOAT_EQ(list->data[2].avg_temp, 15.0f);
    destroy_temperature_list(list);
}

// Тест 11: Поиск минимальной температуры
TEST(TemperatureTest, FindMinTemperature_ValidList_ReturnCorrectValue_no11) {
    TemperatureList* list = create_sample_list();
    float min_temp = find_min_temperature(list);
    EXPECT_FLOAT_EQ(min_temp, -5.0f);
    destroy_temperature_list(list);
}

// Тест 12: Поиск максимальной температуры
TEST(TemperatureTest, FindMaxTemperature_ValidList_ReturnCorrectValue_no12) {
    TemperatureList* list = create_sample_list();
    float max_temp = find_max_temperature(list);
    EXPECT_FLOAT_EQ(max_temp, 15.0f);
    destroy_temperature_list(list);
}

// Тест 13: Расширение capacity при добавлении
TEST(TemperatureTest, AddTemperature_ExceedCapacity_ResizeSuccessfully_no13) {
    TemperatureList* list = create_temperature_list();
    // Добавляем больше элементов, чем начальная capacity
    for (int i = 0; i < 15; i++) {
        char date[MAX_DATE_LENGTH];
        snprintf(date, sizeof(date), "2024-01-%02d", i + 1);
        int result = add_temperature(list, date, (float)i);
        EXPECT_TRUE(result);
    }
    EXPECT_GE(list->capacity, 15);
    EXPECT_EQ(list->size, 15);
    destroy_temperature_list(list);
}