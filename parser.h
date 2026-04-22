#ifndef PARSER_H
#define PARSER_H

#include "data.h"

// Результат парсинга строки
typedef enum {
    PARSE_OK,
    PARSE_ERROR
} ParseStatus;

// Парсинг строки CSV в структуру DataRow
// line      — входная строка
// outRow    — результат парсинга
// status    — статус выполнения (успех / ошибка)
void parse_line(const char* line, DataRow* outRow, ParseStatus* status);

#endif // PARSER_H
