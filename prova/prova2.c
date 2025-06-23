#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long timestamp;
    char id_sensor[32];
    char valor[64];
} Leitura;
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <ID_SENSOR> <TIMESTAMP>\n", argv[0]);
        return 1;
    }

    char *sensor = argv[1];
    long alvo = atol(argv[2]);
    char nome_arquivo[64];
    sprintf(nome_arquivo, "%s.txt", sensor);

    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        return 1;
    }
    Leitura leituras[10000];
    int n = 0;
    while (fscanf(arquivo, "%ld %s %s", &leituras[n].timestamp, leituras[n].id_sensor, leituras[n].valor) == 3)
        n++;
    fclose(arquivo);
    int esq = 0, dir = n - 1;
    int melhor = -1;
    long menor_diff = 9999999999;

    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        long diff = labs(leituras[meio].timestamp - alvo);
        if (diff < menor_diff) {
            menor_diff = diff;
            melhor = meio;
        }
        if (leituras[meio].timestamp > alvo)
            esq = meio + 1;
        else
            dir = meio - 1;
    }

    if (melhor != -1)
        printf("%ld %s %s\n", leituras[melhor].timestamp, leituras[melhor].id_sensor, leituras[melhor].valor);
    else
        printf("Leitura não encontrada\n");

    return 0;
}