#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int index;
    int posi;
} tabela;

// *** *** *** METODOS OFERECIDOS, IMPLEMENTADOS PELO DOCENTE/PAE *** *** *** \\

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
//unsigned char typedef bool;
#define TRUE  1
#define FALSE 0

int* ler_inteiros(const char * arquivo, const int n)
{
    FILE* f = fopen(arquivo, "r");

    int* inteiros = (int *) malloc(sizeof(int) * n);

    for (int i = 0; !feof(f); i++)
        fscanf(f, "%d\n", &inteiros[i]);

    fclose(f);

    return inteiros;
}

void inicia_tempo()
{
    srand(time(NULL));
    _ini = clock();
}

double finaliza_tempo()
{
    _fim = clock();
    return ((double) (_fim - _ini)) / CLOCKS_PER_SEC;
}

// *** *** *** INICIO IMPLEMENTACAO DO ALUNO *** *** *** \\

int busca_seq_ind_prim(int n, int x, int entradas[], tabela tabela[]){
    int i;

    for(i = 0; i < n && x > tabela[i].index; i++); //coloca o marcador i no intervalo no lugar correto da tabela
    if(i == 0) //se o numero buscado for <= ao indice da tabela
        if(x == tabela[i].index)
            return i;

    for(i = tabela[i - 1].posi; i < n && x > entradas[i]; i++); //percorre a entrada a partir i ate achar "x" ou o vetor acabar
    if(i < n && x == entradas[i]) //NUMERO ENCONTRADO! FIM!
        return i;

    //NUMERO NÂO ENCONTRADO! FIM!
    return -1;
}


void quicksort(int ini, int fim, int A[]) {
    int meio, pivo, aux, i, j;
    if (!(ini < fim)) //condicao de parada
        return;

    meio = ini + (fim - ini)/2; //calculando o meio do vetor
    pivo = A[meio]; //escolhe o pivo
    i = ini;
    j = fim;

    while (TRUE) { //fazendo o particionamento
        for ( ; A[i] < pivo; i++); //reposicionando o indice i
        for ( ; A[j] > pivo; j--); //reposicionando o indice j

        if (i == j) //condição de parada dessa iteracao
            break;
        aux = A[i];
        A[i] = A[j] ;//trocar de lugar A[i] com A[j]
        A[j] = aux;
    }

    quicksort(ini, i - 1, A); //dividinto o problema pela metade, analizando para baixo
    quicksort(i + 1, fim, A); //dividinto o problema pela metade, analizando para cima
}

void ordena( int tam, int A[]) {
    quicksort( 0, tam - 1, A); // quicksort recursivo
}


int main(int argc, char const *argv[])
{
    const int N = 50000;
    const int index_size = 10000;
    unsigned encontrados = 0;
    const int TAM = N/index_size;

    int* entradas = ler_inteiros("inteiros_entrada.txt", N);
    int* consultas = ler_inteiros("inteiros_busca.txt", N);

    ordena(N, entradas); //ordenar entrada

    tabela indice_primario[TAM]; //criar tabela de indice
    for(int i = 0; i < TAM; i++){
        indice_primario[i].posi = i*(index_size);
        indice_primario[i].index = entradas[indice_primario[i].posi];
    }

    inicia_tempo();
    for (int i = 0; i < N; i++) {
        if(!(busca_seq_ind_prim(N, consultas[i], entradas, indice_primario) == -1)) //realizar consultas na tabela de indices
            encontrados++;
    }
    double tempo_busca = finaliza_tempo();

    printf("Tempo de busca    :\t%fs\n", tempo_busca);
    printf("Itens encontrados :\t%d\n", encontrados);

    return 0;
}