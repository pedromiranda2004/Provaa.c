#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 128
#define MAX_SENSORS 100

typedef struct {
    long timestamp;
    char id_sensor[32];
    char valor[64];
} Leitura;

int comparar_desc(const void *a, const void *b) {
    return ((Leitura *)b)->timestamp - ((Leitura *)a)->timestamp;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    FILE *entrada = fopen(argv[1], "r");
    if (!entrada) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    Leitura leituras[10000];
    int total = 0;

    while (fscanf(entrada, "%ld %s %s", &leituras[total].timestamp, leituras[total].id_sensor, leituras[total].valor) == 3) {
        total++;
    }

     fclose(entrada);


    for (int i = 0; i < total; i++) {
        char nome_arquivo[64];
        sprintf(nome_arquivo, "%s.txt", leituras[i].id_sensor);
        FILE *saida = fopen(nome_arquivo, "a");
        if (!saida) continue;
        fprintf(saida, "%ld %s %s\n", leituras[i].timestamp, leituras[i].id_sensor, leituras[i].valor);
        fclose(saida);
    }


    char sensores[MAX_SENSORS][32];
    int count = 0;

    for (int i = 0; i < total; i++) {
        int novo = 1;
        for (int j = 0; j < count; j++) {
            if (strcmp(sensores[j], leituras[i].id_sensor) == 0) {
            novo = 0;
            break;
            }
        }
        if (novo) strcpy(sensores[count++], leituras[i].id_sensor);
    }

    for (int i = 0; i < count; i++) {
        char nome_arquivo[64];
        sprintf(nome_arquivo, "%s.txt", sensores[i]);
        FILE *arquivo = fopen(nome_arquivo, "r");
        Leitura temp[10000];
        int n = 0;

        while (fscanf(arquivo, "%ld %s %s", &temp[n].timestamp, temp[n].id_sensor, temp[n].valor) == 3)
            n++;
        fclose(arquivo);

        qsort(temp, n, sizeof(Leitura), comparar_desc);

        arquivo = fopen(nome_arquivo, "w");
        for (int j = 0; j < n; j++)
            fprintf(arquivo, "%ld %s %s\n", temp[j].timestamp, temp[j].id_sensor, temp[j].valor);
        fclose(arquivo);
    }

    return 0;
}
