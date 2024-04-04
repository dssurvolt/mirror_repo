/*
** EPITECH PROJECT, 2024
** print.c
** File description:
** suydgxfdg
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
#include "../include/my.h"
#include <unistd.h>
void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_putnbr(int nb)
{
    if (nb >= 0 && nb < 10)
        my_putchar(48 + nb);
    else if (nb < 0){
        my_putchar('-');
        my_putnbr(nb * (-1));
    } else {
        my_putnbr(nb / 10);
        my_putnbr(nb % 10);
    }
}

int my_putstr(char const *str)
{
    int i = 0;

    for (i; str[i] != '\0'; i++)
        my_putchar(str[i]);
    return 0;
}
