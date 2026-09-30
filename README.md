# Banco INF101 - Etapa 1

Implementacao em C++ do sistema de registro e gestao de contas bancarias solicitado no trabalho de INF101.

## O que o programa faz

- Mantem o menu em execucao com `do...while` e seleciona cada acao com `switch`.
- Cadastra, consulta e verifica o saldo de contas.
- Altera o tipo entre conta corrente e poupanca.
- Ativa ou desativa uma conta.
- Valida numero de conta, CPF, tipo de conta e saldo inicial.
- Impede operacoes de saldo e alteracao de tipo em contas inativas.
- Implementa o desafio: suporta ate cinco contas com vetores paralelos.

## Como compilar e executar

No terminal, dentro desta pasta, use um compilador C++ com suporte a C++17:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o banco
./banco
```

No Windows com MinGW, o executavel sera `banco.exe`:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o banco.exe
.\banco.exe
```

## Observacao para a apresentacao

Os dados ficam apenas na memoria enquanto o programa esta aberto, pois persistencia em arquivos pertence a etapa posterior descrita no enunciado.
