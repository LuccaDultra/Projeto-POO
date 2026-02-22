#include "interface.h"
#include <iostream>
#include <limits> 
#include <iomanip> 
#include <map>     
#include <string>  
#include <cctype>  
#include <cstdlib> 

using namespace std;

// Funcoes de validacao e leitura
string InterfaceCLI::lerString(const string& prompt) {
    string entrada;
    while (true) {
        cout << prompt;
        getline(cin, entrada);
        if (!entrada.empty()) {
            return entrada;
        }
        cout << COR_ERRO << "[ERRO] Voce precisa digitar algo! Pressione Enter para tentar novamente..." << COR_RESET;
        getline(cin, entrada);
        cout << "\033[1A\033[2K\033[1A\033[2K\r"; 
    }
}

string InterfaceCLI::lerSemNumeros(const string& prompt) {
    string entrada;
    while (true) {
        cout << prompt;
        getline(cin, entrada);
        
        bool temNumero = false;
        for (char c : entrada) {
            if (isdigit(c)) {
                temNumero = true;
                break;
            }
        }
        
        if (!entrada.empty() && !temNumero) {
            return entrada;
        }
        
        cout << COR_ERRO << "[ERRO] A entrada nao pode ser vazia ou conter numeros. Pressione Enter para tentar..." << COR_RESET;
        string dummy; getline(cin, dummy);
        cout << "\033[1A\033[2K\033[1A\033[2K\r"; 
    }
}

string InterfaceCLI::lerStringNumeros(const string& prompt, size_t tamanhoExato) {
    string entrada;
    while (true) {
        cout << prompt;
        getline(cin, entrada);
        
        bool formatoValido = (entrada.length() == tamanhoExato);
        for (char c : entrada) {
            if (!isdigit(c)) {
                formatoValido = false;
                break;
            }
        }
        
        if (formatoValido) {
            return entrada;
        }
        
        cout << COR_ERRO << "[ERRO] Digite exatamente " << tamanhoExato << " numeros. Pressione Enter para tentar..." << COR_RESET;
        string dummy; getline(cin, dummy);
        cout << "\033[1A\033[2K\033[1A\033[2K\r"; 
    }
}

string InterfaceCLI::lerOpcoes(const string& prompt, const vector<string>& opcoes) {
    string entrada;
    while(true) {
        cout << prompt;
        getline(cin, entrada);
        for(const string& op : opcoes) {
            if (entrada == op) return entrada;
        }
        cout << COR_ERRO << "[ERRO] Opcao invalida. Pressione Enter para tentar novamente..." << COR_RESET;
        string dummy; getline(cin, dummy);
        cout << "\033[1A\033[2K\033[1A\033[2K\r";
    }
}

string InterfaceCLI::escolherTurno() {
    while(true) {
        int op = lerInteiro("Turno (1-Manha, 2-Tarde, 3-Noite): ");
        if (op == 1) return "Manha";
        if (op == 2) return "Tarde";
        if (op == 3) return "Noite";
        
        cout << COR_ERRO << "[ERRO] Opcao invalida. Pressione Enter para tentar novamente..." << COR_RESET;
        string dummy; getline(cin, dummy);
        cout << "\033[1A\033[2K\033[1A\033[2K\r";
    }
}

string InterfaceCLI::escolherDepartamento() {
    cout << COR_TITULO << "\n--- Departamentos ---\n" << COR_RESET;
    cout << "1. Administrativo\n2. Recursos Humanos\n3. Tecnologia (TI)\n4. Vendas\n5. Operacional\n";
    while(true) {
        int op = lerInteiro("Opcao de Departamento: ");
        if (op == 1) return "Administrativo";
        if (op == 2) return "Recursos Humanos";
        if (op == 3) return "Tecnologia (TI)";
        if (op == 4) return "Vendas";
        if (op == 5) return "Operacional";
        
        cout << COR_ERRO << "[ERRO] Opcao invalida. Pressione Enter para tentar novamente..." << COR_RESET;
        string dummy; getline(cin, dummy);
        cout << "\033[1A\033[2K\033[1A\033[2K\r";
    }
}

Data InterfaceCLI::lerData(const string& prompt) {
    Data d;
    while(true) {
        cout << prompt << "\n";
        d.dia = lerInteiro("  Dia: ");
        d.mes = lerInteiro("  Mes: ");
        d.ano = lerInteiro("  Ano: ");
        
        if (d.valida()) return d;
        
        cout << COR_ERRO << "[ERRO] Data invalida! Pressione Enter para tentar novamente..." << COR_RESET;
        string dummy; getline(cin, dummy);
        cout << "\033[5A\033[0J"; 
    }
}

