#include <stdio.h>
#include <string.h>

typedef struct {             // strutct pra gurdar os dados
    char nome[35];          
    int numero;
    float corrente;
    float salario;
    float poupanca;
    char historico[50];
    int fez_emprestimo;
} Cliente;

void cadastrarCliente(Cliente banco[], int *t) {           // cadast. clientes 
    int i = *t;
    printf("nome do cliente: ");
    scanf(" %[^\n]", banco[i].nome);

    printf("numero da conta: ");
    scanf("%d", &banco[i].numero);

    printf("saldo conta corrente: ");
    scanf("%f", &banco[i].corrente);

    printf("saldo conta salario: ");
    scanf("%f", &banco[i].salario);

    printf("saldo conta poupanca: ");
    scanf("%f", &banco[i].poupanca);
  
    strcpy(banco[i].historico, "Conta criada");     //historico incial + cliente não fez emprestimo
    banco[i].fez_emprestimo = 0;
  
    (*t)++;     //Aumenta a quantidade de clientes cadastrados
    printf("Cliente cadastrado com sucesso!\n");
}

void realizarEmprestimo(Cliente banco[], int t) {     // função pra verificar se cliente fez emprestimo
    int num;
    printf("Digite o numero da conta para o emprestimo: ");
    scanf("%d", &num);

    for (int i = 0; i < t; i++) {                      // procurar a conta pelo numero
        if (banco[i].numero == num) {
            if (banco[i].fez_emprestimo == 1) {             // Verifica se o cliente ja fez um emprestimo
                printf("Erro: Cliente ja possui 1 emprestimo.\n");          
            }  
            else if (banco[i].poupanca > 0) {                // Verifica se o cliente tem dinheiro na poupanca
                float lim = 2.5 * (banco[i].poupanca + banco[i].corrente);
                float v;
                printf("Limite liberado: R$ %.2f\n", lim);
                printf("Valor do emprestimo: R$ ");
                scanf("%f", &v);
              
                if (v <= lim) {                              // Verifica se o valor pedido esta dentro do limite
                    banco[i].corrente += v;
                    banco[i].fez_emprestimo = 1;
                    strcpy(banco[i].historico, "Emprestimo realizado");
                    printf("Sucesso! Valor creditado na conta corrente.\n");
                }   else {
                    printf("Erro: Valor acima do limite!\n");
                }
            } else {
                printf("Erro: Sem saldo na poupanca.\n");
            }

            return;
        }
    }
    printf("Conta nao encontrada.\n");                 // Mostra uma mensagem caso a conta nao seja encontrada
}

int main() {
    Cliente banco[100];
    int t = 0;
    char op;
    
    do {
        printf("Menu: {c} cadastrar um cliente | {e} emprestimo | {s} sair");
        printf("opcao: ");
        scanf("%c", &op);

        // funcao cadastro
        if (op == 'c') {
            cadastrarCliente(banco, &t);
        }
        // funcao emprestimo
        else if (op == 'e') {
            realizarEmprestimo(banco, t);
        }

    } while (op != 's');
    float saldo_banco = 0;

    for (int i = 0; i < t; i++) {                                                // somar saldo do cliente
        saldo_banco += banco[i].corrente + banco[i].salario + banco[i].poupanca;
    }
    printf("1. Saldo total do banco: R$ %.2f\n", saldo_banco);
    printf("2. Clientes que podem fazer emprestimo:\n");             //clientes que podem fazer emprestimo

    for (int i = 0; i < t; i++) {
        if (banco[i].poupanca > 0 && banco[i].fez_emprestimo == 0) {
            printf("   - %s\n", banco[i].nome);
        }
    }
    printf("\n3. Clientes com saldo negativo na Conta Corrente:\n");          // clientes com saldo negativo

    for (int i = 0; i < t; i++) {
        if (banco[i].corrente < 0) {
            printf("   - %s\n", banco[i].nome);
        }
    }

    printf("\n4. Clientes com R$1000 a R$1500 no total:\n");       //clientes que tem entre 1000/1500

    for (int i = 0; i < t; i++) {
        float soma = banco[i].corrente + banco[i].salario + banco[i].poupanca;

        if (soma >= 1000 && soma <= 1500) {
            printf("   - %s (R$ %.2f)\n", banco[i].nome, soma);
        }
    }

    return 0;
}
