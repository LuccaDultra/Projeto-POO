#include "interface.h"
#include <iostream>
#include <limits> // p limpar o buffer do cin
#include <iomanip> // Para formatação de tabelas
#include <map>     // Para agrupar 

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
    cout << "4. Grade de Horarios Visual\n";       
    cout << "5. Organograma de Equipe\n";
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
                    cout << "\n=========================================\n";
                    cout << "         LISTA GERAL DE FUNCIONARIOS       \n";
                    cout << "=========================================\n\n";
                // Cumprindo o requisito do método render() 
                for (const auto& f : funcionarios) {
                    f->render();
                }
                pausarTela();
                break;
            case 4:
                exibirGradeHorarios(funcionarios);
                break;
            case 5:
                exibirOrganograma(funcionarios);
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
    cout << "\n======================================================\n";
    cout << "                MODULO DE RH                           \n";
    cout << "======================================================\n";
    // Chama os métodos que já existem do rh.h
    ModuloRH::listarFeriasVencidas(funcionarios, dataAtual);
    ModuloRH::listarContratosVencendo(funcionarios, dataAtual);
    pausarTela();
}

void InterfaceCLI::menuFinanceiro(const vector<unique_ptr<Funcionario>>& funcionarios) {
    limparTela();
    cout << "\n======================================================\n";
    cout << "                MODULO FINANCEIRO                      \n";
    cout << "======================================================\n";
    // Chama o relatório do financeiro
    RelatorioFinanceiro::folhaPagamento(funcionarios);
    pausarTela();
}

void InterfaceCLI::exibirGradeHorarios(const vector<unique_ptr<Funcionario>>& funcionarios) {
    limparTela();
    cout << "\n======================================================\n";
    cout << "                GRADE DE HORARIOS VISUAL                \n";
    cout << "======================================================\n";
    
    // Cabeçalho da tabela alinhado à esquerda (left) com larguras fixas (setw)
    cout << left << setw(15) << "NOME" 
         << setw(15) << "MATRICULA" 
         << setw(15) << "CARGO" 
         << setw(15) << "TURNO" << "\n";
    cout << "------------------------------------------------------\n";

    // Imprimindo os dados
    for (const auto& f : funcionarios) {
        cout << left << setw(15) << f->getNome() 
             << setw(15) << f->getMatricula() 
             << setw(15) << f->getCargo() 
             << setw(15) << f->getTurno() << "\n";
    }
    cout << "======================================================\n";
    pausarTela();
}

void InterfaceCLI::exibirOrganograma(const vector<unique_ptr<Funcionario>>& funcionarios) {
    limparTela();
    cout << "\n=========================================\n";
    cout << "         ORGANOGRAMA DE EQUIPE           \n";
    cout << "=========================================\n";

    // Usamos um std::map para agrupar automaticamente. 
    // A chave é o nome do departamento, o valor é um vetor com os nomes dos funcionários.
    map<string, vector<string>> agrupamento;

    for (const auto& f : funcionarios) {
        agrupamento[f->getDepartamento()].push_back(f->getNome() + " (" + f->getCargo() + ")");
    }

    // Exibindo os grupos
    for (const auto& par : agrupamento) {
        cout << "\n[ Departamento: " << par.first << " ]\n";
        for (const auto& nomeFuncionario : par.second) {
            cout << "  |- " << nomeFuncionario << "\n";
        }
    }
    cout << "\n=========================================\n";
    pausarTela();
}