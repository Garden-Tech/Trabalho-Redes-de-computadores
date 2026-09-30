#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Desafio da etapa: usar vetores paralelos para permitir ate 5 contas.
// Cada indice representa uma conta completa. Por exemplo, numeroConta[0],
// nomeCliente[0] e saldo[0] pertencem ao mesmo cliente.
const int MAX_CONTAS = 5;

int numeroConta[MAX_CONTAS]{};
string nomeCliente[MAX_CONTAS];
string cpf[MAX_CONTAS];
int tipoConta[MAX_CONTAS]{}; // 1 = Corrente | 2 = Poupanca
double saldo[MAX_CONTAS]{};
bool contaAtiva[MAX_CONTAS]{};
int totalContas = 0;

void limparEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int lerInteiro(const string& mensagem) {
    int valor;
    while (true) {
        cout << mensagem;
        if (cin >> valor) {
            limparEntrada();
            return valor;
        }

        cout << "Entrada invalida. Digite apenas um numero inteiro.\n";
        limparEntrada();
    }
}

double lerDouble(const string& mensagem) {
    double valor;
    while (true) {
        cout << mensagem;
        if (cin >> valor) {
            limparEntrada();
            return valor;
        }

        cout << "Entrada invalida. Digite um valor numerico.\n";
        limparEntrada();
    }
}

string lerTextoObrigatorio(const string& mensagem) {
    string texto;
    do {
        cout << mensagem;
        getline(cin, texto);
        if (texto.empty()) {
            cout << "Este campo nao pode ficar vazio.\n";
        }
    } while (texto.empty());

    return texto;
}

string somenteDigitos(const string& texto) {
    string digitos;
    for (char caractere : texto) {
        if (isdigit(static_cast<unsigned char>(caractere))) {
            digitos += caractere;
        }
    }
    return digitos;
}

string lerCpf() {
    string entrada;
    while (true) {
        entrada = lerTextoObrigatorio("CPF (apenas numeros ou formatado): ");
        string cpfLimpo = somenteDigitos(entrada);
        if (cpfLimpo.length() == 11) {
            return cpfLimpo;
        }
        cout << "CPF invalido. Informe exatamente 11 digitos.\n";
    }
}

string descricaoTipo(int tipo) {
    return tipo == 1 ? "Corrente" : "Poupanca";
}

string formatarCpf(const string& cpfSemMascara) {
    return cpfSemMascara.substr(0, 3) + "." + cpfSemMascara.substr(3, 3) + "." +
           cpfSemMascara.substr(6, 3) + "-" + cpfSemMascara.substr(9, 2);
}

int localizarConta(int numero) {
    for (int i = 0; i < totalContas; i++) {
        if (numeroConta[i] == numero) {
            return i;
        }
    }
    return -1;
}

int solicitarContaExistente() {
    if (totalContas == 0) {
        cout << "Nenhuma conta foi cadastrada ainda.\n";
        return -1;
    }

    int numero = lerInteiro("Numero da conta: ");
    int indice = localizarConta(numero);
    if (indice == -1) {
        cout << "Conta nao encontrada.\n";
    }
    return indice;
}

void exibirCabecalho() {
    cout << "\n========================================\n";
    cout << "          BANCO INF101 - P1\n";
    cout << "========================================\n";
}

