#include "iterator.h"
#include <stdio.h>
#include <stdlib.h>


// Создание итератора (устанавливаем на начало списка)
Iterator iterator_create(List* list) {
    Iterator it;

    it.current = NULL;

    if (list != NULL) {
        it.current = list->head;
    }

    return it;

}

// Проверка наличия текущего элемента
int iterator_has_next(Iterator* it) {
    int result = 0;

    if (it != NULL && it->current != NULL) {
        result = 1;
    }

    return result;

}

// Переход к следующему элементу
void iterator_next(Iterator* it) {
    if (it != NULL && it->current != NULL) {
        it->current = it->current->next;
    }
}

// Получение текущего элемента
DataRow* iterator_get(Iterator* it) {
    DataRow* data = NULL;

    if (it != NULL && it->current != NULL) {
        data = &(it->current->data);
    }

    return data;

}
