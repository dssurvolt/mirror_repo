/*
** EPITECH PROJECT, 2023
** B-CPE-110 : Secured
** File description:
** my.h
*/

#ifndef HASHTABLE_H
    #define HASHTABLE_H
    #include <unistd.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
typedef struct entry {
    int key;
    char *value;
    struct entry *next;
} entry_t;
typedef struct hashtable {
    int len;
    entry_t **s;
    int (*hash)(char *, int);
} hashtable_t;

// Hash function
int hash(char *key, int len);

// Create & destro table
hashtable_t *new_hashtable(int (*hash)(char *, int), int len);
void delete_hashtable(hashtable_t *ht);

// Handle table
int ht_insert(hashtable_t *ht, char *key, char *value);
int ht_delete(hashtable_t *ht, char *key);
char *ht_search(hashtable_t *ht, char *key);
void ht_dump(hashtable_t *ht);
char *base_converter(int nb, int base);
int my_atoi(char const *str);
char *charconver(int nb);
char *concint(char *dest, int i);
char *my_strcat(char *dest, char const *src);
char *my_strcpy(char *dest, char const *src);
int my_strlen(char const *str);
void my_swap(char *a, char *b);
char *reduc(char *str);
char *my_strcat(char *dest, char const *src);
char *my_revstr(char *str);
char *redix(char *str);
int basec(char *dest);
void my_putchar(char c);
int my_putnbr(int nb);
int my_putstr(char const *str);
entry_t *create_address(char *key, char *value, hashtable_t *ht);
char *my_strdup(char *str);
int my_strcmp(char const *dest, char *str);
void atpos(int hash, entry_t *hm);
char *my_strcpy(char *dest, char const *src);
#endif /* HASHTABLE_H */
