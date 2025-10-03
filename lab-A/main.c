#include <stdio.h>
#include "temperature.h"
#include <locale.h>

#pragma warning(disable: 4996)

int main() {
    setlocale(LC_CTYPE, "Russian");

    TemperatureList* list = create_temperature_list();
    if (!list) {
        printf("Ошибка создания списка\n");
        return 1;
    }

    FILE* file = fopen("temperatures.txt", "r");
    if (!file) {
        printf("Ошибка открытия файла\n");
        destroy_temperature_list(list);
        return 1;
    }

    char line[100];
    char date[MAX_DATE_LENGTH];
    float temp;

    while (fgets(line, sizeof(line), file)) {
        if (parse_temperature_line(line, date, &temp)) {
            add_temperature(list, date, temp);
        }
    }
    fclose(file);

    printf("Прочитано %d записей\n\n", list->size);

    sort_temperatures(list);

    printf("Дни с температурой ниже нуля:\n");
    int negative_count = count_negative_temperatures(list);
    for (int i = 0; i < list->size; i++) {
        if (list->data[i].avg_temp < 0) {
            printf("%s: %.1f°C\n", list->data[i].date, list->data[i].avg_temp);
        }
    }
    printf("Всего: %d дней\n\n", negative_count);

    float search_temp;
    printf("Введите температуру для поиска: ");
    scanf("%f", &search_temp);

    if (find_temperature(list, search_temp)) {
        printf("Температура %.1f°C найдена в списке\n", search_temp);
    }
    else {
        printf("Температура %.1f°C не найдена\n", search_temp);
    }

    destroy_temperature_list(list);
    return 0;
}