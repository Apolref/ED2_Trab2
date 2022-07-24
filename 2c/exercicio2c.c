#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
//typedef unsigned char bool;
#define TRUE  1
#define FALSE 0

// Definição do tipo string
typedef char * string;

#define MAX_STRING_LEN 20

typedef struct node{ //TAD
    char inf[MAX_STRING_LEN];
    struct node *next;
} Node;

typedef struct node *List;

// struct hash
typedef struct{
    List *vect;
} hash_table;

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

unsigned h_div(unsigned x, unsigned B)
{
    return x % B;
}

unsigned h_mul(unsigned x, unsigned B)
{
    const double A = 0.6180;
    return fmod(x * A, 1) * B;
}

List *new_node(unsigned TAM){
    List *x = (List *) calloc(TAM, sizeof(List));
    return x;
}

hash_table *newH(unsigned X, hash_table *t){
    t->vect = (node**) calloc(1, sizeof(hash_table));
    t->vect = new_node(X);
    return t;
}

int search_node(string x, Node *structure){
    while(structure != NULL){
        if(strcmp(structure->inf, x) == 0)
            return 0;
        return search_node(x, structure->next);
    }
    return -1;
}

int add_node(string s, List *X){
    int collision = 0;
    Node *newNode = (Node *) calloc(MAX_STRING_LEN ,sizeof(Node));
    if (!(*X == NULL))
        collision = 1;
    strcpy(newNode->inf, s);
    newNode->next = (*X);
    (*X) = newNode;
    return collision;
}

int add(string s, unsigned X, hash_table *t, unsigned (*fHash)(unsigned, unsigned)){
    unsigned B, A;
    A = converter(s);
    B = fHash(A, X);
    if(search_node(s, t->vect[B]) == 0 || add_node(s, &t->vect[B]) == 0)
        return 0;
    return 1;
}

int search(string s,  unsigned X, hash_table *t, unsigned (*fHash)(unsigned, unsigned)){
    unsigned B, A;
    A = converter(s);
    B = fHash(A, X);
    if(search_node(s, t->vect[B]) == 0)
        return 1;
    return 0;
}

void free_hash(unsigned X, hash_table *t){
    int i;
    for (i= 0; i < X; i++)
        free(t->vect[i]);
    free(t->vect);
}

int main(int argc, char const *argv[])
{
    const int N = 50000;
    const int M = 70000;
    const int B = 150001;

    unsigned colisoes_h_div = 0;
    unsigned colisoes_h_mul = 0;

    unsigned encontrados_h_div = 0;
    unsigned encontrados_h_mul = 0;

    string* insercoes = ler_strings("strings_entrada.txt", N);
    string* consultas = ler_strings("strings_busca.txt", M);


    hash_table tabela1; //cria tabela hash com hash por divisão
    newH(B, &tabela1);

    // inserção dos dados na tabela hash com hash por divisão
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        if(add(insercoes[i], B, &tabela1, &h_div))
            colisoes_h_div++;
    }
    double tempo_insercao_h_div = finaliza_tempo();

    // busca dos dados na tabela hash com hash por divisão
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        if (search( consultas[i], B,&tabela1, &h_div))
            encontrados_h_div++;
    }
    double tempo_busca_h_div = finaliza_tempo();

    // destroi tabela hash com hash por divisão
    free_hash(B, &tabela1);



    hash_table tabela2;// cria tabela hash com hash por multiplicação
    newH(B, &tabela2);

    // inserção dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        if(add(insercoes[i], B, &tabela2, &h_mul))
            colisoes_h_mul++;
    }

    double tempo_insercao_h_mul = finaliza_tempo();

    // busca dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        if (search( consultas[i], B,&tabela2, &h_mul))
            encontrados_h_mul++;
    }

    double tempo_busca_h_mul = finaliza_tempo();

    // destroi tabela hash com hash por multiplicação
    free_hash(B, &tabela2);


    printf("Hash por Divisao\n");
    printf("Colisoes na insercao: %d\n", colisoes_h_div);
    printf("Tempo de insercao   : %fs\n", tempo_insercao_h_div);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_div);
    printf("Itens encontrados   : %d\n", encontrados_h_div);
    printf("\n");
    printf("Hash por Multiplicacao\n");
    printf("Colisoes na insercao: %d\n", colisoes_h_mul);
    printf("Tempo de insercao   : %fs\n", tempo_insercao_h_mul);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_mul);
    printf("Itens encontrados   : %d\n", encontrados_h_mul);

    return 0;
}
