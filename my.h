/*
** EPITECH PROJECT, 2023
** my.h
** File description:
** my headerfile
*/

#include <stdarg.h>
#ifndef TRIPLE_H_INCLUDED
    #define TRIPLE_H_INCLUDED
int my_printf(char const *format, ...);
void my_putchar(char c);
int my_put_nbr(int nb);
int my_put_nbr_second(long int nb);
int my_put_nbr_third(long long int nb);
int my_putstr(char const *str);
int my_compute_power_it(int nb, int p);
char my_put_upper(char a);
int my_put_str_up(char const *str);
int octal(int nb);
int binary(int nb);
int my_convert_base(int n);
int hexadecimal_up(int nb);
int my_put_signe(int nb);
void float_flag(double nb, int n);
void float_to_hex(double nb);
short int my_put_short_third(short int nb);
int my_cond_five(va_list args, char const *format, int i);
unsigned int my_put_unsigned(unsigned int nb);
unsigned long long int my_convert_adress(unsigned long long int n);
void information(char *argv);
void nothing(void);
void file_as_parameter(char *argv);
void file_l(char *argv);
char **my_str_to_word_array(char const *str);
int erreur(char *argv);
void dir_file(char *argv);
char *my_strcat(char *dest, char const *src, const char *str);
int count(char *p);
#endif // TRIPLE_H_INCLUDED
