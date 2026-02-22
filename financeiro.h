#ifndef MODULO_FINANCEIRO_H
#define MODULO_FINANCEIRO_H

#include "funcionario.h"
#include <vector>
#include <iostream>
#include <memory> 
#include <iomanip> //p usar o setw()

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
    FuncionarioCLT(std::string nome, std::string cpf, 
                   Endereco end, Data admissao,
                   double salarioBase,
                   bool noturno, std::string turno, std::string departamento)
        : Funcionario(nome, cpf, end, admissao, salarioBase, TipoVinculo::CLT, turno, departamento),
          turnoNoturno(noturno) {
              this->cargo = "Funcionario"; // Ajuste para os filtros do RH
          }

    // Calcula o salário líquido final
    double calcularSalario() const override {
        double bruto = salarioBase;
        if (turnoNoturno)
            bruto += salarioBase * 0.20;

        double inss = calcularINSS(bruto);
        double irrf = calcularIRRF(bruto);
        double valeTransporte = bruto * 0.06;

        return bruto - inss - irrf - valeTransporte;
    }

    // Exibe informações resumidas na folha
    void render() const override {
        //Formatacao do dashboard
        std::cout << std::left << std::setw(20) << departamento << " - " 
                  << std::setw(15) << getPrimeiroNome() << " - " 
                  << std::setw(10) << matricula << " - " 
                  << COR_SAIDA << "R$ " << calcularSalario() << COR_RESET << std::endl;
    }
    
    // Exibe todos os dados detalhados 
    void exibirDetalhes() const override {
        std::cout << COR_TITULO << "--- DETALHES FUNCIONARIO CLT ---\n" << COR_RESET
                  << "Nome Completo: " << nome << (ativo ? COR_SIM " [ATIVO]" COR_RESET : COR_NAO " [DESLIGADO]" COR_RESET) << "\n"
                  << "Matricula: " << matricula << " | CPF: " << cpf << "\n"
                  << "Admissao: " << dataAdmissao.toString() << "\n"
                  << "Departamento: " << departamento << " | Turno: " << turno << "\n"
                  << "Salario Base: R$ " << salarioBase << " | Noturno: " << (turnoNoturno ? COR_SIM "Sim" COR_RESET : COR_NAO "Nao" COR_RESET) << "\n";
    }

    // Regra de negocio para rescisao CLT coerente
    double calcularRescisao(bool justaCausa) const override {
        if (justaCausa) {
            return 0; // Perde direito a multa do FGTS e aviso previo
        }
        return salarioBase + (salarioBase * 0.40); // Aviso previo + 40% FGTS simulado
    }
};

// ESTAGIARIO / HORISTA

class Estagiario : public Funcionario {
private:

    int horas;
    double valorHora;
    Data fimContrato; 

public:

    // Construtor do estagiário 
    Estagiario(std::string nome, std::string cpf, 
               Endereco end, Data admissao, Data fim, 
               int horasTrabalhadas,
               double valor, std::string turno, std::string departamento)
        : Funcionario(nome, cpf, end, admissao, 0, TipoVinculo::ESTAGIARIO, turno, departamento),
          fimContrato(fim),
          horas(horasTrabalhadas),
          valorHora(valor) {
              this->cargo = "Estagiario";
          }

    Data getFimContrato() const { return fimContrato; }

    double calcularSalario() const override {
        return horas * valorHora;
    }

    // Exibe valor da bolsa
    void render() const override {
        //Formatacao do dashboard
        std::cout << std::left << std::setw(20) << departamento << " - " 
                  << std::setw(15) << getPrimeiroNome() << " - " 
                  << std::setw(10) << matricula << " - " 
                  << COR_SAIDA << "R$ " << calcularSalario() << COR_RESET << std::endl;
    }
    
