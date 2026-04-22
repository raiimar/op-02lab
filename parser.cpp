#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "parser.h"

#define MAX_FIELDS 7
#define BUFFER_SIZE 512

// Проверка: строка является числом
static int is_valid_number(const char* str) {
    int result = 1;
    int i = 0;
    int hasDot = 0;

    if (str == NULL || str[0] == '\0') {
        result = 0;
    } else {
        if (str[i] == '-' || str[i] == '+') {
            i++;
        }

        for (; str[i] != '\0'; i++) {
            if (str[i] == '.') {
                if (hasDot) {
                    result = 0;
                }
                hasDot = 1;
            } else if (!isdigit((unsigned char)str[i])) {
                result = 0;
            }
        }
    }

    return result;
}

// Парсинг строки CSV
void parse_line(const char* line, DataRow* outRow, ParseStatus* status) {
    char buffer[BUFFER_SIZE];
    char* token = NULL;
    char* fields[MAX_FIELDS];
    int fieldCount = 0;
    int error = 0;
    int i = 0;

    if (status != NULL) {
        *status = PARSE_ERROR;
    }

    if (line != NULL && outRow != NULL && status != NULL) {

        // копируем строку (strtok изменяет её)
        strncpy(buffer, line, BUFFER_SIZE - 1);
        buffer[BUFFER_SIZE - 1] = '\0';

        // удаляем перевод строки
        buffer[strcspn(buffer, "\r\n")] = '\0';

        // разбиваем строку
        token = strtok(buffer, ",");

        while (token != NULL && fieldCount < MAX_FIELDS) {
            fields[fieldCount++] = token;
            token = strtok(NULL, ",");
        }

        // проверка количества полей
        if (fieldCount != MAX_FIELDS) {
            error = 1;
        }

        // проверка на пустые поля
        for (i = 0; i < fieldCount && !error; i++) {
            if (fields[i] == NULL || fields[i][0] == '\0') {
                error = 1;
            }
        }

        // проверка числовых полей
        if (!error) {
            for (i = 0; i < MAX_FIELDS; i++) {
                if (i != 1) { // поле region — строка
                    if (!is_valid_number(fields[i])) {
                        error = 1;
                    }
                }
            }
        }

        // если всё ок — заполняем структуру
        if (!error) {
            outRow->year = atoi(fields[0]);

            strncpy(outRow->region, fields[1], REGION_NAME_LENGTH - 1);
            outRow->region[REGION_NAME_LENGTH - 1] = '\0';

            outRow->natural_population_growth = atof(fields[2]);
            outRow->birth_rate = atof(fields[3]);
            outRow->death_rate = atof(fields[4]);
            outRow->general_demographic_weight = atof(fields[5]);
            outRow->urbanization = atof(fields[6]);

            *status = PARSE_OK;
        } else {
            *status = PARSE_ERROR;
        }
    }
}
