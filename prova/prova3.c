#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long gerar_timestamp(long inicio, long fim) {
    return inicio + rand() % (fim - inicio + 1);
}
void gerar_valor(char *tipo, char *saida) {
    if (strcmp(tipo, "CONJ_Z") == 0)
        sprintf(saida, "%d", rand() % 1000);
    else if (strcmp(tipo, "CONJ_Q") == 0)
        sprintf(saida, "%.2f", (float)(rand() % 10000) / 100.0);
    else if (strcmp(tipo, "BINARIO") == 0)
        strcpy(saida, rand() % 2 ? "true" : "false");
    else if (strcmp(tipo, "TEXTO") == 0) {
        int len = rand() % 16 + 1;
        for (int i = 0; i < len; i++)
            saida[i] = 'A' + rand() % 26;
        saida[len] = '\0';
    }
}
int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Uso: %s <timestamp_inicio> <timestamp_fim> <sensor1,tipo1> <sensor2,tipo2> ...\n", argv[0]);
        return 1;
    }
    long inicio = atol(argv[1]);
    long fim = atol(argv[2]);
    FILE *saida = fopen("leituras.txt", "w");
    for (int i = 3; i < argc; i++) {
        char sensor[32], tipo[16];
        sscanf(argv[i], "%[^,],%s", sensor, tipo);

        for (int j = 0; j < 2000; j++) {
            long ts = gerar_timestamp(inicio, fim);
            char valor[64];
            gerar_valor(tipo, valor);
            fprintf(saida, "%ld %s %s\n", ts, sensor, valor);
        }
    }
    fclose(saida);
    return 0;
}