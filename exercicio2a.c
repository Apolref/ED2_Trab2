#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // funções strcmp e strcpy
#include <math.h>
#include <tgmath.h>

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
typedef unsigned char bool;
#define TRUE  1
#define FALSE 0
#define sucesso 0
#define erro -1
#define inserido -2

// Definição do tipo string
typedef char * string;

#define MAX_STRING_LEN 20

typedef struct {
    unsigned info[150001];
} hash;

unsigned int h_div(unsigned int x, unsigned int i, unsigned int B)
{
    return ((x % B) + i) % B;
}

unsigned h_mul(unsigned x, unsigned i, unsigned B)
{
    const double A = 0.6180;
    double aux = fmod(x * A, 1);
    return  ((int) ((aux * B) + i)) % B;
}

void criar_hash(hash *t, unsigned int B) {
    for (int i = 0; i < B; i++)
        t->info[i] = -1; // -1: posicao vazia, nunca utilizada
}

int inserir_div(hash *tabela, unsigned int n, unsigned int B){
    unsigned int pos;
    for(unsigned int i = 0; i < B; i++){
        pos = h_div(n, i, B);
        if (tabela->info[pos] == -1 || tabela->info[pos] == -2){
            tabela->info[pos] = n;
            return sucesso;
        }
        if(tabela->info[pos] == n){
            return inserido;
        }
    }
    return erro;
}

int busca_div(hash *tabela, unsigned int n, unsigned int B){
    unsigned int pos;
    for(unsigned int i = 0; i < B; i++){
        pos = h_div(n, i, B);
        if(tabela->info[pos] == n){
            return pos;
        }
        if(tabela->info[pos] == -1){
            return erro;
        }
    }
    return erro;
}

int inserir_mul(hash *tabela, unsigned int n, unsigned int B){
    unsigned int pos;
    for(unsigned int i = 0; i < B; i++){
        pos = h_mul(n, i, B);
        if (tabela->info[pos] == -1 || tabela->info[pos] == -2){
            tabela->info[pos] = n;
            return sucesso;
        }
        if(tabela->info[pos] == n){
            return inserido;
        }
    }
    return erro;
}

int busca_mul(hash *tabela, unsigned int n, unsigned int B){
    unsigned int pos;
    for(unsigned int i = 0; i < B; i++){
        pos = h_mul(n, i, B);
        if(tabela->info[pos] == n){
            return pos;
        }
        if(tabela->info[pos] == -1){
            return erro;
        }
    }
    return erro;
}

unsigned converter(string s) {
   unsigned h = 0;
   for (int i = 0; s[i] != '\0'; i++) 
      h = h * 256 + s[i];
   return h;
}

string* ler_strings(const char * arquivo, const int n)
{
    FILE* f = fopen(arquivo, "r");
    
    string* strings = (string *) malloc(sizeof(string) * n);

    for (int i = 0; !feof(f); i++) {
        strings[i] = (string) malloc(sizeof(char) * MAX_STRING_LEN);
        fscanf(f, "%s\n", strings[i]);
    }

    fclose(f);

    return strings;
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


int main(int argc, char const *argv[])
{
    unsigned int N = 50000;
    unsigned int M = 70000;
    unsigned int B = 150001;
    int h;

    unsigned int colisoes_h_div = 0;
    unsigned colisoes_h_mul = 0;

    unsigned int encontrados_h_div = 0;
    unsigned int encontrados_h_mul = 0;

    hash tabela;
    int key;//apagar var depois, fiz para teste

    string* insercoes = ler_strings("strings_entrada.txt", N);
    string* consultas = ler_strings("strings_busca.txt", M);


    // cria tabela hash com hash por divisão
    
    criar_hash(&tabela, B);

    // inserção dos dados na tabela hash usando hash por divisão
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        // inserir insercoes[i] na tabela hash
        h = converter(insercoes[i]);
        key = inserir_div(&tabela, h, B);
        if(key == -2){
            colisoes_h_div++;
        }
    }
    double tempo_insercao_h_div = finaliza_tempo();

    // consulta dos dados na tabela hash usando hash por divisão
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        // buscar consultas[i] na tabela hash
        h = converter(consultas[i]);
        key = busca_div(&tabela, h, B);
        if(key != -1){
            encontrados_h_div++;
        }

    }
    double tempo_busca_h_div = finaliza_tempo();
    
    // limpa a tabela hash com hash por divisão



    // cria tabela hash com hash por divisão

    criar_hash(&tabela, B);

    // inserção dos dados na tabela hash usando hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        // inserir insercoes[i] na tabela hash
        h = converter(insercoes[i]);
        inserir_mul(&tabela, h, B);
        if(key == -2){
            colisoes_h_mul++;
        }
    }
    double tempo_insercao_h_mul = finaliza_tempo();

    // busca dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        // buscar consultas[i] na tabela hash
        h = converter(consultas[i]);
        key = busca_mul(&tabela, h, B);
        if(key != -1){
            encontrados_h_mul++;
        }
    }
    double tempo_busca_h_mul = finaliza_tempo();

    // limpa a tabela hash com hash por multiplicação
    


    printf("Hash por Divisão\n");
    printf("Colisões na inserção: %d\n", colisoes_h_div);
    printf("Tempo de inserção   : %fs\n", tempo_insercao_h_div);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_div);
    printf("Itens encontrados   : %d\n", encontrados_h_div);
    printf("\n");
    printf("Hash por Multiplicação\n");
    printf("Colisões na inserção: %d\n", colisoes_h_mul);
    printf("Tempo de inserção   : %fs\n", tempo_insercao_h_mul);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_mul);
    printf("Itens encontrados   : %d\n", encontrados_h_mul);
    
    return 0;
}
