/*
** EPITECH PROJECT, 2023
** my_printf5.c
** File description:
** herdg
*/
#include "my.h"
#include <stdarg.h>
int my_cond_five(va_list args, char const *format, int i)
{
    if (format[i] == '%' && format[i + 1] == '0' && format[i + 2] == 'o'){
        octal(va_arg(args, int));
        i++;
    }
    if (format[i] == '%' && format[i + 1] == '0' && format[i + 2] == 'x'){
        my_convert_base(va_arg(args, int));
        i++;
    }
    if (format[i] == '%' && format[i + 1] == '0' && format[i + 2] == 'X'){
        hexadecimal_up(va_arg(args, int));
        i++;
    }
    if (format[i] == '%' && format[i + 1] == 'u')
        my_put_unsigned(va_arg(args, int));
    if (format[i] == '%' && format[i + 1] == 'h' && format[i + 2] == 'd')
        my_put_short_third(va_arg(args, int));
    if (format[i] == '%' && format[i + 1] == 'f')
        float_flag(va_arg(args, double), 6);
    return i;
}
