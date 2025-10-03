#include "temperature.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996)

TemperatureList* create_temperature_list() {
    TemperatureList* list = (TemperatureList*)malloc(sizeof(TemperatureList));
    if (!list) return NULL;

    list->capacity = 10;
    list->size = 0;
    list->data = (DayData*)malloc(list->capacity * sizeof(DayData));

    if (!list->data) {
        free(list);
        return NULL;
    }

    return list;
}

void destroy_temperature_list(TemperatureList* list) {
    if (list) {
        free(list->data);
        free(list);
    }
}

int add_temperature(TemperatureList* list, const char* date, float temp) {
    if (!list || !date) return 0;

    if (list->size >= list->capacity) {
        int new_capacity = list->capacity * 2;
        DayData* new_data = (DayData*)realloc(list->data, new_capacity * sizeof(DayData));
        if (!new_data) return 0;

        list->data = new_data;
        list->capacity = new_capacity;
    }

    strncpy(list->data[list->size].date, date, MAX_DATE_LENGTH - 1);
    list->data[list->size].date[MAX_DATE_LENGTH - 1] = '\0';
    list->data[list->size].avg_temp = temp;
    list->size++;

    return 1;
}

int parse_temperature_line(const char* line, char* date, float* temp) {
    if (!line || !date || !temp) return 0;

    return sscanf(line, "%10s %f", date, temp) == 2;
}

int compare_temperatures(const void* a, const void* b) {
    const DayData* day1 = (const DayData*)a;
    const DayData* day2 = (const DayData*)b;

    if (day1->avg_temp < day2->avg_temp) return -1;
    if (day1->avg_temp > day2->avg_temp) return 1;

    return strcmp(day1->date, day2->date);
}

void sort_temperatures(TemperatureList* list) {
    if (!list || list->size <= 1) return;
    qsort(list->data, list->size, sizeof(DayData), compare_temperatures);
}

int count_negative_temperatures(const TemperatureList* list) {
    if (!list) return 0;

    int count = 0;
    for (int i = 0; i < list->size; i++) {
        if (list->data[i].avg_temp < 0) {
            count++;
        }
    }
    return count;
}

int find_temperature(const TemperatureList* list, float temp) {
    if (!list) return 0;

    for (int i = 0; i < list->size; i++) {
        if (list->data[i].avg_temp == temp) {
            return 1;
        }
    }
    return 0;
}

float find_min_temperature(const TemperatureList* list) {
    if (!list || list->size == 0) return 0;

    float min = list->data[0].avg_temp;
    for (int i = 1; i < list->size; i++) {
        if (list->data[i].avg_temp < min) {
            min = list->data[i].avg_temp;
        }
    }
    return min;
}

float find_max_temperature(const TemperatureList* list) {
    if (!list || list->size == 0) return 0;

    float max = list->data[0].avg_temp;
    for (int i = 1; i < list->size; i++) {
        if (list->data[i].avg_temp > max) {
            max = list->data[i].avg_temp;
        }
    }
    return max;
}