#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estruturas e constantes
#define MAX_SALAS 7
#define MAX_HASHTBL 11
#define MAX_NOME 50
#define MAX_PISTA 50
#define MAX_SUSPEITO 30

// Estrutura do cômodo na árvore binária
typedef struct sala
{
    char nome[MAX_NOME];
    char pista[MAX_PISTA];
    struct sala *esq, *dir;
} Sala;

// Estrutura de nó BST para pistas
typedef struct bstnode
{
    char pista[MAX_PISTA];
    struct bstnode *esq, *dir;
} BSTNode;

// Estrutura de entrada na tabela hash
typedef struct hashitem
{
    char pista[MAX_PISTA];
    char suspeito[MAX_SUSPEITO];
    struct hashitem *prox;
} HashItem;

// Função para criar cômodo da mansão
Sala *criarSala(const char *nome, const char *pista)
{
    Sala *nova = (Sala *)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esq = nova->dir = NULL;
    return nova;
}

// Função para inserir pista coletada na BST
BSTNode *inserirPista(BSTNode *raiz, const char *pista)
{
    if (!raiz)
    {
        BSTNode *novo = (BSTNode *)malloc(sizeof(BSTNode));
        strcpy(novo->pista, pista);
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserirPista(raiz->esq, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->dir = inserirPista(raiz->dir, pista);
    return raiz;
}

// Função hash simples (soma dos caracteres da pista)
int hash(const char *str)
{
    int soma = 0;
    for (int i = 0; str[i]; i++)
        soma += str[i];
    return soma % MAX_HASHTBL;
}

// Insere associação pista-suspeito na hash
void inserirNaHash(HashItem *tbl[], const char *pista, const char *suspeito)
{
    int idx = hash(pista);
    HashItem *novo = (HashItem *)malloc(sizeof(HashItem));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tbl[idx];
    tbl[idx] = novo;
}

// Consulta o suspeito correspondente à pista
const char *encontrarSuspeito(HashItem *tbl[], const char *pista)
{
    int idx = hash(pista);
    for (HashItem *it = tbl[idx]; it; it = it->prox)
        if (strcmp(it->pista, pista) == 0)
            return it->suspeito;
    return NULL;
}

// Percorre BST e conta quantas pistas apontam para o suspeito acusado
int contarPistasSuspeito(BSTNode *raiz, HashItem *tbl[], const char *suspeito)
{
    if (!raiz)
        return 0;
    int soma = contarPistasSuspeito(raiz->esq, tbl, suspeito) + contarPistasSuspeito(raiz->dir, tbl, suspeito);
    const char *sus = encontrarSuspeito(tbl, raiz->pista);
    return (sus && strcmp(sus, suspeito) == 0) ? soma + 1 : soma;
}

// Lista em ordem as pistas coletadas (BST)
void listarPistas(BSTNode *raiz)
{
    if (!raiz)
        return;
    listarPistas(raiz->esq);
    printf("- %s\n", raiz->pista);
    listarPistas(raiz->dir);
}

// Explora as salas binárias e coleta pistas
void explorarSalas(Sala *atual, BSTNode **arvore, HashItem *tbl[])
{
    char op;
    if (!atual)
        return;
    printf("\nVocê entrou na sala '%s'.\n", atual->nome);
    if (strlen(atual->pista))
    {
        printf("Pista encontrada: %s\n", atual->pista);
        *arvore = inserirPista(*arvore, atual->pista);
    }
    else
    {
        printf("Não há pista nesta sala.\n");
    }
    printf("Escolha:\nE - Esquerda\nD - Direita\nS - Sair\nOpção: ");
    scanf(" %c", &op);
    if (op == 'E' || op == 'e')
        explorarSalas(atual->esq, arvore, tbl);
    else if (op == 'D' || op == 'd')
        explorarSalas(atual->dir, arvore, tbl);
}

// Monta manualmente o mapa fixo da mansão
void montarMansao(Sala **raiz)
{
    *raiz = criarSala("Hall", "Pegada ensanguentada");             // Pista 1
    (*raiz)->esq = criarSala("Cozinha", "Faca sumida");            // Pista 2
    (*raiz)->dir = criarSala("Biblioteca", "Livro rasgado");       // Pista 3
    (*raiz)->esq->esq = criarSala("Adega", "Taça quebrada");       // Pista 4
    (*raiz)->esq->dir = criarSala("Despensa", "Luvas sujas");      // Pista 5
    (*raiz)->dir->esq = criarSala("Estúdio", "Gravação suspeita"); // Pista 6
    (*raiz)->dir->dir = criarSala("Jardim", "Pegadas de lama");    // Pista 7
}

// Monta manualmente a tabela hash de pistas e suspeitos
void montarTabelaHash(HashItem *tbl[])
{
    for (int i = 0; i < MAX_HASHTBL; i++)
        tbl[i] = NULL;
    inserirNaHash(tbl, "Pegada ensanguentada", "Mordomo");
    inserirNaHash(tbl, "Faca sumida", "Cozinheira");
    inserirNaHash(tbl, "Livro rasgado", "Bibliotecária");
    inserirNaHash(tbl, "Taça quebrada", "Cônego");
    inserirNaHash(tbl, "Luvas sujas", "Jardineiro");
    inserirNaHash(tbl, "Gravação suspeita", "Dama de vermelho");
    inserirNaHash(tbl, "Pegadas de lama", "Jardineiro");
}

// Fase final: acusação e verificação automática
void verificarSuspeitoFinal(BSTNode *arvore, HashItem *tbl[])
{
    char suspeito[MAX_SUSPEITO];
    printf("\nPistas coletadas:\n");
    listarPistas(arvore);
    printf("\nInforme o nome do suspeito para acusação: ");
    scanf(" %[^\n]", suspeito);
    int qtde = contarPistasSuspeito(arvore, tbl, suspeito);
    if (qtde >= 2)
        printf("\nACUSAÇÃO SUSTENTADA: %d pistas apontam para '%s'. Caso encerrado!\n", qtde, suspeito);
    else
        printf("\nACUSAÇÃO FRÁGIL: apenas %d pista(s) apontam para '%s'. Mistério permanece!\n", qtde, suspeito);
}

int main()
{
    Sala *mansao = NULL;
    BSTNode *arvorePistas = NULL;
    HashItem *tabelaHash[MAX_HASHTBL];

    montarMansao(&mansao);
    montarTabelaHash(tabelaHash);

    printf("\nDetective Quest — Desafio Mestre\nExplore a mansão e resolva o mistério!\n");
    explorarSalas(mansao, &arvorePistas, tabelaHash);

    verificarSuspeitoFinal(arvorePistas, tabelaHash);
    return 0;
}
