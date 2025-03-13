/*
** EPITECH PROJECT, 2024
** Nouveau dossier [WSL: kali-linux]
** File description:
** dataframe.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"

dataframe_t *df_read_csv(const char *filename, const char *separator) {
    if (!separator) separator = ",";

    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return NULL;
    }

    dataframe_t *df = malloc(sizeof(dataframe_t));
    if (!df) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    df->nb_rows = 0;
    df->nb_columns = 0;
    df->columns = NULL;

    char line[1024];
    if (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, separator);
        while (token) {
            df->nb_columns++;
            df->columns = realloc(df->columns, df->nb_columns * sizeof(column_t));
            df->columns[df->nb_columns - 1].name = strdup(token);
            df->columns[df->nb_columns - 1].values = NULL;
            df->columns[df->nb_columns - 1].type = UNDEFINED;
            token = strtok(NULL, separator);
        }
    }

    while (fgets(line, sizeof(line), file)) {
        df->nb_rows++;
        char *token = strtok(line, separator);
        for (int i = 0; i < df->nb_columns; i++) {
            if (token) {
                df->columns[i].values = realloc(df->columns[i].values, df->nb_rows * sizeof(void *));
                df->columns[i].values[df->nb_rows - 1] = strdup(token);
                token = strtok(NULL, separator);
            }
        }
    }

    fclose(file);
    return df;
}

int df_write_csv(dataframe_t *df, const char *filename) {
    if (!df || !filename) return 84;

    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Cannot write to file %s\n", filename);
        return 84;
    }

    // Écrire les en-têtes
    for (int i = 0; i < df->nb_columns; i++) {
        fprintf(file, "%s%s", df->columns[i].name, (i == df->nb_columns - 1) ? "\n" : ",");
    }

    // Écrire les données
    for (int r = 0; r < df->nb_rows; r++) {
        for (int c = 0; c < df->nb_columns; c++) {
            fprintf(file, "%s%s", (char *)df->columns[c].values[r], (c == df->nb_columns - 1) ? "\n" : ",");
        }
    }

    fclose(file);
    return 0;
}
