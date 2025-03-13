/*
** EPITECH PROJECT, 2024
** Nouveau dossier [WSL: kali-linux]
** File description:
** my.h
*/

#ifndef DATAFRAME_H
#define DATAFRAME_H

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

typedef struct {
    char *name;
    column_type_t type;
    void **values;  // Tableau de pointeurs (chaque élément est une valeur d'une colonne)
} column_t;

typedef struct {
    int nb_rows;
    int nb_columns;
    column_t *columns;
} dataframe_t;

// Fonctions de base
dataframe_t *df_read_csv(const char *filename, const char *separator);
int df_write_csv(dataframe_t *dataframe, const char *filename);
void df_free(dataframe_t *dataframe);

// Fonctions d'affichage
dataframe_t *df_head(dataframe_t *dataframe, int nb_rows);
dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows);
typedef struct {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;
dataframe_shape_t df_shape(dataframe_t *dataframe);
void df_info(dataframe_t *dataframe);
void df_describe(dataframe_t *dataframe);

// Filtrage et tri
dataframe_t *df_filter(dataframe_t *dataframe, const char *column, bool (*filter_func)(void *value));
dataframe_t *df_sort(dataframe_t *dataframe, const char *column, bool (*sort_func)(void *, void *));

// Utilitaires
void *df_get_value(dataframe_t *dataframe, int row, const char *column);
void **df_get_values(dataframe_t *dataframe, const char *column);
void **df_get_unique_values(dataframe_t *dataframe, const char *column);

#endif
