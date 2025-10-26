# Projeto: Tetrix — Gerenciador Estratégico de Peças (Fila Circular + Pilha Reserva)

Este projeto simula o gerenciamento tático de peças no universo do jogo Tetrix, usando estruturas de dados clássicas: fila circular e pilha linear.

## Contexto do Desafio

Você precisa controlar as peças do jogo de forma ágil e inteligente, usando uma fila circular (5 espaços) e uma pilha reserva (3 espaços). Cada ação — jogar, reservar, usar, trocar peças — depende da estratégia escolhida.

## Funcionalidades

- **Fila circular**: Gerenciamento contínuo de peças, sempre cheia por geração automática.
- **Pilha reserva**: Guarda até 3 peças para uso estratégico.
- **Ações disponíveis**:
  - Jogar peça da frente da fila (remove e gera nova peça automaticamente)
  - Reservar peça da fila (move para pilha, caso haja espaço)
  - Usar peça reservada (remove do topo da pilha)
  - Trocar peça da frente da fila com topo da pilha
  - Troca múltipla de 3 peças entre fila e pilha
  - Visualização do estado atual após cada ação
  - Encerrar jogo

## Estrutura do Código

- `Peca`: struct que representa a peça individual (nome: 'I', 'O', 'T', 'L', id único)
- `Fila`: estrutura circular de 5 peças, gerando automaticamente sempre que peça é usada ou reservada
- `Pilha`: estrutura linear de 3 peças para reserva
- Funções separadas para cada operação, totalmente comentadas e organizadas

## Como Executar

1. Compile o código principal (exemplo usando gcc):

   ```bash
   gcc tetrix.c -o tetrix
   ```

2. Execute o programa:

   ```bash
   ./tetrix
   ```

3. Utilize o menu para testar todas as operações, conforme regras e exemplos da disciplina.

## Exemplos de Estratégia

- Alternar trocas entre fila e pilha para otimizar o uso das peças.
- Reservar peças cruciais para uso em momentos decisivos.
- Simular jogadas do Tetrix de forma didática e divertida.

---

**Observação:**  
O desafio reforça o uso de fila circular e pilha linear, além de consolidar conceitos de manipulação eficiente de estruturas em linguagem C, conforme exigências da disciplina de Estruturas de Dados.
