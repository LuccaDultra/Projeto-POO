#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include <memory>
#include <string> 
#include "funcionario.h"
#include "rh.h"
#include "financeiro.h"

class InterfaceCLI {
public:
    static void iniciar(std::vector<std::unique_ptr<Funcionario>>& funcionarios);

private:
    static int exibirMenuPrincipal();
    static void menuRH(const std::vector<std::unique_ptr<Funcionario>>& funcionarios, Data dataAtual);
    static void menuFinanceiro(const std::vector<std::unique_ptr<Funcionario>>& funcionarios);
    static void exibirGradeHorarios(const std::vector<std::unique_ptr<Funcionario>>& funcionarios);
    static void exibirOrganograma(const std::vector<std::unique_ptr<Funcionario>>& funcionarios);
    static void listarGeral(const std::vector<std::unique_ptr<Funcionario>>& funcionarios); 
    
    static void cadastrarFuncionario(std::vector<std::unique_ptr<Funcionario>>& funcionarios);
    static void gerenciarFuncionario(std::vector<std::unique_ptr<Funcionario>>& funcionarios);

    static void pausarTela();
    static void limparTela();

    // Funções auxiliares para leitura  de dados e tratamento de erros
    static int lerInteiro(const std::string& prompt);
    static double lerDouble(const std::string& prompt);
    static std::string lerString(const std::string& prompt);
    static std::string lerSemNumeros(const std::string& prompt);
    static std::string lerStringNumeros(const std::string& prompt, size_t tamanhoExato);
    static std::string lerOpcoes(const std::string& prompt, const std::vector<std::string>& opcoes);
    static Data lerData(const std::string& prompt);
    
    //metodos para menus numericos fixos
    static std::string escolherTurno();
    static std::string escolherDepartamento();
};

#endif
