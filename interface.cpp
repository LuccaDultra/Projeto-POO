#include "interface.h"
#include <iostream>
#include <limits> // p limpar o buffer do cin

using namespace std;

void InterfaceCLI::limparTela() {
    // Codigos ANSI p limpar a tela
    std::cout << "\033[2J\033[1;1H";
}

void InterfaceCLI::pausarTela() {
    cout << "\nPressione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    limparTela();
}

int InterfaceCLI::exibirMenuPrincipal() {
    
    int opcao;
    cout << "\n=========================================\n";
    cout << "   SISTEMA DE GESTAO ORIENTADO A OBJETOS   \n";
    cout << "=========================================\n";
    cout << "1. Menu de Recursos Humanos (RH)\n";
    cout << "2. Menu Financeiro\n";
    cout << "3. Listar Todos os Funcionarios \n";
    // 
    cout << "0. Sair do Sistema\n";
    cout << "Escolha uma opcao: ";
    if (!(cin >> opcao)) { // Caso usuário digite algo que NÃO é um número
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        return -1; // Retorna um valor que cairá obrigatoriamente no 'default'
    }
    return opcao;
}

void InterfaceCLI::iniciar(vector<unique_ptr<Funcionario>>& funcionarios) {
    int opcao = -1;
    Data dataDoSistema = Data::hoje(); // Pega a data de hoje pelo OS

    limparTela();
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
                limparTela();
                cout << "\n--- LISTA GERAL DE FUNCIONARIOS ---\n";
                // Cumprindo o requisito do método render() 
                for (const auto& f : funcionarios) {
                    f->render();
                }
                pausarTela();
                break;
            case 0:
                limparTela();
                cout << "\nEncerrando o sistema...\n";
                break;
            default:
                cout << "\nOpcao invalida! Aperte Enter e tente novamente.\n";
                // Tratamento básico p evitar loop se usuário n digitar uma da opções 
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                
        }
    }
}

void InterfaceCLI::menuRH(const vector<unique_ptr<Funcionario>>& funcionarios, Data dataAtual) {
    limparTela();
    cout << "\n>>> ACESSANDO MODULO DE RH <<<\n";
    // Chama os métodos que já existem do rh.h
    ModuloRH::listarFeriasVencidas(funcionarios, dataAtual);
    ModuloRH::listarContratosVencendo(funcionarios, dataAtual);
    pausarTela();
}

void InterfaceCLI::menuFinanceiro(const vector<unique_ptr<Funcionario>>& funcionarios) {
    limparTela();
    cout << "\n>>> ACESSANDO MODULO FINANCEIRO <<<\n";
    // Chama o relatório do financeiro
    RelatorioFinanceiro::folhaPagamento(funcionarios);
    pausarTela();
}