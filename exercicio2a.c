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

// Definição do tipo string
typedef char * string;

#define MAX_STRING_LEN 20

typedef struct {
    string* dados;
} hash;

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
    t->dados = (string *) malloc(B* sizeof(string));
    for (int i = 0; i < B; i++)
        t->dados[i] = NULL; // inicialização da tabela com NULL nos espaços vazios
}

int inserir_div(hash *tabela, string elem, unsigned B){
    unsigned pos;
    int h=converter(elem);
    for(unsigned int i = 0; i < B; i++){
        pos = h_div(h, i, B);//calculo da função hash
        if(tabela->dados[pos] == NULL){
            tabela->dados[pos] = (string) malloc(20 * sizeof(char));
            tabela->dados[pos] = elem;
            return i;// retorna sempre 0 se não haver colisão
        }
        if(!strcmp(tabela->dados[pos], elem)){
            return 0; // elemento ja presente
        }
    }
    return 0;
}

int busca_div(hash *tabela, string elem, unsigned B){
    unsigned pos;
    int h=converter(elem);
    for(unsigned int i = 0; i < B; i++){
        pos = h_div(h, i, B);//calculo da função hash
        if(tabela->dados[pos] == NULL){
            return 0; // elemento não está presente na tabela
        }
       if(!strcmp(tabela->dados[pos], elem)){
            return 1; // elemento encontrado
        }
    }
    return 0;
}

int inserir_mul(hash *tabela, string elem, unsigned B){
    unsigned pos;
    int h=converter(elem);
    for(unsigned int i = 0; i < B; i++){
        pos = h_mul(h, i, B); //calculo da função hash
        if(tabela->dados[pos] == NULL){
            tabela->dados[pos] = (string) malloc(20 * sizeof(char));
            tabela->dados[pos] = elem;
            return i; // retorna sempre 0 se não haver colisão
        }
        if(!strcmp(tabela->dados[pos], elem)){
            return 0;// elemento ja presente
        }
    }
    return 0;
}

int busca_mul(hash *tabela, string elem, unsigned B){
    unsigned pos;
    int h=converter(elem);
    for(unsigned int i = 0; i < B; i++){
        pos = h_mul(h, i, B); //calculo da função hash
        if(tabela->dados[pos] == NULL){
            return 0; //elemento não está presente na tabela
        }
       if(!strcmp(tabela->dados[pos], elem)){
            return 1; //elemento encontrado
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
    unsigned int N = 50000;
    unsigned int M = 70000;
    unsigned int B = 150001;

    unsigned int colisoes_h_div = 0;
    unsigned colisoes_h_mul = 0;

    unsigned int encontrados_h_div = 0;
    unsigned int encontrados_h_mul = 0;

    hash tabela;

    string* insercoes = ler_strings("strings_entrada.txt", N);
    string* consultas = ler_strings("strings_busca.txt", M);


    // cria tabela hash com hash por divisão
    
    criar_hash(&tabela, B);

    // inserção dos dados na tabela hash usando hash por divisão
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        // inserir insercoes[i] na tabela hash
        if(inserir_div(&tabela, insercoes[i], B)>0){
          colisoes_h_div++;
        }
    }
    double tempo_insercao_h_div = finaliza_tempo();

    // consulta dos dados na tabela hash usando hash por divisão
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        // buscar consultas[i] na tabela hash
        if(busca_div(&tabela, consultas[i], B)==1){
          encontrados_h_div++;
        }

    }
    double tempo_busca_h_div = finaliza_tempo();
    
    // limpa a tabela hash com hash por divisão
    limpar_hash(&tabela, B);

    // cria tabela hash com hash por divisão
    criar_hash(&tabela, B);

    // inserção dos dados na tabela hash usando hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        // inserir insercoes[i] na tabela hash
        if(inserir_mul(&tabela, insercoes[i], B)>0){
            colisoes_h_mul++;
        }
    }
    double tempo_insercao_h_mul = finaliza_tempo();

    // busca dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        // buscar consultas[i] na tabela hash
        if(busca_mul(&tabela, consultas[i], B)==1){
            encontrados_h_mul++;
        }
    }
    double tempo_busca_h_mul = finaliza_tempo();

    // limpa a tabela hash com hash por multiplicação
    
    limpar_hash(&tabela, B);
  
    
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

    free(insercoes);
    free(consultas);
    
    return 0;
}
