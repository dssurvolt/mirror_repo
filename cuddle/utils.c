/*
** EPITECH PROJECT, 2024
** Nouveau dossier [WSL: kali-linux]
** File description:
** utils.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"

dataframe_shape_t df_shape(dataframe_t *df) {
    return (dataframe_shape_t){df->nb_rows, df->nb_columns};
}

void df_info(dataframe_t *df) {
    if (!df) return;
    printf("%d columns:\n", df->nb_columns);
    for (int c = 0; c < df->nb_columns; c++) {
        printf("- %s: ", df->columns[c].name);
        switch (df->columns[c].type) {
            case BOOL: printf("bool\n"); break;
            case INT: printf("int\n"); break;
            case UINT: printf("unsigned int\n"); break;
            case FLOAT: printf("float\n"); break;
            case STRING: printf("string\n"); break;
            default: printf("unknown\n");
        }
    }
}

void df_describe(dataframe_t *df) {
    if (!df) return;
    
    for (int c = 0; c < df->nb_columns; c++) {
        if (df->columns[c].type == INT || df->columns[c].type == FLOAT) {
            int count = df->nb_rows;
            double sum = 0, min = atof(df->columns[c].values[0]), max = min;
            
            for (int r = 0; r < df->nb_rows; r++) {
                double val = atof(df->columns[c].values[r]);
                sum += val;
                if (val < min) min = val;
                if (val > max) max = val;
            }
            
            double mean = sum / count;
            printf("Column: %s\n", df->columns[c].name);
            printf("Count: %d\nMean: %.2f\nMin: %.2f\nMax: %.2f\n", count, mean, min, max);
        }
    }
}

void df_free(dataframe_t *df) {
    if (!df) return;

    for (int c = 0; c < df->nb_columns; c++) {
        free(df->columns[c].name);
        for (int r = 0; r < df->nb_rows; r++) {
            free(df->columns[c].values[r]);
        }
        free(df->columns[c].values);
    }
    free(df->columns);
    free(df);
}
