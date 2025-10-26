#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definições dos tipos e tamanhos das estruturas
#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct
{
    char nome; // 'I', 'O', 'T', 'L'
    int id;    // identificador único
} Peca;

// Fila circular de peças
typedef struct
{
    Peca dados[TAM_FILA];
    int ini, fim, qtd;
    int proxID;
} Fila;

// Pilha de reserva
typedef struct
{
    Peca dados[TAM_PILHA];
    int topo;
} Pilha;

// Gera uma nova peça com id único e nome aleatório
Peca gerarPeca(int id)
{
    char nomes[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = nomes[rand() % 4];
    nova.id = id;
    return nova;
}

// Inicializa fila cheia de peças
void inicializaFila(Fila *f)
{
    f->ini = 0;
    f->fim = 0;
    f->qtd = 0;
    f->proxID = 0;
    for (int i = 0; i < TAM_FILA; i++)
    {
        f->dados[i] = gerarPeca(f->proxID++);
        f->fim = (f->fim + 1) % TAM_FILA;
        f->qtd++;
    }
}

// Inicializa pilha vazia
void inicializaPilha(Pilha *p)
{
    p->topo = -1;
}

// Remove peça da frente da fila
Peca removerFila(Fila *f)
{
    Peca retirado = {'.', -1};
    if (f->qtd > 0)
    {
        retirado = f->dados[f->ini];
        f->dados[f->ini] = gerarPeca(f->proxID++);
        f->ini = (f->ini + 1) % TAM_FILA;
    }
    return retirado;
}

// Adiciona peça no topo da pilha
int empilha(Pilha *p, Peca item)
{
    if (p->topo < TAM_PILHA - 1)
    {
        p->topo++;
        p->dados[p->topo] = item;
        return 1;
    }
    return 0;
}

// Remove peça do topo da pilha
Peca desempilha(Pilha *p)
{
    Peca retirado = {'.', -1};
    if (p->topo >= 0)
    {
        retirado = p->dados[p->topo];
        p->topo--;
        return retirado;
    }
    return retirado;
}

// Move peça da fila para pilha
int reservarPeca(Fila *f, Pilha *p)
{
    if (p->topo < TAM_PILHA - 1)
    {
        Peca retirada = removerFila(f);
        if (retirada.id != -1)
            return empilha(p, retirada);
    }
    return 0;
}

// Troca peça da frente da fila com topo da pilha
int trocarSimples(Fila *f, Pilha *p)
{
    if (p->topo >= 0)
    {
        Peca temp = f->dados[f->ini];
        f->dados[f->ini] = p->dados[p->topo];
        p->dados[p->topo] = temp;
        return 1;
    }
    return 0;
}

// Troca múltipla entre os 3 primeiros da fila com os 3 da pilha
int trocaMultipla(Fila *f, Pilha *p)
{
    if (f->qtd >= 3 && p->topo >= 2)
    {
        for (int i = 0; i < 3; i++)
        {
            int idxFila = (f->ini + i) % TAM_FILA;
            Peca temp = f->dados[idxFila];
            f->dados[idxFila] = p->dados[p->topo - i];
            p->dados[p->topo - i] = temp;
        }
        return 1;
    }
    return 0;
}

// Exibe o estado atual da fila e pilha
void exibirEstado(Fila f, Pilha p)
{
    printf("\nFila de peças: ");
    for (int i = 0; i < TAM_FILA; i++)
    {
        int idx = (f.ini + i) % TAM_FILA;
        printf("[%c %d] ", f.dados[idx].nome, f.dados[idx].id);
    }
    printf("\nPilha de reserva (Topo -> base): ");
    for (int i = p.topo; i >= 0; i--)
    {
        printf("[%c %d] ", p.dados[i].nome, p.dados[i].id);
    }
    printf("\n");
}

int main()
{
    Fila fila;
    Pilha pilha;
    int op;
    srand(time(NULL));

    inicializaFila(&fila);
    inicializaPilha(&pilha);

    do
    {
        exibirEstado(fila, pilha);
        printf("\nOpções disponíveis:\n"
               "1 - Jogar peça da frente da fila\n"
               "2 - Enviar peça da fila para pilha de reserva\n"
               "3 - Usar peça da pilha de reserva\n"
               "4 - Trocar a peça da frente da fila com o topo da pilha\n"
               "5 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n"
               "0 - Sair\n"
               "Opção: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
        { // Jogar peça da frente da fila
            Peca p = removerFila(&fila);
            printf("Peça jogada [%c %d]!\n", p.nome, p.id);
            break;
        }
        case 2:
        { // Reservar peça da fila na pilha
            if (reservarPeca(&fila, &pilha))
                printf("Peça reservada com sucesso!\n");
            else
                printf("Não foi possível reservar (pilha cheia).\n");
            break;
        }
        case 3:
        { // Usar peça da pilha de reserva
            Peca p = desempilha(&pilha);
            if (p.id != -1)
                printf("Peça usada [%c %d]!\n", p.nome, p.id);
            else
                printf("Pilha vazia!\n");
            break;
        }
        case 4:
        { // Troca simples
            if (trocarSimples(&fila, &pilha))
                printf("Troca realizada com sucesso!\n");
            else
                printf("Não foi possível trocar.\n");
            break;
        }
        case 5:
        { // Troca múltipla
            if (trocaMultipla(&fila, &pilha))
                printf("Troca múltipla realizada!\n");
            else
                printf("Não foi possível realizar a troca múltipla.\n");
            break;
        }
        case 0:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (op != 0);

    return 0;
}
