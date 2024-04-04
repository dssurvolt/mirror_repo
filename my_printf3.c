/*
** EPITECH PROJECT, 2023
** fonctions_3.c
** File description:
** my fonctions
*/
#include "my.h"
#include <stdarg.h>
int cases_of_x(int i, int T[45])
{
    if (T[i] == 10)
        my_putchar('A');
    if (T[i] == 11)
        my_putchar('B');
    if (T[i] == 12)
        my_putchar('C');
    if (T[i] == 13)
        my_putchar('D');
    if (T[i] == 14)
        my_putchar('E');
    if (T[i] == 15)
        my_putchar('F');
}

int condition(int p, int T[45])
{
    for (int i = p - 1; i >= 0; i--){
        if (T[i] >= 0 && T[i] <= 9)
        my_put_nbr(T[i]);
        if (T[i] >= 10 && T[i] <= 16)
            cases_of_x(i, T);
    }
}

int hexadecimal_up(int nb)
{
    int a = nb;
    int b = 0;
    int c = 0;
    int p = 0;
    int y = 0;
    int T[45];

    do {
        b = (a % 16);
        a = a / 16;
        T[p] = b;
        p++;
        y++;
    }while (a != 0);
    condition(p, T);
}

int my_compute_power_it(int nb, int p)
{
    int c = 1;

    for (int e = 1; e <= p; e++){
        if (p < 0)
            c = c - 1;
        if (p > 0)
            c = c * nb;
    }
    return c;
}

int my_put_nbr_second(long int nb)
{
    if (nb >= 0 && nb < 10)
        my_putchar(nb + 48);
    else if (nb < 0){
        my_putchar('-');
        my_put_nbr_second(nb * (-1));
    } else {
        my_put_nbr_second(nb / 10);
        my_put_nbr_second(nb % 10);
    }
    return nb;
}
