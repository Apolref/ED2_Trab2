#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
typedef unsigned char bool;
#define TRUE  1
#define FALSE 0

// Definição do tipo string
typedef char * string;

#define MAX_STRING_LEN 20

typedef struct{
  string* dados;
}hash;

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


unsigned h_div(unsigned x, unsigned i, unsigned B)
{
    return ((x % B) + i) % B;
}

unsigned h_mul(unsigned x, unsigned i, unsigned B)
{
    const double A = 0.6180;
    return  ((int) ((fmod(x * A, 1) * B) + i)) % B;
}


void criar_hash(hash *tabela, unsigned B){
    tabela->dados = (string *) malloc(B* sizeof(string));
    for (int i=0; i<B; i++){
        tabela->dados[i]=NULL;
    }
}

int inserir_hash(hash *tabela, int B, string elem){
    unsigned posicao;
    unsigned h=converter(elem);
    for (int i=0; i<B; i++){
        posicao = (h_mul(h,0,B)+i*h_div(h,0,B))%B; //função hash duplo
        if(tabela->dados[posicao]==NULL){
            tabela->dados[posicao] = (string) malloc(20 * sizeof(char));
            tabela->dados[posicao] = elem;
            return i; // retorna sempre 0 se não haver colisão
        }
        if(!strcmp(tabela->dados[posicao], elem)){
            return 0;
        }
    }
    return 0;
}

int busca_hash(hash *tabela, int B, string elem){
    unsigned posicao;
    unsigned h=converter(elem);
    for (int i=0; i<B; i++){
      posicao = (h_mul(h,0,B)+i*h_div(h,0,B))%B; // função hash duplo
        if(tabela->dados[posicao] == NULL){
            return 0; // elemento não faz parte da tabela
        }
       if(!strcmp(tabela->dados[posicao], elem)){
            return 1; // elemento encontrado
        }
    }
    return 0;
}


void limpar_hash(hash *tabela, int B){
    for (int i; i<B; i++){
        free(tabela->dados[i]);
    }
    free(tabela->dados);
}


int main(int argc, char const *argv[])
{
    const int N = 50000;
    const int M = 70000;
    const int B = 150001;

    unsigned colisoes = 0;
    unsigned encontrados = 0;

    string* insercoes = ler_strings("strings_entrada.txt", N);
    string* consultas = ler_strings("strings_busca.txt", M);

    hash tabela;
    // cria tabela hash com hash por hash duplo
    criar_hash(&tabela, B);

    // inserção dos dados na tabela hash
    inicia_tempo();
    for (int i = 0; i < N; i++) {
      // inserir insercoes[i] na tabela hash
      if(inserir_hash(&tabela,B,insercoes[i])>0){
        colisoes++;
      }
    }
    double tempo_insercao = finaliza_tempo();

    // busca dos dados na tabela hash
    inicia_tempo();
    for (int i = 0; i < M; i++) {
      // buscar consultas[i] na tabela hash
      if(busca_hash(&tabela,B,consultas[i]) == 1){
        encontrados++;
      }
    }
    double tempo_busca = finaliza_tempo();

    // Limpa a tabela hash
    limpar_hash(&tabela, B);
    

    printf("Colisões na inserção: %d\n", colisoes);
    printf("Tempo de inserção   : %fs\n", tempo_insercao);
    printf("Tempo de busca      : %fs\n", tempo_busca);
    printf("Itens encontrados   : %d\n", encontrados);
    
    free(insercoes);
    free(consultas);
    
    return 0;
}
