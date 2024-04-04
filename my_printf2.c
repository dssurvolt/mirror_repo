/*
** EPITECH PROJECT, 2023
** fonctions_2.c
** File description:
** my functions
*/
#include <stdarg.h>
#include "my.h"
int octal(int nb)
{
    int a = nb;
    int i;
    int b = 0;
    int p = 0;
    int T[45];

    do {
        b = (a % 8);
        a = a / 8;
        T[p] = b;
        p++;
    }while (a != 0);
    for (i = p - 1; i >= 0; i--){
        my_put_nbr(T[i]);
    }
    return 0;
}

int my_convert_base(int n)
{
    if (n < 10) {
        my_put_nbr(n);
        return n;
    }
    if (n >= 10 && n < 16) {
        my_putchar(n + 87);
        return n;
    }
    if (n >= 16) {
        my_convert_base(n / 16);
    }
    my_convert_base(n % 16);
    return n;
}

unsigned int my_put_unsigned(unsigned int nb)
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
    return nb;
}

void float_flag(double nb, int n)
{
    int x;
    int y;
    int i = 0;
    int j = 1;

    my_put_nbr(nb);
    my_putchar('.');
    for (i; i < n; i++){
        j = j * 10;
        x = nb * j;
        y = x % 10;
        my_put_nbr(y);
    }
}
