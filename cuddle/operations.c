/*
** EPITECH PROJECT, 2024
** Nouveau dossier [WSL: kali-linux]
** File description:
** operations.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "my.h"

dataframe_t *df_head(dataframe_t *df, int nb_rows) {
    if (!df || nb_rows <= 0 || nb_rows > df->nb_rows) return NULL;

    dataframe_t *new_df = malloc(sizeof(dataframe_t));
    new_df->nb_rows = nb_rows;
    new_df->nb_columns = df->nb_columns;
    new_df->columns = malloc(df->nb_columns * sizeof(column_t));

    for (int c = 0; c < df->nb_columns; c++) {
        new_df->columns[c].name = strdup(df->columns[c].name);
        new_df->columns[c].values = malloc(nb_rows * sizeof(void *));
        for (int r = 0; r < nb_rows; r++) {
            new_df->columns[c].values[r] = strdup(df->columns[c].values[r]);
        }
    }
    return new_df;
}

dataframe_t *df_tail(dataframe_t *df, int nb_rows) {
    if (!df || nb_rows <= 0 || nb_rows > df->nb_rows) return NULL;
    int start = df->nb_rows - nb_rows;
    
    dataframe_t *new_df = malloc(sizeof(dataframe_t));
    new_df->nb_rows = nb_rows;
    new_df->nb_columns = df->nb_columns;
    new_df->columns = malloc(df->nb_columns * sizeof(column_t));

    for (int c = 0; c < df->nb_columns; c++) {
        new_df->columns[c].name = strdup(df->columns[c].name);
        new_df->columns[c].values = malloc(nb_rows * sizeof(void *));
        for (int r = 0; r < nb_rows; r++) {
            new_df->columns[c].values[r] = strdup(df->columns[c].values[start + r]);
        }
    }
    return new_df;
}

dataframe_t *df_filter(dataframe_t *df, const char *column, bool (*filter_func)(void *)) {
    if (!df || !column || !filter_func) return NULL;

    int col_index = -1;
    for (int c = 0; c < df->nb_columns; c++) {
        if (strcmp(df->columns[c].name, column) == 0) {
            col_index = c;
            break;
        }
    }
    if (col_index == -1) return NULL;

    dataframe_t *new_df = malloc(sizeof(dataframe_t));
    new_df->nb_columns = df->nb_columns;
    new_df->columns = malloc(df->nb_columns * sizeof(column_t));
    
    for (int c = 0; c < df->nb_columns; c++) {
        new_df->columns[c].name = strdup(df->columns[c].name);
        new_df->columns[c].values = NULL;
    }

    new_df->nb_rows = 0;
    for (int r = 0; r < df->nb_rows; r++) {
        if (filter_func(df->columns[col_index].values[r])) {
            new_df->nb_rows++;
            for (int c = 0; c < df->nb_columns; c++) {
                new_df->columns[c].values = realloc(new_df->columns[c].values, new_df->nb_rows * sizeof(void *));
                new_df->columns[c].values[new_df->nb_rows - 1] = strdup(df->columns[c].values[r]);
            }
        }
    }
    return new_df;
}

int get_column_index(dataframe_t *df, const char *column) {
    for (int c = 0; c < df->nb_columns; c++) {
        if (strcmp(df->columns[c].name, column) == 0) return c;
    }
    return -1;
}

int compare_values(const void *a, const void *b, void *arg) {
    column_t *col = (column_t *)arg;
    int indexA = *(int *)a;
    int indexB = *(int *)b;
    return strcmp((char *)col->values[indexA], (char *)col->values[indexB]);
}

dataframe_t *df_sort(dataframe_t *df, const char *column, bool (*sort_func)(void *, void *)) {
    if (!df || !column || !sort_func) return NULL;

    int col_index = get_column_index(df, column);
    if (col_index == -1) return NULL;

    dataframe_t *sorted_df = malloc(sizeof(dataframe_t));
    sorted_df->nb_rows = df->nb_rows;
    sorted_df->nb_columns = df->nb_columns;
    sorted_df->columns = malloc(df->nb_columns * sizeof(column_t));

    int *indices = malloc(df->nb_rows * sizeof(int));
    for (int i = 0; i < df->nb_rows; i++) indices[i] = i;

    qsort_r(indices, df->nb_rows, sizeof(int), compare_values, &df->columns[col_index]);

    for (int c = 0; c < df->nb_columns; c++) {
        sorted_df->columns[c].name = strdup(df->columns[c].name);
        sorted_df->columns[c].values = malloc(df->nb_rows * sizeof(void *));
        for (int r = 0; r < df->nb_rows; r++) {
            sorted_df->columns[c].values[r] = strdup(df->columns[c].values[indices[r]]);
        }
    }

    free(indices);
    return sorted_df;
}

dataframe_t *df_groupby(dataframe_t *df, const char *group_by, const char **to_aggregate, void *(*agg_func)(void **, int)) {
    if (!df || !group_by || !to_aggregate || !agg_func) return NULL;

    int group_col_idx = get_column_index(df, group_by);
    if (group_col_idx == -1) return NULL;

    dataframe_t *grouped_df = malloc(sizeof(dataframe_t));
    grouped_df->nb_columns = 1;
    grouped_df->columns = malloc(sizeof(column_t));
    grouped_df->columns[0].name = strdup(group_by);
    grouped_df->columns[0].values = NULL;

    int *group_counts = malloc(df->nb_rows * sizeof(int));
    char **unique_groups = malloc(df->nb_rows * sizeof(char *));
    int unique_count = 0;

    for (int r = 0; r < df->nb_rows; r++) {
        char *value = df->columns[group_col_idx].values[r];

        int found = -1;
        for (int i = 0; i < unique_count; i++) {
            if (strcmp(unique_groups[i], value) == 0) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            unique_groups[unique_count] = strdup(value);
            group_counts[unique_count] = 1;
            unique_count++;
        } else {
            group_counts[found]++;
        }
    }

    grouped_df->nb_rows = unique_count;
    grouped_df->columns[0].values = malloc(unique_count * sizeof(void *));
    for (int i = 0; i < unique_count; i++) {
        grouped_df->columns[0].values[i] = unique_groups[i];
    }

    for (int a = 0; to_aggregate[a] != NULL; a++) {
        int agg_col_idx = get_column_index(df, to_aggregate[a]);
        if (agg_col_idx == -1) continue;

        grouped_df->nb_columns++;
        grouped_df->columns = realloc(grouped_df->columns, grouped_df->nb_columns * sizeof(column_t));
        grouped_df->columns[grouped_df->nb_columns - 1].name = strdup(to_aggregate[a]);
        grouped_df->columns[grouped_df->nb_columns - 1].values = malloc(unique_count * sizeof(void *));

        for (int i = 0; i < unique_count; i++) {
            void **values = malloc(group_counts[i] * sizeof(void *));
            int index = 0;
            for (int r = 0; r < df->nb_rows; r++) {
                if (strcmp(df->columns[group_col_idx].values[r], unique_groups[i]) == 0) {
                    values[index++] = df->columns[agg_col_idx].values[r];
                }
            }
            grouped_df->columns[grouped_df->nb_columns - 1].values[i] = agg_func(values, group_counts[i]);
            free(values);
        }
    }

    free(unique_groups);
    free(group_counts);
    return grouped_df;
}

dataframe_t *df_apply(dataframe_t *df, const char *column, void *(*apply_func)(void *)) {
    if (!df || !column || !apply_func) return NULL;

    int col_index = get_column_index(df, column);
    if (col_index == -1) return NULL;

    dataframe_t *new_df = malloc(sizeof(dataframe_t));
    new_df->nb_rows = df->nb_rows;
    new_df->nb_columns = df->nb_columns;
    new_df->columns = malloc(df->nb_columns * sizeof(column_t));

    for (int c = 0; c < df->nb_columns; c++) {
        new_df->columns[c].name = strdup(df->columns[c].name);
        new_df->columns[c].values = malloc(df->nb_rows * sizeof(void *));
        for (int r = 0; r < df->nb_rows; r++) {
            if (c == col_index) {
                new_df->columns[c].values[r] = apply_func(df->columns[c].values[r]);
            } else {
                new_df->columns[c].values[r] = strdup(df->columns[c].values[r]);
            }
        }
    }
    return new_df;
}
