#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20

typedef struct
{
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Função para mostrar todos os componentes
void mostrarComponentes(Componente componentes[], int n)
{
    printf("\nComponentes:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%02d - Nome: %s | Tipo: %s | Prioridade: %d\n", i + 1, componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
}

// Bubble Sort por nome
int bubbleSortNome(Componente componentes[], int n)
{
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0)
            {
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
    return comparacoes;
}

// Insertion Sort por tipo
int insertionSortTipo(Componente componentes[], int n)
{
    int comparacoes = 0;
    for (int i = 1; i < n; i++)
    {
        Componente chave = componentes[i];
        int j = i - 1;
        while (j >= 0 && ++comparacoes && strcmp(componentes[j].tipo, chave.tipo) > 0)
        {
            componentes[j + 1] = componentes[j];
            j--;
        }
        componentes[j + 1] = chave;
    }
    return comparacoes;
}

// Selection Sort por prioridade
int selectionSortPrioridade(Componente componentes[], int n)
{
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            comparacoes++;
            if (componentes[j].prioridade < componentes[min].prioridade)
                min = j;
        }
        if (min != i)
        {
            Componente temp = componentes[i];
            componentes[i] = componentes[min];
            componentes[min] = temp;
        }
    }
    return comparacoes;
}

// Busca binária por nome (após ordenar por nome)
int buscaBinariaPorNome(Componente componentes[], int n, char chave[])
{
    int inicio = 0, fim = n - 1, meio, comparacoes = 0;
    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(componentes[meio].nome, chave);
        if (cmp == 0)
            return meio; // Encontrado!
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1; // Não encontrado
}

// Função para medir tempo de execução de cada sort
double medirTempo(int (*algoritmo)(Componente[], int), Componente componentes[], int n, int *comparacoes)
{
    clock_t inicio = clock();
    *comparacoes = algoritmo(componentes, n);
    clock_t fim = clock();
    return ((double)(fim - inicio) / CLOCKS_PER_SEC);
}

int main()
{
    Componente componentes[MAX_COMP];
    int n = 0, escolha, comparacoes;
    char chave[30];

    // Cadastro dos componentes
    printf("Quantos componentes deseja cadastrar? (1-%d): ", MAX_COMP);
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++)
    {
        printf("\nComponente #%d\nNome: ", i + 1);
        fgets(componentes[i].nome, 30, stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = 0;
        printf("Tipo: ");
        fgets(componentes[i].tipo, 20, stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = 0;
        printf("Prioridade (1-10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar();
    }

    // Menu de estratégias
    do
    {
        printf("\nEscolha a ordenação:\n1 - Bubble Sort (Nome)\n2 - Insertion Sort (Tipo)\n3 - Selection Sort (Prioridade)\n4 - Buscar componente-chave por nome\n0 - Sair\nOpção: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha)
        {
        case 1:
        {
            double tempo = medirTempo(bubbleSortNome, componentes, n, &comparacoes);
            printf("\n* Bubble Sort concluído! Comparações: %d | Tempo: %.6f seg", comparacoes, tempo);
            mostrarComponentes(componentes, n);
            break;
        }
        case 2:
        {
            double tempo = medirTempo(insertionSortTipo, componentes, n, &comparacoes);
            printf("\n* Insertion Sort concluído! Comparações: %d | Tempo: %.6f seg", comparacoes, tempo);
            mostrarComponentes(componentes, n);
            break;
        }
        case 3:
        {
            double tempo = medirTempo(selectionSortPrioridade, componentes, n, &comparacoes);
            printf("\n* Selection Sort concluído! Comparações: %d | Tempo: %.6f seg", comparacoes, tempo);
            mostrarComponentes(componentes, n);
            break;
        }
        case 4:
        {
            printf("Informe o nome do componente-chave para busca binária: ");
            fgets(chave, 30, stdin);
            chave[strcspn(chave, "\n")] = 0;
            int pos = buscaBinariaPorNome(componentes, n, chave);
            if (pos != -1)
            {
                printf("\nComponente-chave encontrado na posição: %d\n", pos + 1);
            }
            else
            {
                printf("\nComponente-chave NÃO encontrado!\n");
            }
            break;
        }
        case 0:
            printf("Encerrando programa...\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);

    return 0;
}
