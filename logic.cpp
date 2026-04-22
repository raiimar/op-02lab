#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logic.h"
#include "parser.h"
#include "list.h"
#include "iterator.h"

#define LINE_BUFFER_SIZE 512

// Вспомогательная функция: получить значение по индексу колонки
static double get_column_value(DataRow* row, int columnIndex) {
    double value = 0.0;

    if (row != NULL) {
        switch (columnIndex) {
        case 1: value = row->year; break;
        case 2: value = row->natural_population_growth; break;
        case 3: value = row->birth_rate; break;
        case 4: value = row->death_rate; break;
        case 5: value = row->general_demographic_weight; break;
        case 6: value = row->urbanization; break;
        default: value = 0.0; break;
        }
    }

    return value;

}

// Инициализация
void logic_init(AppContext* context) {
    if (context != NULL) {
        context->dataList = list_create();

        context->totalRows = 0;
        context->validRows = 0;
        context->errorRows = 0;

        context->minValue = 0;
        context->maxValue = 0;
        context->medianValue = 0;

        context->status = STATUS_OK;
        context->errorMessage[0] = '\0';
    }

}

// Очистка данных
void logic_clear_data(AppContext* context) {
    if (context != NULL) {
        if (context->dataList != NULL) {
            list_free(context->dataList);
            context->dataList = NULL;
        }
    }
}

// Загрузка данных
void logic_load_data(AppContext* context, const char* filePath) {
    FILE* file = NULL;
    char line[LINE_BUFFER_SIZE];
    DataRow row;
    ParseStatus parseStatus;

    if (context != NULL && filePath != NULL) {

        logic_clear_data(context);
        context->dataList = list_create();

        context->totalRows = 0;
        context->validRows = 0;
        context->errorRows = 0;

        file = fopen(filePath, "r");

        if (file == NULL) {
            context->status = ERROR_FILE_OPEN;
        } else {

            // пропускаем заголовок
            fgets(line, LINE_BUFFER_SIZE, file);

            while (fgets(line, LINE_BUFFER_SIZE, file) != NULL) {
                context->totalRows++;

                parse_line(line, &row, &parseStatus);

                if (parseStatus == PARSE_OK) {
                    list_push_back(context->dataList, row);
                    context->validRows++;
                } else {
                    context->errorRows++;
                }
            }

            fclose(file);
            context->status = STATUS_OK;

            //printf("SIZE: %d\n", context->dataList->size);
        }
    }

}

// Расчёт метрик
void logic_calculate_metrics(AppContext* context, const char* region, int columnIndex) {
    Iterator it;
    DataRow* row = NULL;
    double* values = NULL;
    int count = 0;
    int capacity = 10;
    int i = 0;
    int j = 0;
    double temp = 0.0;
    int error = 0;

    if (context != NULL && context->dataList != NULL) {

        if (columnIndex < 1 || columnIndex > 6) {
            context->status = ERROR_INVALID_PARAMS;
            error = 1;
        }

        if (!error) {

            values = (double*)malloc(sizeof(double) * capacity);

            if (values == NULL) {
                context->status = ERROR_INVALID_DATA;
                error = 1;
            }
        }

        if (!error) {

            it = iterator_create(context->dataList);

            while (iterator_has_next(&it)) {
                row = iterator_get(&it);

                if (row != NULL) {

                    if (region == NULL || region[0] == '\0' || strcmp(row->region, region) == 0) {

                        if (count >= capacity) {
                            capacity *= 2;
                            values = (double*)realloc(values, sizeof(double) * capacity);
                        }

                        values[count++] = get_column_value(row, columnIndex);
                    }
                }

                iterator_next(&it);
            }

            if (count == 0) {
                context->status = ERROR_EMPTY_RESULT;
                error = 1;
            }
        }

        if (!error) {

            // сортировка (пузырьком)
            for (i = 0; i < count - 1; i++) {
                for (j = 0; j < count - i - 1; j++) {
                    if (values[j] > values[j + 1]) {
                        temp = values[j];
                        values[j] = values[j + 1];
                        values[j + 1] = temp;
                    }
                }
            }

            context->minValue = values[0];
            context->maxValue = values[count - 1];

            if (count % 2 == 0) {
                context->medianValue = (values[count / 2 - 1] + values[count / 2]) / 2.0;
            } else {
                context->medianValue = values[count / 2];
            }

            context->status = STATUS_OK;
        }

        if (values != NULL) {
            free(values);
        }
    }
}
