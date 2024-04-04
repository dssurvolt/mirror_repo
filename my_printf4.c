/*
** EPITECH PROJECT, 2023
** fonctions_4.c
** File description:
** my functions
*/
#include "my.h"
#include <stdarg.h>
int binary(int nb)
{
    int a = nb;
    int r = 0;
    int p = 0;
    int T[45];

    do {
        r = (a % 2);
        a = a / 2;
        T[p] = r;
        p++;
    }while (a != 0);
    for (int i = p - 1; i >= 0; i--)
        my_put_nbr(T[i]);
}

int my_put_nbr_third(long long int nb)
{
    if (nb >= 0 && nb < 10)
        my_putchar(nb + 48);
    else if (nb < 0){
        my_putchar('-');
        my_put_nbr_third(nb * (-1));
    } else {
        my_put_nbr_third(nb / 10);
        my_put_nbr_third(nb % 10);
    }
    return nb;
}

unsigned long long int my_convert_adress(unsigned long long int n)
{
    my_putstr("0x");
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

int my_put_signe(int nb)
{
    if (nb > 0){
        my_putchar('+');
        my_put_nbr(nb);
    }
    if (nb < 0)
        my_put_nbr(nb);
}

short int my_put_short_third(short int nb)
{
    if (nb >= 0 && nb < 10)
        my_putchar(nb + 48);
    else if (nb < 0){
        my_putchar('-');
        my_put_nbr_third(nb * (-1));
    } else {
        my_put_nbr_third(nb / 10);
        my_put_nbr_third(nb % 10);
    }
    return nb;
}
