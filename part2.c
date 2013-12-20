/*COGNOM: CITERA NOM: DOMENICO DNI: AK1183068*/

#include <stdio.h>
#include <stdlib.h>

void AvaluarLagrange(double t, double L[4]);
void ReadGroup(double x[4], double y[4], double z[4]);

int main(int argc, char** argv) {

    int k, i, n;
    double x[4], y[4], z[4], L[4], rx, ry, rz, t, pas;

    /*n=punti per corda*/
    printf("\n# Dammi n: ");
    scanf("%d", &n);

    pas = 1.f / n;

    FILE * entrada, *uscita;
    entrada = fopen("cont.dad", "r");
    if (entrada == NULL) {
        printf("Error en obrir el fitxer %s \n", "cont.dad");
        exit(1);
    }

    uscita = fopen("cont_res.res", "w");
    if (uscita == NULL) {
        perror("Errore in apertura del file cont_res.res");
        exit(1);
    }

    fscanf(entrada, "%d", &k);
    /*leggo primo P*/
    fscanf(entrada, "%lf %lf %lf", &x[0], &y[0], &z[0]);
    /*per ogni gruppo di 4*/
    for (i = 0; i < k; i++) {
        fprintf(uscita, "\n#      x                    y                   z");
        /*leggo successivi 3 P*/
        for (int j = 1; j < 4; j++) {
            fscanf(entrada, "%lf %lf %lf", &x[j], &y[j], &z[j]);
        }
        /*calcolo punti*/
        for (int j = 0; j < n + 1; j++) {
            t = j *pas;
            rx = 0.f;
            ry = 0.f;
            rz = 0.f;
            AvaluarLagrange(t, L);
            for (int k = 0; k < 4; k++) {
                rx += x[k] * L[k];
                ry += y[k] * L[k];
                rz += z[k] * L[k];
            }
            fprintf(uscita, "\n%+16.6e   %+16.6e   %+16.6e", rx, ry, rz);
        }
        /*sostituisco ultimo P con primo P*/
        x[0] = x[3];
        y[0] = y[3];
        z[0] = z[3];
    }
    return (EXIT_SUCCESS);
}

void AvaluarLagrange(double t, double L[4]) {
    L[0] = (-9.f / 2.f) * (t - (1.f / 3.f))*(t - (2.f / 3.f))*(t - 1.f);
    L[1] = (27.f / 2.f) * (t - 0.f)*(t - (2.f / 3.f))*(t - 1.f);
    L[2] = (-27.f / 2.f) * (t - 0.f)*(t - (1.f / 3.f))*(t - 1.f);
    L[3] = (9.f / 2.f) * (t - 0.f)*(t - (1.f / 3.f))*(t - (2.f / 3.f));
}
