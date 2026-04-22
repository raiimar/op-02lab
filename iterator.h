#ifndef ITERATOR_H
#define ITERATOR_H

#include "list.h"

typedef struct {
    Node* current;
} Iterator;

// Создание итератора
Iterator iterator_create(List* list);

// Проверка наличия следующего элемента
int iterator_has_next(Iterator* it);

// Переход к следующему
void iterator_next(Iterator* it);

// Получение текущего элемента
DataRow* iterator_get(Iterator* it);

#endif // ITERATOR_H
