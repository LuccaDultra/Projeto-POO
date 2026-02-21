#ifndef MODULO_RH_H
#define MODULO_RH_H

#include "funcionario.h"
#include "financeiro.h" 
#include <vector>
#include <memory>
#include <iostream>
#include <string>

class ModuloRH {
private:
    //funcao auxiliar privada para calcular a diferença de dias entre duas datas, utiliza mes comercial 30 dias e ano comercial 660 dias
    static int calcularDiferencaDias(Data inicio, Data fim) {
        int diasInicio = (inicio.ano * 360) + (inicio.mes * 30) + inicio.dia;
        int diasFim = (fim.ano * 360) + (fim.mes * 30) + fim.dia;
        return diasFim - diasInicio;
    }

public:
    // =========================================================
    // 1. GESTAO DE FERIAS
    // =========================================================
    
    //Lista funcionArios com mais de 1 ano e 11 meses sem ferias
    static void listarFeriasVencidas(const std::vector<std::unique_ptr<Funcionario>>& lista, Data dataAtual) {
        std::cout << "\n========== ALERTA DE FERIAS VENCIDAS ==========\n";
        bool encontrou = false;
        
        //compara data atual - data admissao
        for (const auto& f : lista) {
            int diasTrabalhados = calcularDiferencaDias(f->getDataAdmissao(), dataAtual);
            
            if (diasTrabalhados >= 690) { 
                std::cout << "[ALERTA] Funcionario: " << f->getNome() 
                          << " | Matricula: " << f->getMatricula() 
                          << " | Admissao: " << f->getDataAdmissao().toString() 
                          << " | Dias na empresa: " << diasTrabalhados << "\n";
                encontrou = true;
            }
        }
        if (!encontrou) std::cout << "Nenhum funcionario com ferias vencidas.\n";
    }

    // =========================================================
    // 2. FILTROS
    // =========================================================

    //filtro de matricula
    static void buscarPorMatricula(const std::vector<std::unique_ptr<Funcionario>>& lista, int matBusca) {
        std::cout << "\n--- Busca por Matricula: " << matBusca << " ---\n";
        for (const auto& f : lista) {
            if (f->getMatricula() == matBusca) {
                f->render();
                return; //se encontrou, sai da funcao
            }
        }
        std::cout << "Funcionario nao encontrado.\n";
    }

    //filtro de nome
    static void buscarPorNome(const std::vector<std::unique_ptr<Funcionario>>& lista, const std::string& nomeBusca) {
        std::cout << "\n--- Busca por Nome: " << nomeBusca << " ---\n";
        bool encontrou = false;
        for (const auto& f : lista) {
            if (f->getNome() == nomeBusca) {
                f->render();
                encontrou = true;
            }
        }
        if (!encontrou) std::cout << "Funcionario nao encontrado.\n";
    }

    //filtrid de cpf
    static void buscarPorCPF(const std::vector<std::unique_ptr<Funcionario>>& lista, const std::string& cpfBusca) {
        std::cout << "\n--- Busca por CPF: " << cpfBusca << " ---\n";
        for (const auto& f : lista) {
            if (f->getCpf() == cpfBusca) {
                f->render();
                return;
            }
        }
        std::cout << "Funcionario nao encontrado.\n";
    }

    //filtro de cargo
    static void buscarPorCargo(const std::vector<std::unique_ptr<Funcionario>>& lista, const std::string& cargoBusca) {
        std::cout << "\n--- Funcionarios no cargo: " << cargoBusca << " ---\n";
        bool encontrou = false;
        for (const auto& f : lista) {
            if (f->getCargo() == cargoBusca) {
                std::cout << "- " << f->getNome() << " (Mat: " << f->getMatricula() << ")\n";
                encontrou = true;
            }
        }
        if (!encontrou) std::cout << "Nenhum funcionario encontrado neste cargo.\n";
    }

    // =========================================================
    // 3. CONTRATOS
    // =========================================================

    //listar estagiarios e contratos com contrato vencendo em 30 dias
    static void listarContratosVencendo(const std::vector<std::unique_ptr<Funcionario>>& lista, Data dataAtual) {
        std::cout << "\n========== CONTRATOS VENCENDO (30 DIAS) ==========\n";
        bool encontrou = false;

        for (const auto& f : lista) {
            
            //tenta converter o ponteiro base para as classes derivadas que possuem data de fim
            Estagiario* est = dynamic_cast<Estagiario*>(f.get());
            Vendedor* pj = dynamic_cast<Vendedor*>(f.get());

            Data fimContrato = {0, 0, 0}; 
            std::string tipoFunc = "";

            if (est != nullptr) { //se funcionou ele e estagiario
                fimContrato = est->getFimContrato();
                tipoFunc = "Estagiario";
            } else if (pj != nullptr) { //se nao, e pj 
                fimContrato = pj->getFimContrato();
                tipoFunc = "Contrato PJ";
            }

            //apenas em quem e estagiario ou pj
            if (est != nullptr || pj != nullptr) {
                
                //data fim - data atual
                int diasParaVencer = calcularDiferencaDias(dataAtual, fimContrato);

                if (diasParaVencer > 0 && diasParaVencer <= 30) {
                    std::cout << "[ALERTA] " << tipoFunc << ": " << f->getNome() 
                              << " | Vence em: " << diasParaVencer << " dias (" 
                              << fimContrato.toString() << ").\n";
                    encontrou = true;
                } else if (diasParaVencer <= 0) {
                    std::cout << "[EXPIRADO] " << tipoFunc << ": " << f->getNome() 
                              << " | Contrato ja venceu em " << fimContrato.toString() << "!\n";
                    encontrou = true;
                }
            }
        }
        
        if (!encontrou) std::cout << "Nenhum contrato temporario vencendo nos proximos 30 dias.\n";
    }
};

#endif