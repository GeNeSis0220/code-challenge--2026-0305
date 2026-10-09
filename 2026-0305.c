// 2026-0305
#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M, L, U;
    if (scanf("%d %d %d %d", &N, &M, &L, &U) != 4) {
        printf("ERROR\n");
        return 0;
    }
    if (N < 1 || N > 30 || M < 1 || M > 30 || L < 0 || U < 0 || L > U || U > 1000) {
        printf("ERROR\n");
        return 0;
    }
    int matriz[30][30];
    int eventos_columna[30] = {0};
    int fila_prioritaria = 0;
    int max_racha_global = -1;
    int max_impacto_global = -1;
    int max_eventos_global = -1;
    int res_eventos[30], res_impacto[30], res_racha[30], res_inicio[30];
    int total_eventos_matriz = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (scanf("%d", &matriz[i][j]) != 1) {
                printf("ERROR\n");
                return 0;
            }
            if (matriz[i][j] < 0 || matriz[i][j] > 1000) {
                printf("ERROR\n");
                return 0;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        int MX = matriz[i][0];
        for (int j = 1; j < M; j++) {
            if (matriz[i][j] > MX) {
                MX = matriz[i][j];
            }
        }
        int cant_eventos = 0, suma_impacto = 0;
        int racha_actual = 0, inicio_actual = 0;
        int max_racha_fila = 0, inicio_max_racha_fila = 0;

        for (int j = 0; j < M; j++) {
            int x = matriz[i][j];
            if ((MX - x <= L) && (x >= U)) {
                cant_eventos++;
                suma_impacto += (x - U + 1);
                eventos_columna[j]++;
                total_eventos_matriz++;
                if (racha_actual == 0) {
                    inicio_actual = j + 1;
                }
                racha_actual++;
                if (racha_actual > max_racha_fila) {
                    max_racha_fila = racha_actual;
                    inicio_max_racha_fila = inicio_actual;
                }
            } else {
                racha_actual = 0;
            }
        }
        if (max_racha_fila == 0) {
            inicio_max_racha_fila = 0;
        }
        res_eventos[i] = cant_eventos;
        res_impacto[i] = suma_impacto;
        res_racha[i] = max_racha_fila;
        res_inicio[i] = inicio_max_racha_fila;

        int cambiar_prioridad = 0;
        if (fila_prioritaria == 0) {
            cambiar_prioridad = 1;
        } else {
            if (max_racha_fila > max_racha_global) {
                cambiar_prioridad = 1;
            } else if (max_racha_fila == max_racha_global) {
                if (suma_impacto > max_impacto_global) {
                    cambiar_prioridad = 1;
                } else if (suma_impacto == max_impacto_global) {
                    if (cant_eventos > max_eventos_global) {
                        cambiar_prioridad = 1;
                    }
                }
            }
        }
        if (cambiar_prioridad) {
            fila_prioritaria = i + 1;
            max_racha_global = max_racha_fila;
            max_impacto_global = suma_impacto;
            max_eventos_global = cant_eventos;
        }
    }
    int columna_destacada = 0;
    int max_eventos_columna = -1;
    for (int j = 0; j < M; j++) {
        if (eventos_columna[j] > max_eventos_columna) {
            max_eventos_columna = eventos_columna[j];
            columna_destacada = j + 1;
        }
    }
    if (total_eventos_matriz == 0) {
        fila_prioritaria = 0;
        columna_destacada = 0;
    }
    for (int i = 0; i < N; i++) {
        printf("FILA %d EVENTOS %d IMPACTO %d RACHA %d INICIO %d\n", i + 1, res_eventos[i], res_impacto[i], res_racha[i], res_inicio[i]);
    }
    printf("COLUMNAS");
    for (int j = 0; j < M; j++) {
        printf(" %d", eventos_columna[j]);
    }
    printf("\n");
    printf("PRIORIDAD %d\n", fila_prioritaria);
    printf("COLUMNA %d\n", columna_destacada);
    return 0;
}


