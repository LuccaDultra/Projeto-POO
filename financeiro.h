#ifndef MODULO_FINANCEIRO_H
#define MODULO_FINANCEIRO_H

#include "funcionario.h"
#include <vector>
#include <iostream>
#include <memory> 

// FUNCIONARIO CLT

class FuncionarioCLT : public Funcionario {
private:

    // Indica se o funcionário trabalha em turno noturno
    bool turnoNoturno;

    // Calcula desconto de INSS com faixas simplificadas
    double calcularINSS(double salario) const {
        if (salario <= 2000) return salario * 0.08;
        if (salario <= 4000) return salario * 0.10;
        return salario * 0.12;
    }

    // Calcula desconto de IRRF com faixas simplificadas
    double calcularIRRF(double salario) const {
        if (salario <= 2500) return 0;
        if (salario <= 5000) return salario * 0.075;
        return salario * 0.15;
    }

public:

    // Construtor do funcionário CLT
    // Recebe dados pessoais e salário base
    // Define o vínculo como CLT
    FuncionarioCLT(std::string nome, std::string cpf, std::string rg,
                   Endereco end, Data admissao,
                   double salarioBase,
                   bool noturno, std::string turno, std::string departamento)
        : Funcionario(nome, cpf, rg, end, admissao, salarioBase, TipoVinculo::CLT, turno, departamento),
          turnoNoturno(noturno) {
              this->cargo = "Funcionario CLT"; // Ajuste para os filtros do RH
          }

    // Calcula o salário líquido final
    // Aplica adicional noturno e descontos obrigatórios
    double calcularSalario() const override {

        // Salário bruto começa com o base
        double bruto = salarioBase;

        // Se for turno noturno, adiciona 20%
        if (turnoNoturno)
            bruto += salarioBase * 0.20;

        // Calcula descontos
        double inss = calcularINSS(bruto);
        double irrf = calcularIRRF(bruto);
        double valeTransporte = bruto * 0.06;

        // Retorna salário líquido final
        return bruto - inss - irrf - valeTransporte;
    }

    // Exibe informações resumidas na folha
    void render() const override {
        std::cout << "CLT: " << nome
                  << " | Liquido: "
                  << calcularSalario()
                  << std::endl;
    }
};

// ESTAGIARIO / HORISTA

class Estagiario : public Funcionario {
private:

    // Quantidade de horas trabalhadas no mês
    int horas;

    // Valor pago por hora
    double valorHora;
    
    // Data de termino do estagio (Regra de negocio adicionada)
    Data fimContrato; 

public:

    // Construtor do estagiário
    // Salário base é 0 pois é calculado por hora
    Estagiario(std::string nome, std::string cpf, std::string rg,
               Endereco end, Data admissao, Data fim, // Recebe a data de fim
               int horasTrabalhadas,
               double valor, std::string turno, std::string departamento)
        : Funcionario(nome, cpf, rg, end, admissao, 0, TipoVinculo::ESTAGIARIO, turno, departamento),
          fimContrato(fim),
          horas(horasTrabalhadas),
          valorHora(valor) {
              this->cargo = "Estagiario";
          }

    // Getter para o RH verificar o vencimento
    Data getFimContrato() const { return fimContrato; }

    // Calcula salário multiplicando horas x valor hora
    double calcularSalario() const override {
        return horas * valorHora;
    }

    // Exibe valor da bolsa
    void render() const override {
        std::cout << "Estagiario: " << nome
                  << " | Bolsa: "
                  << calcularSalario()
                  << std::endl;
    }
};

// VENDEDOR (COMISSAO / CONTRATO PJ)

class Vendedor : public Funcionario {
private:

    // Total vendido no mês
    double totalVendas;

    // Percentual de comissão sobre vendas
    double percentualComissao;
    
    // Data de termino do contrato (Regra de negocio adicionada)
    Data fimContrato; 

public:

    // Construtor do vendedor
    // Pode ter salário fixo + comissão
    Vendedor(std::string nome, std::string cpf, std::string rg,
             Endereco end, Data admissao, Data fim, // Recebe a data de fim
             double salarioBase,
             double vendas,
             double percentual, std::string turno, std::string departamento)
        : Funcionario(nome, cpf, rg, end, admissao, salarioBase, TipoVinculo::PJ, turno, departamento),
          fimContrato(fim),
          totalVendas(vendas),
          percentualComissao(percentual) {
              this->cargo = "Vendedor PJ";
          }
          
    // Getter para o RH verificar o vencimento
    Data getFimContrato() const { return fimContrato; }

    // Calcula salário somando salário fixo + comissão
    double calcularSalario() const override {
        return salarioBase + (totalVendas * percentualComissao);
    }

    // Exibe salário total do vendedor
    void render() const override {
        std::cout << "Vendedor: " << nome
                  << " | Total: "
                  << calcularSalario()
                  << std::endl;
    }
};

// RELATORIO FINANCEIRO

class RelatorioFinanceiro {
public:

    // Calcula custo total da empresa
    // Soma o salário líquido de todos os funcionários
    static double custoTotalEmpresa(const std::vector<std::unique_ptr<Funcionario>>& lista) {
        double total = 0;

        // Cada objeto chama sua própria implementação de calcularSalario()
        for (const auto& f : lista)
            total += f->calcularSalario();

        return total;
    }

    // Calcula custo total por tipo de vínculo (CLT, ESTAGIARIO, PJ)
    static double custoPorVinculo(const std::vector<std::unique_ptr<Funcionario>>& lista,
                                  TipoVinculo tipo) {

        double total = 0;

        for (const auto& f : lista) {
            if (f->getVinculo() == tipo)
                total += f->calcularSalario();
        }

        return total;
    }

    // Gera folha de pagamento completa
    static void folhaPagamento(const std::vector<std::unique_ptr<Funcionario>>& lista) {

        std::cout << "\n========== FOLHA DE PAGAMENTO ==========\n";

        // Renderiza cada funcionário
        for (const auto& f : lista)
            f->render();

        // Exibe custo total final
        std::cout << "\nCusto Total Empresa: "
                  << custoTotalEmpresa(lista)
                  << "\n";
    }
};

#endif