int InterfaceCLI::lerInteiro(const string& prompt) {
    string entrada;
    int valor;
    while (true) {
        cout << prompt;
        getline(cin, entrada);
        try {
            size_t pos;
            valor = stoi(entrada, &pos);
            if (pos == entrada.length()) { 
                return valor;
            }
        } catch (...) {} 
        
        cout << COR_ERRO << "[ERRO] Numero invalido! Pressione Enter para tentar novamente..." << COR_RESET;
        getline(cin, entrada);
        cout << "\033[1A\033[2K\033[1A\033[2K\r"; 
    }
}

double InterfaceCLI::lerDouble(const string& prompt) {
    string entrada;
    double valor;
    while (true) {
        cout << prompt;
        getline(cin, entrada);
        try {
            size_t pos;
            valor = stod(entrada, &pos);
            if (pos == entrada.length()) {
                return valor;
            }
        } catch (...) {}
        
        cout << COR_ERRO << "[ERRO] Valor numerico invalido! Pressione Enter para tentar novamente..." << COR_RESET;
        getline(cin, entrada);
        cout << "\033[1A\033[2K\033[1A\033[2K\r"; 
    }
}


// =========================================================
// CONTROLE DE TELAS
// =========================================================

//verifica se o sistema é windows ou linux, para definir com qual comando vai limpar a tela
void InterfaceCLI::limparTela() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

//funcao que pauda a tela
void InterfaceCLI::pausarTela() {
    cout << "\nPressione Enter para continuar...";
    string dummy;
    getline(cin, dummy);
}

int InterfaceCLI::exibirMenuPrincipal() {
    limparTela(); 
    cout << COR_TITULO << "=========================================\n";
    cout << "   SISTEMA DE GESTAO ORIENTADO A OBJETOS \n";
    cout << "=========================================\n" << COR_RESET;
    cout << "1. Dashboard RH \n";
    cout << "2. Dashbaord Financeiro \n";
    cout << "3. Listar funcionarios \n";
    cout << "4. Grade de horarios \n";       
    cout << "5. Orgonograma da empresa \n";
    cout << "6. Cadastrar novo funcionario \n";
    cout << "7. Gerenciar funcionarios \n"; 
    cout << "0. Sair do sistema\n";
    
    string entrada;
    int opcao;

    while (true) {
        cout << "Escolha uma opcao: ";
        getline(cin, entrada);
        try {
            size_t pos;
            opcao = stoi(entrada, &pos);
            if (pos == entrada.length() && opcao >= 0 && opcao <= 7) {
                return opcao;
            }
        } catch (...) {}
        
        cout << COR_ERRO << "[ERRO] Opcao invalida! Pressione Enter para tentar novamente..." << COR_RESET;
        getline(cin, entrada);
        cout << "\033[1A\033[2K\033[1A\033[2K\r"; 
    }
}

void InterfaceCLI::iniciar(vector<unique_ptr<Funcionario>>& funcionarios) {
    int opcao = -1;
    Data dataDoSistema = Data::hoje(); 

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
                listarGeral(funcionarios);
                break;
            case 4:
                exibirGradeHorarios(funcionarios);
                break;
            case 5:
                exibirOrganograma(funcionarios);
                break;
            case 6:
                cadastrarFuncionario(funcionarios);
                break;
            case 7: 
                gerenciarFuncionario(funcionarios);
                break;
            case 0:
                limparTela();
                cout << COR_TITULO << "Encerrando o sistema...\n" << COR_RESET;
                break;
        }
    }
}

