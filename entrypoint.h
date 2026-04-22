#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"

typedef enum {
    LOAD_DATA,
    CALCULATE_METRICS,
    INITIALIZATION,
} Operation;

// Параметры операций
typedef struct {
    char filePath[256];
    char region[128];
    int columnIndex;
} AppParams;

// Единая точка входа
void doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
