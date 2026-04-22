#ifndef DATA_H
#define DATA_H

#define REGION_NAME_LENGTH 128

// Структура, описывающая одну строку CSV файла
typedef struct {
    int year;
    char region[REGION_NAME_LENGTH];

    double natural_population_growth;
    double birth_rate;
    double death_rate;
    double general_demographic_weight;
    double urbanization;

} DataRow;

#endif // DATA_H
