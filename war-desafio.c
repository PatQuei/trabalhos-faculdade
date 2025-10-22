#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura de território
typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Cria missões estratégicas
void criarMissoes(char *missoes[], int totalMissoes)
{
    missoes[0] = "Conquistar 3 territórios seguidos";
    missoes[1] = "Eliminar todas as tropas da cor vermelha";
    missoes[2] = "Ter mais de 20 tropas";
    missoes[3] = "Conquistar pelo menos dois territórios";
    missoes[4] = "Manter o território inicial sem perder tropas";
}

// Sorteia missão estratégica para o jogador
void atribuirMissao(char *destino, char *missoes[], int totalMissoes)
{
    int sorteada = rand() % totalMissoes;
    strcpy(destino, missoes[sorteada]);
}

// Exibe missão do jogador (apenas uma vez)
void exibirMissao(char *missao)
{
    printf("\nSua missão estratégica: %s\n\n", missao);
}

// Avaliação simples das missões (adapte conforme o enunciado/creatividade)
int verificarMissao(char *missao, Territorio *mapa, int n)
{
    if (strstr(missao, "3 territórios"))
    {
        // Exemplo: verifica se existe ao menos 3 territórios da mesma cor
        int maior = 1;
        for (int i = 1, cont = 1; i < n; i++)
        {
            if (strcmp(mapa[i].cor, mapa[i - 1].cor) == 0)
                cont++;
            else
                cont = 1;
            if (cont > maior)
                maior = cont;
        }
        return maior >= 3;
    }
    else if (strstr(missao, "vermelha"))
    {
        // Exemplo: todas tropas vermelhas igual a zero
        for (int i = 0; i < n; i++)
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0)
                return 0;
        return 1;
    }
    else if (strstr(missao, "20 tropas"))
    {
        // Soma de tropas maior que 20
        int soma = 0;
        for (int i = 0; i < n; i++)
            soma += mapa[i].tropas;
        return soma > 20;
    }
    else if (strstr(missao, "dois territórios"))
    {
        // Exemplo: número de territórios da cor do jogador >= 2
        int cor_jogador = 0;
        char cor_ref[10];
        strcpy(cor_ref, mapa[0].cor);
        for (int i = 0; i < n; i++)
            if (strcmp(mapa[i].cor, cor_ref) == 0)
                cor_jogador++;
        return cor_jogador >= 2;
    }
    else if (strstr(missao, "inicial"))
    {
        // Território inicial sem perder tropas
        return mapa[0].tropas > 0;
    }
    return 0;
}

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio *mapa, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nCadastro do território %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibe todos os territórios
void exibirTerritorios(Territorio *mapa, int n)
{
    printf("\n=== Territórios ===\n");
    for (int i = 0; i < n; i++)
    {
        printf("ID %d: %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simula ataque entre territórios
void atacar(Territorio *atacante, Territorio *defensor)
{
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;

    printf("\nAtaque: %s (%s, %d tropas) --> %s (%s, %d tropas)\n",
           atacante->nome, atacante->cor, atacante->tropas, defensor->nome, defensor->cor, defensor->tropas);

    printf("Dado atacante: %d | Dado defensor: %d\n", dado_atacante, dado_defensor);

    if (dado_atacante > dado_defensor)
    {
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas /= 2;
        printf("O atacante venceu! Agora %s é da cor %s com %d tropas.\n", defensor->nome, defensor->cor, defensor->tropas);
    }
    else
    {
        if (atacante->tropas > 1)
            atacante->tropas--;
        printf("O atacante perdeu! Agora tem %d tropas.\n", atacante->tropas);
    }
}

// Libera toda memória alocada
void liberarMemoria(Territorio *mapa, char *missao)
{
    free(mapa);
    free(missao);
}

int main()
{
    srand(time(NULL));

    int n = 5;
    Territorio *mapa = (Territorio *)calloc(n, sizeof(Territorio));
    if (mapa == NULL)
    {
        printf("Erro ao alocar memória dos territórios!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);
    exibirTerritorios(mapa, n);

    // Missões
    int totalMissoes = 5;
    char *missoes[5];
    criarMissoes(missoes, totalMissoes);

    char *missaoJogador = (char *)malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    char continuar;
    int venceu = 0;

    do
    {
        int id_atacante, id_defensor;
        exibirTerritorios(mapa, n);
        printf("\nSelecione o ID do atacante: ");
        scanf("%d", &id_atacante);
        printf("Selecione o ID do defensor: ");
        scanf("%d", &id_defensor);

        if (id_atacante == id_defensor ||
            strcmp(mapa[id_atacante].cor, mapa[id_defensor].cor) == 0)
        {
            printf("Ataque inválido! Escolha territórios de cores diferentes.\n");
        }
        else
        {
            atacar(&mapa[id_atacante], &mapa[id_defensor]);
        }

        if (verificarMissao(missaoJogador, mapa, n))
        {
            printf("\nParabéns! Você cumpriu sua missão: %s\n", missaoJogador);
            venceu = 1;
            break;
        }

        printf("Deseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    if (!venceu)
        printf("\nVocê não cumpriu sua missão!\n");

    liberarMemoria(mapa, missaoJogador);
    printf("Programa finalizado. Memória liberada.\n");
    return 0;
}