void InterfaceCLI::gerenciarFuncionario(vector<unique_ptr<Funcionario>>& funcionarios) {
    limparTela();
    cout << COR_TITULO << "=========================================\n";
    cout << "         GERENCIAR FUNCIONARIO           \n";
    cout << "=========================================\n\n" << COR_RESET;
    
    cout << COR_TITULO << "--- Funcionarios Ativos ---\n" << COR_RESET;
    bool temAtivos = false;
    for (const auto& f : funcionarios) {
        if (f->isAtivo()) {
            //vai mostrar somente o primeiro nome
            cout << "- " << f->getPrimeiroNome() << " (Matricula: " << f->getMatricula() << ")\n";
            temAtivos = true;
        }
    }
    
    if (!temAtivos) {
        cout << "Nenhum funcionario ativo no momento.\n";
        pausarTela();
        return;
    }
    cout << "---------------------------\n\n";

    int matriculaBusca = lerInteiro("Digite a Matricula do funcionario (ou 0 para cancelar): ");
    if (matriculaBusca == 0) return;

    Funcionario* alvo = nullptr;
    for (auto& f : funcionarios) {
        if (f->getMatricula() == matriculaBusca) {
            alvo = f.get();
            break;
        }
    }

    if (!alvo) {
        cout << COR_ERRO << "\n[ERRO] Funcionario nao encontrado!\n" << COR_RESET;
        pausarTela();
        return;
    }

    int opcaoMenu = -1;
    while (opcaoMenu != 0) {
        limparTela();
        alvo->exibirDetalhes(); 
        
        cout << COR_TITULO << "\n--- ACOES ---\n" << COR_RESET;
        cout << "1. Editar departamento\n";
        cout << "2. Editar turno\n";
        cout << "3. Editar salario\n";
        cout << "4. Desligar funcionario\n";
        cout << "0. Menu principal\n";
        
        opcaoMenu = lerInteiro("Escolha uma opcao: ");
        
        if (opcaoMenu == 1) {
           //escolher departamento agora é opcao numerica, diferente de  antes
            string novoDepto = escolherDepartamento();
            alvo->setDepartamento(novoDepto);
            cout << COR_SIM << "Departamento atualizado!\n" << COR_RESET;
            pausarTela();
        } 
        else if (opcaoMenu == 2) {
            //escolher turno passou a ser opcao numerica
            string novoTurno = escolherTurno();
            alvo->setTurno(novoTurno);
            cout << COR_SIM << "Turno atualizado!\n" << COR_RESET;
            pausarTela();
        } 
        else if (opcaoMenu == 3) {
            double novoSal = lerDouble("Novo Salario Base: R$ ");
            try {
                alvo->setSalarioBase(novoSal);
                cout << COR_SIM << "Salario atualizado!\n" << COR_RESET;
            } catch(const exception& e) {
                cout << COR_ERRO << "[ERRO] " << e.what() << "\n" << COR_RESET;
            }
            pausarTela();
        } 
        else if (opcaoMenu == 4) {
            if (!alvo->isAtivo()) {
                cout << COR_AVISO << "\nEste funcionario ja foi desligado.\n" << COR_RESET;
            } else {
                cout << COR_TITULO << "\n--- DESLIGAMENTO ---\n" << COR_RESET;
                
                bool justaCausa = false;
                
                if (alvo->getVinculo() == TipoVinculo::CLT || alvo->getVinculo() == TipoVinculo::PJ) {
                    cout << "Motivo do Desligamento:\n";
                    cout << "1. Sem Justa Causa (Iniciativa da empresa)\n";
                    cout << "2. Por Justa Causa (Quebra de contrato)\n";
                    
                    int motivo;
                    while (true) {
                        motivo = lerInteiro("Escolha o motivo (1 ou 2): ");
                        if (motivo == 1 || motivo == 2) break;
                        
                        cout << COR_ERRO << "[ERRO] Escolha 1 ou 2! Pressione Enter para tentar novamente..." << COR_RESET;
                        string dummy; getline(cin, dummy);
                        cout << "\033[1A\033[2K\033[1A\033[2K\r";
                    }
                    justaCausa = (motivo == 2);
                } else {
                    cout << "Encerramento de contrato de estagio antecipado.\n";
                }

                double rescisao = alvo->calcularRescisao(justaCausa);
                
                cout << "Valor total da rescisao / multa a ser paga: " << COR_SAIDA << "R$ " << fixed << setprecision(2) << rescisao << COR_RESET << "\n";
                
                vector<string> simNao = {"S", "N"};
                string confirma = lerOpcoes("Confirmar desligamento? (S/N): ", simNao);
                
                if (confirma == "S") {
                    alvo->setAtivo(false);
                    cout << COR_SIM << "Funcionario desligado com sucesso!\n" << COR_RESET;
                } else {
                    cout << "Operacao cancelada.\n";
                }
            }
            pausarTela();
        }
        else if (opcaoMenu != 0) {
            cout << COR_ERRO << "\n[ERRO] Opcao invalida.\n" << COR_RESET;
            pausarTela();
        }
    }
}

