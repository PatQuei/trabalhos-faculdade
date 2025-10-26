# Projeto: Detective Quest — Mansão das Evidências (Árvore Binária, BST e Tabela Hash)

Este projeto simula uma investigação em uma mansão misteriosa, onde o jogador coleta pistas, relaciona-as a suspeitos e realiza a acusação final usando estruturas dinâmicas em C.

## Contexto do Desafio

No último capítulo de Detective Quest, o investigador explora um mapa de cômodos representado por uma árvore binária, coleta pistas de cada sala e associa essas pistas aos suspeitos por meio de uma tabela hash eficiente. O julgamento final considera se há evidências suficientes para sustentar a acusação!

## Funcionalidades

- **Árvore binária de salas**: Estrutura fixa e manual do mapa da mansão.
- **Árvore BST**: Armazena ordenadamente as pistas coletadas durante a exploração.
- **Tabela hash de suspeitos**: Associa cada pista a um suspeito.
- **Exploração interativa**: Jogador escolhe percursos (esquerda/direita/sair), coleta pistas e visualiza o avanço.
- **Acusação automática**: O sistema verifica quantas evidências sustentam a decisão final.

## Estrutura do Código

- `Sala`: struct representando o cômodo, navegável pela árvore binária
- `BSTNode`: nó da árvore de pistas
- `HashItem`: entrada da tabela hash para suspeitos
- Funções separadas para montar mapa, inserir pistas, explorar salas, verificar suspeitos e estruturar o julgamento

## Como Executar

1. Compile o arquivo principal:

   ```bash
   gcc detective.c -o detective
   ```

2. Execute:

   ```bash
   ./detective
   ```

3. Siga as instruções — explore salas, colete pistas e faça sua acusação final fundamentada!

## Exemplos de Estratégia

- Percorrer as salas para maximizar a coleta de pistas.
- Relacionar as pistas obtidas ao suspeito correto.
- Avaliar sua acusação com base na quantidade de evidências.

## Entrega

- Projeto pronto para avaliação, com código organizado, modularizado e comentado.
- Submeta o link do repositório pelo sistema SAVA conforme orientações.
