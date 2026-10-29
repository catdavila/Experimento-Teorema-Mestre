# Experimentos com o Teorema Mestre

Programa em C que mede o custo de três recorrências resolvidas pelo Teorema Mestre, contando chamadas recursivas, operações e tempo de execução.

## Recorrências

| Caso | Recorrência | n |
|------|-------------|---|
| 1 | T(n) = 3T(n/2) + 1 | potência de 2 (32 a 1024) |
| 2 | T(n) = 3T(n/3) + n | potência de 3 (27 a 6561) |
| 3 | T(n) = T(n/2) + n | potência de 2 (32 a 1024) |

## Como rodar

```bash
gcc -O0 -o experimentos experimentos.c
./experimentos
```

Gera o arquivo `resultados.csv`.

## Saída

`resultados.csv` tem uma linha por execução (3 casos x 6 tamanhos x 5 repetições = 90 linhas):

| Coluna | Descrição |
|--------|-----------|
| problema | caso (1, 2 ou 3) |
| n | tamanho da entrada |
| repeticao | número da repetição (1 a 5) |
| tempo_ms | tempo médio de uma execução, em ms |
| chamadas | número de chamadas recursivas |
| operacoes | unidades de trabalho executadas |

O `tempo_ms` é medido repetindo a função 200 vezes dentro da janela do `clock()` e dividindo pelo total, pra reduzir o erro de resolução do relógio.

## Arquivos

- `experimentos.c`: código dos experimentos
- `resultados.csv`: resultados gerados
