/*
** EPITECH PROJECT, 2024
** trigo.c
** File description:
** ddjdfff
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double **transpose(double **matrice, double **transpose, int n) 
{
    int i = 0;
    int j = 0;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            transpose[i][j] = matrice[i][j];
        }
    }
    return transpose;
}

double **fullz(int a, int b)
{
    double **c = malloc(sizeof(double *) * a);

    for (int z = 0; z < a; z++)
        c[z] = malloc(sizeof(double) * a);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            c[i][j] = b;
        }
    }
    return c;
}

double **full(int ac, char **av)
{
    int a = sqrt(ac - 2);
    double **c = malloc(sizeof(double *) * a);
    int k = 2;

    for (int z = 0; z < a; z++)
        c[z] = malloc(sizeof(double) * a);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            c[i][j] = atof(av[k]);
            k++;
        }
    }
    return c;
}

double **multiplyMatrices(double **A, double **B, int x)
{
    double **result = malloc(x * sizeof(double *));

    for (int z = 0; z < x; z++)
        result[z] = malloc(x * sizeof(double));
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < x; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < x; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

double factorial(double nb)
{
    double c = 1;

    if (nb == 0)
        return 1.0;
    for (double a = 1; a <= nb; a++) {
        c = c * a;
    }
    return c;
}

double **divide(double **matrice, int taille, double n) 
{
    double **mat = fullz(taille, 0);
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            mat[i][j] = matrice[i][j] / n;
        }
    }
    return mat;
}

double **mutiply(double **matrice, int taille, double n) 
{
    double **mat = fullz(taille, 0);
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            mat[i][j] = matrice[i][j] * n;
        }
    }
    return mat;
}

double **identity(double **mat, int n) 
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                mat[i][j] = 1;
            } else {
                mat[i][j] = 0;
            }
        }
    }
    return mat;
}

double **n_matrix(double **mat, int n, int z)
{
    int i = 0;
    double **c = fullz(z, 0);
    transpose(mat, c, z);

    if (n == 0)
        return identity(c, z);
    else {
        for (i = 0; i < n - 1; i++){
            c = multiplyMatrices(c, mat, z);
        }
    }
    return c;
}

double **add(double **matrice1, double **matrice2, int taille) 
{
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            matrice1[i][j] += matrice2[i][j];
        }
    }
    return matrice1;
}

double **min(double **matrice1, double **matrice2, int taille) 
{
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            matrice1[i][j] -= matrice2[i][j];
        }
    }
    return matrice1;
}

double **exps(double **a, int ac)
{
    int b = sqrt(ac - 2);
    double **temp = fullz(b, 0);
    double **result = fullz(b, 0);
    for (int i = 0; i < 100; i++){
        temp = n_matrix(a, i, b);
        temp = divide(temp, b, (double)factorial(i));
        result = add(result, temp, b);
    }
    return result;
}

double **sins(double **a, int ac)
{
    int b = sqrt(ac - 2);
    double c = 0;
    double **temp = fullz(b, 0);
    double **temp2 = fullz(b, 0);
    double **result = fullz(b, 0);
    for (int i = 0; i < 99; i++){
        c = pow(-1, i) / factorial((2 * i) + 1);
        temp2 = n_matrix(a, (2 * i) + 1, b);
        temp = mutiply(temp2, b, c);
        result = add(result, temp, b);
    }
    return result;
}

double **coss(double **a, int ac)
{
    int b = sqrt(ac - 2);
    double c = 0;
    double **temp = fullz(b, 0);
    double **temp2 = fullz(b, 0);
    double **result = fullz(b, 0);
    for (int i = 0; i < 99; i++){
        c = pow(-1, i) / factorial((2 * i));
        temp2 = n_matrix(a, (2 * i), b);
        temp = mutiply(temp2, b, c);
        result = add(result, temp, b);
    }
    return result;
}

double **cossh(double **a, int ac)
{
    int b = sqrt(ac - 2);
    double c = 0;
    double **temp = fullz(b, 0);
    double **temp2 = fullz(b, 0);
    double **result = fullz(b, 0);
    for (int i = 0; i < 99; i++){
        c = 1 / factorial((2 * i));
        temp2 = n_matrix(a, (2 * i), b);
        temp = mutiply(temp2, b, c);
        result = add(result, temp, b);
    }
    return result;
}

double **sinsh(double **a, int ac)
{
    int b = sqrt(ac - 2);
    double c = 0;
    double **temp = fullz(b, 0);
    double **temp2 = fullz(b, 0);
    double **result = fullz(b, 0);
    for (int i = 0; i < 99; i++){
        c = 1 / factorial((2 * i) + 1);
        temp2 = n_matrix(a, (2 * i) + 1, b);
        temp = mutiply(temp2, b, c);
        result = add(result, temp, b);
    }
    return result;
}

double **error(int ac, char **av, double **a)
{
    int ai = 0;
    int b = sqrt(ac - 2);
    int c = 0;
    if (ac < 3)
        exit(84);
    if (pow(b, 2) != ac - 2)
        exit(84);
    if (strcmp(av[1], "EXP") == 0){
        a = exps(a, ac);
    }
    if (strcmp(av[1], "COS") == 0){
        a = coss(a, ac);
    }
    if (strcmp(av[1], "SIN") == 0){
        a = sins(a, ac);
    }
    if (strcmp(av[1], "SINH") == 0){
        a = sinsh(a, ac);
    }
    if (strcmp(av[1], "COSH") == 0){
        a = cossh(a, ac);
    }
    if (strcmp(av[1], "COSH") != 0 && strcmp(av[1], "SINH") != 0 && strcmp(av[1], "SIN") != 0 && strcmp(av[1], "COS") != 0 && strcmp(av[1], "EXP") != 0)
        exit(84);
    for (int i = 2; av[i] != NULL; i++){
        for (int j = 0; av[i][j] != '\0'; j++){
            if (!(av[i][j] >= '0' && av[i][j] <= '9'))
	        exit(84);
        }
        ai = 0;
    }
    for (int i = 2; av[i] != NULL; i++){
        for (int j = 0; av[i][j] != '\0'; j++){
            if (!(av[i][j] >= '0' && av[i][j] <= '9') && av[i][j] != '.' && av[i][j] != '-')
                exit(84);
            if (av[i][j] == '.' && !(av[i][j + 1] >= '0' && av[i][j + 1] <= '9'))
                exit(84);
            if (av[i][j] == '.')
		ai++;
            if (av[i][j] == '-' && j != 0)
                exit(84);
        }
        ai = 0;
    }
    if (ai > 1)
        exit(84);
    return a;
}

int main(int ac, char **av)
{
    int b = sqrt(ac - 2);
    double **a = full(ac, av);
    double c = 0;
    a = error(ac, av, a);
    for (int i = 0; i < b; i++){
        for (int j = 0; j < b; j++){
            c = a[i][j];
            printf("%.2f", c);
            if (j != b - 1)
                printf("\t");
        }
        printf("\n");
    }
}
