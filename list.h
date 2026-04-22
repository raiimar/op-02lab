#ifndef LIST_H
#define LIST_H

#include "data.h"

// Узел двусвязного списка
typedef struct Node {
    DataRow data;
    struct Node* next;
    struct Node* prev;
} Node;

// Сам список
typedef struct {
    Node* head;
    Node* tail;
    int size;
} List;

// === Работа со списком ===

// Создание списка
List* list_create();

// Добавление элемента в конец
void list_push_back(List* list, DataRow data);

// Очистка списка
void list_clear(List* list);

// Удаление списка
void list_free(List* list);

#endif // LIST_H
