#include <stdlib.h>
#include "list.h"

// Создание списка
List* list_create() {
    List* list = NULL;

    list = (List*)malloc(sizeof(List));
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }

    return list;

}

// Добавление элемента в конец
void list_push_back(List* list, DataRow data) {
    Node* newNode = NULL;

    if (list != NULL) {
        newNode = (Node*)malloc(sizeof(Node));

        if (newNode != NULL) {
            newNode->data = data;
            newNode->next = NULL;
            newNode->prev = list->tail;

            if (list->tail != NULL) {
                list->tail->next = newNode;
            } else {
                list->head = newNode;
            }

            list->tail = newNode;
            list->size++;
        }
    }

}

// Очистка списка (удаление всех узлов)
void list_clear(List* list) {
    Node* current = NULL;
    Node* temp = NULL;

    if (list != NULL) {
        current = list->head;

        while (current != NULL) {
            temp = current;
            current = current->next;
            free(temp);
        }

        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }

}

// Полное удаление списка
void list_free(List* list) {
    if (list != NULL) {
        list_clear(list);
        free(list);
    }
}
