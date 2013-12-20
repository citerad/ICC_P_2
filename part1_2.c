/*COGNOM: CITERA NOM: DOMENICO DNI: AK1183068*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*TEST:
 * Part2 input tol = 0.01, [0, 2] = OK
 * corba_1 input tol = 0.01, [0,5] = OK
 * corba_2 input tol = 0.01, [-40,40] = OK
 * corba_3 input tol = 0.01, [0, 6,3] = OK
 * 
 */
void imatge(double t, double *p);
double distancia(double* p0, double* p1);
void imatge_mod(double t, double *p, int i);
void calculP(int n, FILE *);

int main(int argc, char** argv) {

    double tol, a, b, t, pas, dist;

    printf("\n# Dammi tol: ");
    scanf("%lf", &tol);
    printf("\n# Dammi gli estremi dell'intervallo a e b: ");
    scanf("%lf %lf", &a, &b);

    double p0[3];
    double p1[3];


    FILE *fd;
    fd = fopen("corba_0_2.dad", "w");
    if (fd == NULL) {
        perror("Errore in apertura del file");
        exit(1);
    }

    fprintf(fd, "# Corba: f(t) = cos(2pi*t), sin(2pi*t), t\n");
    fprintf(fd, "#        x                       y                          z\n");

    t = a;
    imatge(t, p0);
    fprintf(fd, "%16.7e        %16.7e          %16.7e\n", p0[0], p0[1], p0[2]);
    pas = tol;
    do {
        do {
            imatge((t + pas), p1);
            dist = distancia(p0, p1);
            if (dist > tol) {
                pas = pas / 2;
            }

        } while (dist > tol);
        fprintf(fd, "%16.7e        %16.7e          %16.7e\n", p1[0], p1[1], p1[2]);
        p0[0] = p1[0];
        p0[1] = p1[1];
        p0[2] = p1[2];

        /*pas = pas * tol / dist;*/
        t = t + pas;


    } while (t + pas < b);

    fclose(fd);
    printf("\n# Punti salvati in corba_0_2.dad.\n");


    FILE *corba_1, *corba_2, *corba_3, *corba_4, *corba_5;
    corba_1 = fopen("corba_1.dad", "w");
    corba_2 = fopen("corba_2.dad", "w");
    corba_3 = fopen("corba_3.dad", "w");
    corba_4 = fopen("corba_4.dad", "w");
    corba_5 = fopen("corba_5.dad", "w");
    if (corba_1 == NULL || corba_2 == NULL || corba_3 == NULL || corba_4 == NULL
            || corba_5 == NULL) {
        perror("Errore in apertura del file");
        exit(1);
    }
    calculP(1, corba_1);
    calculP(2, corba_2);
    calculP(3, corba_3);
    calculP(4, corba_4);
    calculP(5, corba_5);

    return (EXIT_SUCCESS);
}

/**
 * trova punti
 * @param t
 * @param p
 */
void imatge(double t, double *p) {

    p[0] = cos(2 * M_PI * t);
    p[1] = sin(2 * M_PI * t);
    p[2] = t;
}

/**
 * Calcola distanza tra due punti
 * @param p0 punto a
 * @param p1 punto b
 * @return  distancia
 */
double distancia(double* p0, double* p1) {

    return sqrt(pow(p0[0] - p1[0], 2) +
            pow(p0[1] - p1[1], 2) +
            pow(p0[2] - p1[2], 2));
}

/**
 * Risolve le 3 funzioni della 4 parte
 * @param i indica la funzione
 * @param fd file su cui scrivere i risultati
 */
void calculP(int i, FILE *fd) {

    double tol, a, b, t, pas, dist;

    printf("\n# Dammi tol per corba %d: ", i);
    scanf("%lf", &tol);
    printf("\n# Dammi gli estremi dell'intervallo a e b per corba %d: ", i);
    scanf("%lf %lf", &a, &b);
    double p0[3];
    double p1[3];
    if (i == 1)
        fprintf(fd, "# Corba: g(t) = exp(-t/2)cos(2PI*t), exp(-t/3)sin(2PI*t), t^2\n");
    else if (i == 2)
        fprintf(fd, "# Corba: h(t) = cos(t)/cosh(0.1(t-1)), sin(t)/cosh(0.1(t-1)), tanh(0.1(t-1))\n");
    else if (i == 3)
        fprintf(fd, "# Corba: j(t) = cos(t)(cos^2(10t)+0.2)^(1/2), sin(t)(cos^2(10t)+0.2)^(1/2), cos(10t)\n");
    else if (i== 4)
        fprintf(fd, "# Corba: l(t) = 1+cos(t), sin(t), 2*sin(t)/2\n");
    else if (i ==5)
        fprintf(fd, "# Corba: m(t) = t-2*cos(2PI*t), 1-2*sin(2PI*t), cos(4PI*t);\n");
    fprintf(fd, "#        x                       y                          z\n");

    t = a;
    imatge_mod(t, p0, i);
    fprintf(fd, "%16.7e        %16.7e          %16.7e\n", p0[0], p0[1], p0[2]);
    pas = tol;
    do {
        do {
            imatge_mod((t + pas), p1, i);
            dist = distancia(p0, p1);
            if (dist > tol) {
                pas = pas / 2;
            }

        } while (dist > tol);
        fprintf(fd, "%16.7e        %16.7e          %16.7e\n", p1[0], p1[1], p1[2]);
        p0[0] = p1[0];
        p0[1] = p1[1];
        p0[2] = p1[2];

        /*pas = pas * tol / dist;*/
        t = t + pas;


    } while (t + pas < b);

    fclose(fd);
    printf("\n# Punti salvati in corba_%d.dad.\n", i);

}

/**
 * 
 * @param t f(t)
 * @param p punti
 * @param i indica funzione
 */
void imatge_mod(double t, double *p, int i) {

    if (i == 1) {
        p[0] = exp(-t / 2) * cos(2 * M_PI * t);
        p[1] = exp(-t / 3) * sin(2 * M_PI * t);
        p[2] = t*t;
    }
    if (i == 2) {
        p[0] = cos(t) / cosh(0.1 * (t - 1));
        p[1] = sin(t) / cosh(0.1 * (t - 1));
        p[2] = tanh(0.1 * (t - 1));
    }
    if (i == 3) {
        p[0] = cos(t) * sqrt(pow(cos(10 * t), 2) + 0.2);
        p[1] = sin(t) * sqrt(pow(cos(10 * t), 2) + 0.2);
        p[2] = cos(10 * t);
    }
    if (i == 4) {
        p[0] = 1 + cos(t);
        p[1] = sin(t);
        p[2] = 2 * sin(t) / 2;
    }
    if (i == 5) {
        p[0] = t - (2 * cos(2 * M_PI * t));
        p[1] = 1 - (2 * sin(2 * M_PI * t));
        p[2] = cos(4 * M_PI * t);
    }

}

