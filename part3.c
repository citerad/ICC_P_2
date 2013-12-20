/*COGNOM: CITERA NOM: DOMENICO DNI: AK1183068*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Avaluar(double t, double M[4]);

/*
 * 
 */
int main(int argc, char** argv) {
    int k, i, n;
    double x[3], y[3], z[3], M[4], s[3], rx, ry, rz, t, pas;
    

    /*n=punti per corda*/
    printf("\n# Dammi n: ");
    scanf("%d", &n);

    pas = 1.f / n;

    FILE * entrada, *uscita;
    entrada = fopen("deri.dad", "r");
    if (entrada == NULL) {
        printf("Error en obrir el fitxer %s \n", "deri.dad");
        exit(1);
    }

    uscita = fopen("deri_res.res", "w");
    if (uscita == NULL) {
        perror("Errore in apertura del file deri_res.res");
        exit(1);
    }

    fscanf(entrada, "%d", &k);
    /*leggo primo P*/
    fscanf(entrada, "%lf %lf %lf", &x[0], &y[0], &z[0]);
    /*per ogni gruppo di 3*/
    for (i = 0; i < k; i++) {
        fprintf(uscita, "\n#      x                    y                   z");
        /*leggo successivi 3 P*/
        for (int j = 1; j < 3; j++) {
            fscanf(entrada, "%lf %lf %lf", &x[j], &y[j], &z[j]);
        }

            s[0] = -3.f * x[0] + 4.f * x[1] - x[2];
            s[1] = -3.f * y[0] + 4.f * y[1] - y[2];
            s[2] = -3.f * z[0] + 4.f * z[1] - z[2];


        /*calcolo punti*/
        for (int j = 0; j < n + 1; j++) {
            t = j *pas;
            rx = 0.f;
            ry = 0.f;
            rz = 0.f;

            Avaluar(t, M);
            for (int k = 0; k < 3; k++) {
                rx += x[k] * M[k];
                ry += y[k] * M[k];
                rz += z[k] * M[k];
            }
            rx += s[0] * M[3];
            ry += s[1] * M[3];
            rz += s[2] * M[3];
            fprintf(uscita, "\n%+16.6e   %+16.6e   %+16.6e", rx, ry, rz);
        }
        /*sostituisco ultimo P con primo P*/
        x[0] = x[2];
        y[0] = y[2];
        z[0] = z[2];

        
    }
    return (EXIT_SUCCESS);
}

void Avaluar(double t, double M[4]) {
    
        M[0] = 1.f - (7.f * pow(t, 2.f))+(6.f * pow(t, 3.f));
        M[1] = (8.f * pow(t, 2.f))-(8.f * pow(t, 3.f));
        M[2] = -(pow(t, 2.f))+(2.f * pow(t, 3.f));
        M[3] = t - (3.f * pow(t, 2.f))+(2.f * pow(t, 3.f));


}
