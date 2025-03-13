/*
** EPITECH PROJECT, 2024
** Nouveau dossier [WSL: kali-linux]
** File description:
** test_dataframe.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "my.h"

void test_read_csv() {
    printf("🔍 Test: df_read_csv()...\n");
    dataframe_t *df = df_read_csv("tests/test_data.csv", NULL);
    assert(df != NULL);
    assert(df->nb_rows == 3);
    assert(df->nb_columns == 3);
    printf("✅ df_read_csv() OK\n");
    df_free(df);
}

void test_write_csv() {
    printf("🔍 Test: df_write_csv()...\n");
    dataframe_t *df = df_read_csv("tests/test_data.csv", NULL);
    assert(df_write_csv(df, "tests/output.csv") == 0);
    printf("✅ df_write_csv() OK\n");
    df_free(df);
}

int main() {
    test_read_csv();
    test_write_csv();
    printf("🎉 Tous les tests sont passés !\n");
    return 0;
}
