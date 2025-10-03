#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#define MAX_DATE_LENGTH 11

typedef struct {
    char date[MAX_DATE_LENGTH];
    float avg_temp;
} DayData;

typedef struct {
    DayData* data;
    int size;
    int capacity;
} TemperatureList;

TemperatureList* create_temperature_list();
void destroy_temperature_list(TemperatureList* list);

int add_temperature(TemperatureList* list, const char* date, float temp);
int parse_temperature_line(const char* line, char* date, float* temp);
void sort_temperatures(TemperatureList* list);

int count_negative_temperatures(const TemperatureList* list);
int find_temperature(const TemperatureList* list, float temp);

void print_negative_temperatures(const TemperatureList* list);
float find_min_temperature(const TemperatureList* list);
float find_max_temperature(const TemperatureList* list);

#endif