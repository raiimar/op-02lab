#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"

// Инициализация контекста приложения
void logic_init(AppContext* context);

// Загрузка данных из файла
// filePath — путь к CSV файлу
void logic_load_data(AppContext* context, const char* filePath);

// Расчёт статистических метрик
// region        — название региона (может быть пустым)
// columnIndex   — номер колонки (начиная с 1)
void logic_calculate_metrics(AppContext* context, const char* region, int columnIndex);

// Очистка данных (освобождение памяти)
void logic_clear_data(AppContext* context);

#endif // LOGIC_H
