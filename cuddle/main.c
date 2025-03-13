/*
** EPITECH PROJECT, 2024
** Nouveau dossier [WSL: kali-linux]
** File description:
** main.c
*/

#include <stdio.h>
#include <stdbool.h>
#include "my.h"

bool filter_func(void *value) {
    return atoi((char *)value) > 30;
}

void *apply_func(void *value) {
    int *new_val = malloc(sizeof(int));
    *new_val = atoi((char *)value) * 2;
    return new_val;
}

int main() {
    dataframe_t *df = df_read_csv("data.csv", NULL);
    if (!df) return 84;

    dataframe_t *sorted = df_sort(df, "age", filter_func);
    df_write_csv(sorted, "sorted.csv");

    dataframe_t *filtered = df_filter(df, "age", filter_func);
    df_write_csv(filtered, "filtered.csv");

    dataframe_t *applied = df_apply(df, "age", apply_func);
    df_write_csv(applied, "applied.csv");

    df_free(df);
    return 0;
}
