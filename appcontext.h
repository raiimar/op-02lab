#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "list.h"

#define ERROR_MESSAGE_LENGTH 256

// Статус выполнения операций
typedef enum {
    STATUS_OK,
    ERROR_FILE_OPEN,
    ERROR_FILE_READ,
    ERROR_INVALID_DATA,
    ERROR_INVALID_PARAMS,
    ERROR_EMPTY_RESULT
} Status;

// Контекст приложения
typedef struct AppContext {

    // === ДАННЫЕ ===
    List* dataList;

    // === СТАТИСТИКА ЗАГРУЗКИ ===
    int totalRows;
    int validRows;
    int errorRows;

    // === РЕЗУЛЬТАТЫ ВЫЧИСЛЕНИЙ ===
    double minValue;
    double maxValue;
    double medianValue;

    // === СОСТОЯНИЕ ===
    Status status;
    char errorMessage[ERROR_MESSAGE_LENGTH];

} AppContext;

#endif // APPCONTEXT_H
