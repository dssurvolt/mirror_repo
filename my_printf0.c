/*
** EPITECH PROJECT, 2023
** mini_printf.c
** File description:
** some cases of printf
*/
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
int my_cond_fourth(va_list args, char const *format, int i)
{
    if (format[i] == '%' && format[i + 1] == ' ' && format[i + 2] == 'd'){
        my_putchar(' ');
        my_put_nbr(va_arg(args, int));
        i++;
    }
    if (format[i] == '%' && format[i + 1] == '#' && format[i + 2] == 'd'){
        my_put_nbr(va_arg(args, int));
        i++;
    }
    if (format[i] == '%' && format[i + 1] == '+' && format[i + 2] == 'd'){
        my_put_signe(va_arg(args, int));
        i++;
    }
    if (format[i] == '%' && format[i + 1] == '0' && format[i + 2] == 'd'){
        my_put_nbr(va_arg(args, int));
        i++;
    }
    return i;
}

int my_cond_third(va_list args, char const *format, int i)
{
    if (format[i] == '%' && format[i + 1] == '#' && format[i + 2] == 'o') {
        my_putchar('0');
        octal(va_arg(args, int));
        i++;
    }
    if (format[i] == '%' && format[i + 1] == '#' && format[i + 2] == 'x') {
        my_putstr("0x");
        my_convert_base(va_arg(args, int));
        i++;
    }
    if (format[i] == '%' && format[i + 1] == '#' && format[i + 2] == 'X') {
        my_putstr("0X");
        hexadecimal_up(va_arg(args, int));
        i++;
    }
    return i;
}

int my_cond_second(va_list args, char const *format, int i)
{
    if (format[i] == '%' && format[i + 1] == 'b' || format[i + 1] == 'B')
        binary(va_arg(args, int));
    if (format[i] == '%' && format[i + 1] == 'l' && format[i + 2] == 'd'
        || format[i + 2] == 'i') {
        my_put_nbr_second(va_arg(args, long int));
        i++;
    }
    if (format[i] == '%' && format[i + 1] == 'l' && format[i + 2] == 'l'
        && format[i + 3] == 'd' || format[i + 3] == 'i'){
        my_put_nbr_third(va_arg(args, long long int));
        i = i + 2;
    }
    if (format[i] == '%' && format[i + 1] == 'm')
        my_putstr("Success");
    if (format[i] == '%' && format[i + 1] == 'p')
        my_convert_adress(va_arg(args, unsigned long long int));
    return i;
}

int my_cond(va_list args, char const *format, int i)
{
    if (format[i] == '%' && format[i + 1] == 'd' || format[i + 1] == 'i')
        my_put_nbr(va_arg(args, int));
    if (format[i] == '%' && format[i + 1] == 'c')
        my_putchar(va_arg(args, int));
    if (format[i] == '%' && format[i + 1] == 's')
        my_putstr(va_arg(args, char *));
    if (format[i] == '%' && format[i + 1] == '%')
        my_putchar('%');
    if (format[i] == '%' && format[i + 1] == 'C')
        my_put_upper(va_arg(args, int));
    if (format[i] == '%' && format[i + 1] == 'S')
        my_put_str_up(va_arg(args, char *));
    if (format[i] == '%' && format[i + 1] == 'o')
        octal(va_arg(args, int));
    if (format[i] == '%' && format[i + 1] == 'x')
        my_convert_base(va_arg(args, int));
    if (format[i] == '%' && format[i + 1] == 'X')
        hexadecimal_up(va_arg(args, int));
    return 0;
}

int my_printf(char const *format, ...)
{
    va_list args;

    va_start(args, format);
    for (int i = 0; format[i] != '\0'; i++){
        if (format[i] != '%'){
            my_putchar(format[i]);
        } else {
            my_cond(args, format, i);
            i = my_cond_second(args, format, i);
            i = my_cond_third(args, format, i);
            i = my_cond_fourth(args, format, i);
            i = my_cond_five(args, format, i);
            i++;
        }
    }
    va_end(args);
    return 0;
}
