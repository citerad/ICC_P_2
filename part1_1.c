/* 
 * File:   main.c
 * Author: domenicocitera
 *
 * Created on 14 de noviembre de 2013, 16:58
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



void imatge(double t, double *p);
double distancia(double* p0, double* p1);

/*
 * 
 */
int main(int argc, char** argv) {

    int n, i = 0;
    double a, b;

    double p[3];

    printf("\n# Dammi n: ");
    scanf("%d", &n);
    printf("\n# Dammi gli estremi dell'intervallo a e b: ");
    scanf("%lf %lf", &a, &b);


    FILE *fd;
    /* apre il file in scrittura */
    fd = fopen("corba_0.dad", "w");
    if (fd == NULL) {
        perror("Errore in apertura del file");
        exit(1);
    }

    double pas = (b - a) / n;


    fprintf(fd, "# Corba: f(t) = cos(2pi*t), sin(2pi*t), t\n");
    fprintf(fd, "#        x                       y                          z\n");

    for (i = 0; i < n + 1; i++) {
        double t = a + i*pas;
        imatge(t, p);
        fprintf(fd, "%16.7e        %16.7e          %16.7e\n", p[0], p[1], p[2]);
    }
    fclose(fd);
    printf("\n# Punti salvati in corba_0.dad.\n"
            "Visualizzare nel plotter la prima curva? s/n ");
    char c;
    scanf("%s", &c);
    if (c == 's' || c == 'S')
        system("gnuplot -p -e \"splot 'corba_0.dad' w l\"");

    return (EXIT_SUCCESS);
}

void imatge(double t, double *p) {
    p[0] = cos(2 * M_PI * t);
    p[1] = sin(2 * M_PI * t);
    p[2] = t;
}

double distancia(double* p0, double* p1) {

    return sqrt(pow(p0[0] - p1[0], 2) +
            pow(p0[1] - p1[1], 2) +
            pow(p0[2] - p1[2], 2));
}