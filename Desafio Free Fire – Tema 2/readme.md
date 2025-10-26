# Projeto: Desafio Free Fire — Torre de Resgate Estratégico

Este projeto é inspirado na última fase da batalha em Free Fire, onde o jogador precisa montar um plano estratégico para escapar da ilha. Para isso, é necessário construir uma **torre de resgate** com os componentes certos, na exata ordem e prioridade, utilizando técnicas avançadas de Estrutura de Dados.

## Contexto do Desafio

Você chegou à última safe zone do jogo — apenas os mais habilidosos sobrevivem! Para vencer, será preciso organizar de forma estratégica os **componentes da sua torre de resgate**, escolhendo o melhor método de ordenação e realizando uma busca eficiente pelo item-chave que libera a ativação da torre.  
O objetivo é consolidar os conhecimentos de programação, simular situações reais de tomada de decisão em Free Fire e fortalecer o domínio sobre algoritmos clássicos.

## Funcionalidades

- **Cadastro dos componentes:** Cada item representa parte essencial da construção da torre, com nome, tipo (controle, suporte, propulsão etc.) e prioridade de uso (1 a 10).
- **Escolha da estratégia de ordenação:**
  - **Bubble Sort:** Ordena por nome, simulando organização tática dos jogadores.
  - **Insertion Sort:** Ordena por tipo, facilitando divisão de funções na equipe.
  - **Selection Sort:** Ordena por prioridade, determinando o que é mais urgente na missão de fuga.
- **Busca binária:** Localiza rapidamente o **componente-chave** — aquele que destrava a próxima dinâmica do jogo, viabilizando o resgate.
- **Análise de desempenho:** Exibe o número de comparações realizadas e o tempo de execução dos algoritmos, simulando a pressão das decisões em partidas intensas de Free Fire.
- **Interface intuitiva:** Menu interativo que permite testar diferentes estratégias e visualizar o resultado em tempo real.

## Estrutura do Código

- `Componente` — struct que armazena nome, tipo e prioridade.
- Funções separadas para cada algoritmo de ordenação e busca.
- Modularização e comentários facilitando adaptação e entendimento do código por toda a equipe.
- Relatório de desempenho detalhado ao final de cada operação.

## Como Executar

1. Compile o arquivo principal (exemplo usando gcc):

   ```bash
   gcc projeto_freefire.c -o torre_resgate
   ```

2. Execute:

   ```bash
   ./torre_resgate
   ```

3. Siga o menu para cadastrar componentes, escolher métodos de ordenação, buscar o componente-chave e visualizar os resultados — como se estivesse em uma dinâmica de estratégia de Free Fire!

## Exemplos de Cenários

- Cadastro de itens como “chip central”, “propulsor turbo”, “escudo avançado”.
- Simulação de estratégias táticas para resgate.
- Busca pelo componente especial que desbloqueia a saída da ilha.

**Observação:**  
Este projeto une conceitos fundamentais de Estrutura de Dados à emoção das estratégias do Free Fire, tornando o estudo mais envolvente e prático. Bom jogo, boa sorte e boa entrega!