void cadastrarConta() {
    if (totalContas == MAX_CONTAS) {
        cout << "Limite de " << MAX_CONTAS << " contas atingido.\n";
        return;
    }

    cout << "\n--- Cadastro de conta ---\n";
    int novoNumero;
    do {
        novoNumero = lerInteiro("Numero da conta: ");
        if (novoNumero <= 0) {
            cout << "O numero da conta deve ser maior que zero.\n";
        } else if (localizarConta(novoNumero) != -1) {
            cout << "Ja existe uma conta com esse numero.\n";
            novoNumero = 0;
        }
    } while (novoNumero <= 0);

    // A sequencia abaixo segue os campos solicitados no enunciado.
    string novoNome = lerTextoObrigatorio("Nome do titular: ");
    string novoCpf = lerCpf();

    int novoTipo;
    do {
        novoTipo = lerInteiro("Tipo (1 - Corrente | 2 - Poupanca): ");
        if (novoTipo != 1 && novoTipo != 2) {
            cout << "Tipo invalido. Escolha 1 ou 2.\n";
        }
    } while (novoTipo != 1 && novoTipo != 2);

    double saldoInicial;
    do {
        saldoInicial = lerDouble("Saldo inicial: R$ ");
        if (saldoInicial < 0) {
            cout << "O saldo inicial nao pode ser negativo.\n";
        }
    } while (saldoInicial < 0);

    numeroConta[totalContas] = novoNumero;
    nomeCliente[totalContas] = novoNome;
    cpf[totalContas] = novoCpf;
    tipoConta[totalContas] = novoTipo;
    saldo[totalContas] = saldoInicial;
    contaAtiva[totalContas] = true;
    totalContas++;

    cout << "Conta cadastrada e ativada com sucesso.\n";
}

void consultarConta() {
    cout << "\n--- Consulta de conta ---\n";
    int indice = solicitarContaExistente();
    if (indice == -1) return;

    cout << fixed << setprecision(2);
    cout << "Numero: " << numeroConta[indice] << "\n";
    cout << "Titular: " << nomeCliente[indice] << "\n";
    cout << "CPF: " << formatarCpf(cpf[indice]) << "\n";
    cout << "Tipo: " << descricaoTipo(tipoConta[indice]) << "\n";
    cout << "Saldo: R$ " << saldo[indice] << "\n";
    cout << "Situacao: " << (contaAtiva[indice] ? "Ativa" : "Inativa") << "\n";
}

void verificarSaldo() {
    cout << "\n--- Verificacao de saldo ---\n";
    int indice = solicitarContaExistente();
    if (indice == -1) return;
    if (!contaAtiva[indice]) {
        cout << "Operacao indisponivel: a conta esta inativa.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "Saldo da conta " << numeroConta[indice] << ": R$ " << saldo[indice] << "\n";
}

void alterarTipoConta() {
    cout << "\n--- Alteracao de tipo de conta ---\n";
    int indice = solicitarContaExistente();
    if (indice == -1) return;
    if (!contaAtiva[indice]) {
        cout << "Operacao indisponivel: a conta esta inativa.\n";
        return;
    }

    int novoTipo;
    do {
        novoTipo = lerInteiro("Novo tipo (1 - Corrente | 2 - Poupanca): ");
        if (novoTipo != 1 && novoTipo != 2) {
            cout << "Tipo invalido. Escolha 1 ou 2.\n";
        }
    } while (novoTipo != 1 && novoTipo != 2);

    tipoConta[indice] = novoTipo;
    cout << "Tipo da conta alterado para " << descricaoTipo(novoTipo) << ".\n";
}

void alternarStatusConta() {
    cout << "\n--- Ativacao/Desativacao de conta ---\n";
    int indice = solicitarContaExistente();
    if (indice == -1) return;

    contaAtiva[indice] = !contaAtiva[indice];
    cout << "Conta " << (contaAtiva[indice] ? "ativada" : "desativada") << " com sucesso.\n";
}

void exibirMenu() {
    exibirCabecalho();
    cout << "1 - Cadastrar conta\n";
    cout << "2 - Consultar conta\n";
    cout << "3 - Verificar saldo\n";
    cout << "4 - Alterar tipo da conta\n";
    cout << "5 - Ativar/Desativar conta\n";
    cout << "6 - Sair\n";
}

int main() {
    int opcao;

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1: cadastrarConta(); break;
            case 2: consultarConta(); break;
            case 3: verificarSaldo(); break;
            case 4: alterarTipoConta(); break;
            case 5: alternarStatusConta(); break;
            case 6: cout << "Obrigado por utilizar o Banco INF101. Ate logo!\n"; break;
            default: cout << "Opcao invalida. Escolha uma opcao de 1 a 6.\n";
        }
    } while (opcao != 6);

    return 0;
}
