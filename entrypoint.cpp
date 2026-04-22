#include "entrypoint.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>

void doOperation(Operation operation, AppContext* context, AppParams* params) {
    if (context != NULL) {

        switch (operation) {

        case INITIALIZATION:
            logic_init(context);
            break;

        case LOAD_DATA:
            if (params != NULL) {
                logic_load_data(context, params->filePath);
            } else {
                context->status = ERROR_INVALID_PARAMS;
            }
            break;

        case CALCULATE_METRICS:
            if (params != NULL) {
                logic_calculate_metrics(context, params->region, params->columnIndex);
            } else {
                context->status = ERROR_INVALID_PARAMS;
            }
            break;

        default:
            context->status = ERROR_INVALID_PARAMS;
            break;
        }
    }

}