    // Exibe todos os dados do Estagiario
    void exibirDetalhes() const override {
        std::cout << COR_TITULO << "--- DETALHES ESTAGIARIO ---\n" << COR_RESET
                  << "Nome Completo: " << nome << (ativo ? COR_SIM " [ATIVO]" COR_RESET : COR_NAO " [DESLIGADO]" COR_RESET) << "\n"
                  << "Matricula: " << matricula << " | CPF: " << cpf << "\n"
                  << "Admissao: " << dataAdmissao.toString() << " | Fim Previsto: " << fimContrato.toString() << "\n"
                  << "Departamento: " << departamento << " | Turno: " << turno << "\n"
                  << "Horas Mensais: " << horas << "h | Valor Hora: R$ " << valorHora << "\n";
    }

    // Regra de negocio para rescisao de estagio
    double calcularRescisao(bool justaCausa) const override {
        return calcularSalario(); 
    }
};

// contratado (COMISSAO / CONTRATO PJ)

class Vendedor : public Funcionario {
private:

    double totalVendas;
    double percentualComissao;
    Data fimContrato; 

public:

    // Construtor do contratado
    Vendedor(std::string nome, std::string cpf, 
             Endereco end, Data admissao, Data fim, 
             double salarioBase,
             double vendas,
             double percentual, std::string turno, std::string departamento)
        : Funcionario(nome, cpf, end, admissao, salarioBase, TipoVinculo::PJ, turno, departamento),
          fimContrato(fim),
          totalVendas(vendas),
          percentualComissao(percentual) {
              this->cargo = "Contratado";
          }
          
    Data getFimContrato() const { return fimContrato; }

    double calcularSalario() const override {
        return salarioBase + (totalVendas * percentualComissao);
    }

    // Exibe salário total do vendedor
    void render() const override {
        //Formatacao do dashboard
        std::cout << std::left << std::setw(20) << departamento << " - " 
                  << std::setw(15) << getPrimeiroNome() << " - " 
                  << std::setw(10) << matricula << " - " 
                  << COR_SAIDA << "R$ " << calcularSalario() << COR_RESET << std::endl;
    }
    
    // Exibe todos os dados do PJ 
    void exibirDetalhes() const override {
        std::cout << COR_TITULO << "--- DETALHES VENDEDOR PJ ---\n" << COR_RESET
                  << "Nome Completo: " << nome << (ativo ? COR_SIM " [ATIVO]" COR_RESET : COR_NAO " [DESLIGADO]" COR_RESET) << "\n"
                  << "Matricula: " << matricula << " | CPF: " << cpf << "\n"
                  << "Admissao: " << dataAdmissao.toString() << " | Fim Contrato: " << fimContrato.toString() << "\n"
                  << "Departamento: " << departamento << " | Turno: " << turno << "\n"
                  << "Fixo Mensal: R$ " << salarioBase << " | Comissao: " << (percentualComissao * 100) << "%\n";
    }

    //regra de negocio para rescisao PJ
    double calcularRescisao(bool justaCausa) const override {
        if (justaCausa) {
            return 0; 
        }
        return (salarioBase + totalVendas) * 0.10; 
    }
};

// RELATORIO FINANCEIRO

class RelatorioFinanceiro {
public:

    static double custoTotalEmpresa(const std::vector<std::unique_ptr<Funcionario>>& lista) {
        double total = 0;
        for (const auto& f : lista) {
            if (f->isAtivo()) { 
                total += f->calcularSalario();
            }
        }
        return total;
    }

    static double custoPorVinculo(const std::vector<std::unique_ptr<Funcionario>>& lista,
                                  TipoVinculo tipo) {
        double total = 0;
        for (const auto& f : lista) {
            if (f->isAtivo() && f->getVinculo() == tipo) {
                total += f->calcularSalario();
            }
        }
        return total;
    }

    static void folhaPagamento(const std::vector<std::unique_ptr<Funcionario>>& lista) {

        std::cout << COR_TITULO << "\n========== DASHBOARD FINANCEIRO ==========\n" << COR_RESET;

        for (const auto& f : lista) {
            if (f->isAtivo()) { 
                f->render();
            }
        }

        //custo toral
        std::cout << COR_TITULO << "\nCusto Total Empresa: " << COR_SAIDA << "R$ "
                  << custoTotalEmpresa(lista) << COR_RESET << "\n";
    }
};

#endif
