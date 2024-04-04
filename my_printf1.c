/*
** EPITECH PROJECT, 2023
** fonctins.c
** File description:
** my functions
*/
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_put_nbr(int nb)
{
    if (nb >= 0 && nb < 10)
        my_putchar(nb + 48);
    else if (nb < 0){
        my_putchar('-');
        my_put_nbr(nb * (-1));
    } else {
        my_put_nbr(nb / 10);
        my_put_nbr(nb % 10);
    }
}

int my_putstr(char const *str)
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
        my_putchar(str[i]);
    return 0;
}

char my_put_upper(char a)
{
    if (a >= 'a' && a <= 'z'){
        my_putchar(a - 32);
        return (a - 32);
    }
    if (a >= 'A' && a <= 'Z'){
        my_putchar(a);
        return a;
    }
}

int my_put_str_up(char const *str)
{
    int i;

    for (i = 0; str[i] != '\0'; i++){
        if (str[i] >= 'A' && str[i] <= 'Z')
            my_putchar(str[i]);
        if (str[i] >= 'a' && str[i] <= 'z')
            my_putchar(str[i] - 32);
    }
    return 0;
}