//intarface dos menus
void InterfaceCLI::menuRH(const vector<unique_ptr<Funcionario>>& funcionarios, Data dataAtual) {
    int opcao = -1;
    while(opcao != 0) {
        limparTela();
        cout << COR_TITULO << "======================================================\n";
        cout << "                   DASHBOARD DE RH                    \n";
        cout << "======================================================\n" << COR_RESET;
        
        ModuloRH::listarFeriasVencidas(funcionarios, dataAtual);
        ModuloRH::listarFeriasParaVencer(funcionarios, dataAtual); // ADICIONADO: Nova funcionalidade pedida
        ModuloRH::listarContratosVencendo(funcionarios, dataAtual);
        
        opcao = lerInteiro("\nDigite 0 para sair do RH: ");
    }
}

void InterfaceCLI::menuFinanceiro(const vector<unique_ptr<Funcionario>>& funcionarios) {
    int opcao = -1;
    while(opcao != 0) {
        limparTela();
        RelatorioFinanceiro::folhaPagamento(funcionarios);
        opcao = lerInteiro("\nDigite 0 para voltar: ");
    }
}

//padrao de lista
void InterfaceCLI::listarGeral(const vector<unique_ptr<Funcionario>>& funcionarios) {
    int opcao = -1;
    while(opcao != 0) {
        limparTela();
        cout << COR_TITULO << "==================================================================================\n";
        cout << "                           LISTA GERAL DE FUNCIONARIOS                            \n";
        cout << "==================================================================================\n" << COR_RESET;
        
        cout << left << setw(15) << "NOME" 
             << setw(15) << "MATRICULA" 
             << setw(18) << "DEPARTAMENTO" 
             << setw(15) << "CARGO" 
             << setw(15) << "VINCULO" << "\n";
        cout << "----------------------------------------------------------------------------------\n";

        for (const auto& f : funcionarios) {
            cout << left << setw(15) << f->getPrimeiroNome() 
                 << setw(15) << f->getMatricula() 
                 << setw(18) << f->getDepartamento()
                 << setw(15) << f->getCargo() 
                 << setw(15) << f->getVinculoString() << (f->isAtivo() ? "" : COR_AVISO " (DESLIGADO)" COR_RESET) << "\n";
        }
        cout << "==================================================================================\n";
        opcao = lerInteiro("\nDigite 0 para voltar: ");
    }
}

void InterfaceCLI::exibirGradeHorarios(const vector<unique_ptr<Funcionario>>& funcionarios) {
    int opcao = -1;
    //aguarda 0 para sair do loop
    while(opcao != 0) {
        limparTela();
        cout << COR_TITULO << "==================================================================================\n";
        cout << "                              GRADE DE HORARIOS VISUAL                            \n";
        cout << "==================================================================================\n" << COR_RESET;
        cout << left << setw(15) << "NOME" 
             << setw(15) << "MATRICULA" 
             << setw(15) << "CARGO" 
             << setw(15) << "VINCULO" 
             << setw(15) << "TURNO" << "\n";
        cout << "----------------------------------------------------------------------------------\n";

        for (const auto& f : funcionarios) {
            if (f->isAtivo()) { 
                cout << left << setw(15) << f->getPrimeiroNome() 
                     << setw(15) << f->getMatricula() 
                     << setw(15) << f->getCargo() 
                     << setw(15) << f->getVinculoString() // ADICIONADO: Separacao de cargo
                     << setw(15) << f->getTurno() << "\n";
            }
        }
        cout << "==================================================================================\n";
        opcao = lerInteiro("\nDigite 0 para voltar: ");
    }
}

void InterfaceCLI::exibirOrganograma(const vector<unique_ptr<Funcionario>>& funcionarios) {
    int opcao = -1;
    //aguarda 0 para sair
    while(opcao != 0) {
        limparTela();
        cout << COR_TITULO << "=========================================\n";
        cout << "         ORGANOGRAMA DE EQUIPE           \n";
        cout << "=========================================\n" << COR_RESET;

        map<string, vector<string>> agrupamento;

        for (const auto& f : funcionarios) {
            if (f->isAtivo()) { 
                //esta adicionando somente o primerio nome, para nao quebrar formatacao
                agrupamento[f->getDepartamento()].push_back(f->getPrimeiroNome() + " (" + f->getCargo() + ")");
            }
        }

        for (const auto& par : agrupamento) {
            cout << "\n[" << COR_TITULO << " Departamento: " << par.first << " " << COR_RESET << "]\n";
            for (const auto& nomeFuncionario : par.second) {
                cout << "  |- " << nomeFuncionario << "\n";
            }
        }
        cout << "\n=========================================\n";
        opcao = lerInteiro("\nDigite 0 para voltar: ");
    }
}

