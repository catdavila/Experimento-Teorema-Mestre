/*
 * experimentos.c - Aplicacao do Teorema Mestre (tres recorrencias)
 * Caso 1: T(n)=3T(n/2)+1   (n potencia de 2)
 * Caso 2: T(n)=3T(n/3)+n   (n potencia de 3)
 * Caso 3: T(n)=T(n/2)+n    (n potencia de 2)
 * Saida: resultados.csv (problema,n,repeticao,tempo_ms,chamadas,operacoes)
 * tempo_ms = tempo medio de UMA execucao, obtido repetindo a funcao
 * INTERNAS vezes dentro da janela medida com clock() (reduz o erro de resolucao).
 */
#include <stdio.h>
#include <time.h>

#define INTERNAS 200

volatile unsigned long long acumulador = 0;
unsigned long long chamadas, trabalho;

/* Caso 1: T(n)=3T(n/2)+1 */
void caso1(int n) {
    chamadas++; trabalho++;
    acumulador += (unsigned long long)n;
    if (n <= 1) return;
    caso1(n/2); caso1(n/2); caso1(n/2);
}

/* Caso 2: T(n)=3T(n/3)+n */
void caso2(int n) {
    chamadas++;
    for (int i = 0; i < n; i++) { trabalho++; acumulador += (unsigned long long)(i & 1); }
    if (n <= 1) return;
    caso2(n/3); caso2(n/3); caso2(n/3);
}

/* Caso 3: T(n)=T(n/2)+n */
void caso3(int n) {
    chamadas++;
    for (int i = 0; i < n; i++) { trabalho++; acumulador += (unsigned long long)(i & 1); }
    if (n <= 1) return;
    caso3(n/2);
}

static void executa(int p, int n) {
    if (p == 1) caso1(n); else if (p == 2) caso2(n); else caso3(n);
}

int main(void) {
    FILE *arq = fopen("resultados.csv", "w");
    if (!arq) { perror("resultados.csv"); return 1; }
    fprintf(arq, "problema,n,repeticao,tempo_ms,chamadas,operacoes\n");
    const int ns1[] = {32, 64, 128, 256, 512, 1024};
    const int ns2[] = {27, 81, 243, 729, 2187, 6561};
    const int ns3[] = {32, 64, 128, 256, 512, 1024};
    for (int p = 1; p <= 3; p++)
      for (int j = 0; j < 6; j++) {
        int n = (p == 1 ? ns1[j] : (p == 2 ? ns2[j] : ns3[j]));
        for (int r = 1; r <= 5; r++) {
            chamadas = 0; trabalho = 0;
            executa(p, n);                       /* contagem determinística */
            unsigned long long c = chamadas, t = trabalho;
            clock_t ini = clock();
            for (int k = 0; k < INTERNAS; k++) executa(p, n);
            clock_t fim = clock();
            double ms = 1000.0 * (double)(fim - ini) / CLOCKS_PER_SEC / INTERNAS;
            fprintf(arq, "%d,%d,%d,%.6f,%llu,%llu\n", p, n, r, ms, c, t);
        }
      }
    fclose(arq);
    printf("Concluido. Controle: %llu\n", acumulador);
    return 0;
}
