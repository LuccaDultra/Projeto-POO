#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include <memory>
#include "funcionario.h"
#include "rh.h"
#include "financeiro.h"

class InterfaceCLI {
public:
    // Parte pública da interface
    static void iniciar(std::vector<std::unique_ptr<Funcionario>>& funcionarios);

private:
    // Métodos privados para controlar cada tela
    static int exibirMenuPrincipal();
    static void menuRH(const std::vector<std::unique_ptr<Funcionario>>& funcionarios, Data dataAtual);
    static void menuFinanceiro(const std::vector<std::unique_ptr<Funcionario>>& funcionarios);
    
    // Função auxiliar para pausas e limpeza de tela
    static void pausarTela();
    static void limparTela();
};

#endif