//cadastro dos funcionarios
void InterfaceCLI::cadastrarFuncionario(vector<unique_ptr<Funcionario>>& funcionarios) {
    limparTela();
    cout << COR_TITULO << "+---------------------------------------+\n";
    cout << "|        CADASTRO DE FUNCIONARIO        |\n";
    cout << "+---------------------------------------+\n\n" << COR_RESET;

    try {
        int tipo;
        while (true) {
            tipo = lerInteiro("Tipo de Vinculo (1-CLT, 2-Estagiario, 3-Vendedor PJ, 0-Cancelar): ");
            if (tipo >= 0 && tipo <= 3) break;
            
            cout << COR_ERRO << "[ERRO] Tipo de vinculo inexistente. Pressione Enter para tentar novamente..." << COR_RESET;
            string dummy; getline(cin, dummy);
            cout << "\033[1A\033[2K\033[1A\033[2K\r";
        }
        
        //se digitar 0 vai sair do loop
        if (tipo == 0) return;

        string nome = lerSemNumeros("\nNome Completo: ");
        string cpf = lerStringNumeros("CPF (11 digitos apenas numeros): ", 11);
        
        string turno = escolherTurno();
        string depto = escolherDepartamento();

        Endereco end;
        cout << COR_TITULO << "\n[ --- Endereco --- ]\n" << COR_RESET;
        end.rua = lerString("Rua: ");
        end.numero = lerInteiro("Numero: ");
        end.bairro = lerString("Bairro: ");
        end.cidade = lerSemNumeros("Cidade: ");
        end.cep = lerStringNumeros("CEP (8 digitos apenas numeros): ", 8);

        Data adm = lerData(COR_TITULO "\n[ --- Data de Admissao --- ]" COR_RESET);

        if (tipo == 1) {
            double sal; bool noturno;
            cout << COR_TITULO << "\n[ --- Dados CLT --- ]\n" << COR_RESET;
            sal = lerDouble("Salario Base: R$ ");
            
            int noturnoInt;
            while (true) {
                noturnoInt = lerInteiro("Trabalha de noite? (1-Sim, 0-Nao): ");
                if (noturnoInt == 0 || noturnoInt == 1) break;
                cout << COR_ERRO << "[ERRO] Digite apenas 1 ou 0. Pressione Enter para tentar novamente..." << COR_RESET;
                string dummy; getline(cin, dummy);
                cout << "\033[1A\033[2K\033[1A\033[2K\r"; 
            }
            noturno = noturnoInt;
            
            funcionarios.push_back(make_unique<FuncionarioCLT>(nome, cpf, end, adm, sal, noturno, turno, depto));
            
        } else if (tipo == 2) {
            int horas; double valor;
            Data fim = lerData(COR_TITULO "\n[ --- Fim do Contrato (Estagio) --- ]" COR_RESET);

            horas = lerInteiro("Horas Mensais: ");
            valor = lerDouble("Valor da Hora: R$ ");
            
            funcionarios.push_back(make_unique<Estagiario>(nome, cpf, end, adm, fim, horas, valor, turno, depto));
            
        } else if (tipo == 3) {
            double fixo, vendas, perc;
            Data fim = lerData(COR_TITULO "\n[ --- Fim do Contrato (PJ) --- ]" COR_RESET);

            fixo = lerDouble("Salario Fixo: R$ ");
            vendas = lerDouble("Total de Vendas Previsto: R$ ");
            perc = lerDouble("Percentual de Comissao (ex: 0.05 para 5%): ");
            
            funcionarios.push_back(make_unique<Vendedor>(nome, cpf, end, adm, fim, fixo, vendas, perc, turno, depto));
        }

        cout << COR_SIM << "\n>>> FUNCIONARIO CADASTRADO COM SUCESSO! <<<\n" << COR_RESET;
        
    } catch (const exception& e) {
        cout << COR_ERRO << "\n[ERRO NO CADASTRO]: " << e.what() << "\nOperacao cancelada.\n" << COR_RESET;
    }
    pausarTela();
}
