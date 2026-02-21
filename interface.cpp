#include "interface.h"
#include <iostream>
#include <limits> // p limpar o buffer do cin

using namespace std;

void InterfaceCLI::pausarTela() {
    cout << "\nPressione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int InterfaceCLI::exibirMenuPrincipal() {
    int opcao;
    cout << "\n=========================================\n";
    cout << "   SISTEMA DE GESTAO ORIENTADO A OBJETOS   \n";
    cout << "=========================================\n";
    cout << "1. Modulo de Recursos Humanos (RH)\n";
    cout << "2. Modulo Financeiro\n";
    cout << "3. Listar Todos os Funcionarios \n";
    cout << "0. Sair do Sistema\n";
    cout << "Escolha uma opcao: ";
    cin >> opcao;
    return opcao;
}

void InterfaceCLI::iniciar(vector<unique_ptr<Funcionario>>& funcionarios) {
    int opcao = -1;
    Data dataDoSistema = Data::hoje(); // Pega a data de hoje pelo OS

    while (opcao != 0) {
        opcao = exibirMenuPrincipal();

        switch (opcao) {
            case 1:
                menuRH(funcionarios, dataDoSistema);
                break;
            case 2:
                menuFinanceiro(funcionarios);
                break;
            case 3:
                cout << "\n--- LISTA GERAL DE FUNCIONARIOS ---\n";
                // Cumprindo o requisito do método render() 
                for (const auto& f : funcionarios) {
                    f->render();
                }
                pausarTela();
                break;
            case 0:
                cout << "\nEncerrando o sistema...\n";
                break;
            default:
                cout << "\nOpcao invalida! Tente novamente.\n";
                // Tratamento básico p evitar loop se usuário n digitar uma da opções 
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pausarTela();
        }
    }
}

void InterfaceCLI::menuRH(const vector<unique_ptr<Funcionario>>& funcionarios, Data dataAtual) {
    cout << "\n>>> ACESSANDO MODULO DE RH <<<\n";
    // Chama os métodos que já existem do rh.h
    ModuloRH::listarFeriasVencidas(funcionarios, dataAtual);
    ModuloRH::listarContratosVencendo(funcionarios, dataAtual);
    pausarTela();
}

void InterfaceCLI::menuFinanceiro(const vector<unique_ptr<Funcionario>>& funcionarios) {
    cout << "\n>>> ACESSANDO MODULO FINANCEIRO <<<\n";
    // Chama o relatório do financeiro
    RelatorioFinanceiro::folhaPagamento(funcionarios);
    pausarTela();
}