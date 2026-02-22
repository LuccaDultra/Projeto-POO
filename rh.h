#ifndef MODULO_RH_H
#define MODULO_RH_H

#include "funcionario.h"
#include "financeiro.h" 
#include <vector>
#include <memory>
#include <iostream>
#include <string>

//classe do rh, calcula ferias e controla a logica do menu rh
class ModuloRH {
private:
    static int calcularDiferencaDias(Data inicio, Data fim) {
        int diasInicio = (inicio.ano * 360) + (inicio.mes * 30) + inicio.dia;
        int diasFim = (fim.ano * 360) + (fim.mes * 30) + fim.dia;
        return diasFim - diasInicio;
    }

public:
    
    //Lista funcionArios com mais de 1 ano e 11 meses sem ferias
    static void listarFeriasVencidas(const std::vector<std::unique_ptr<Funcionario>>& lista, Data dataAtual) {
        std::cout << COR_TITULO << "\n========== FERIAS VENCIDAS ==========\n" << COR_RESET;
        bool encontrou = false;
        
        for (const auto& f : lista) {
            if (!f->isAtivo()) continue; 
            
            int diasTrabalhados = calcularDiferencaDias(f->getDataAdmissao(), dataAtual);
            
            if (diasTrabalhados > 690) { 
                int diasVencidos = diasTrabalhados - 690;
                // Padrao Nome, Matricula, Admissao e Dias Vencidos apenas
                std::cout << COR_AVISO << "[VENCIDA] " << COR_RESET << f->getPrimeiroNome() 
                          << " | Mat: " << f->getMatricula() 
                          << " | Adm: " << f->getDataAdmissao().toString() 
                          << " | Dias vencidos: " << COR_AVISO << diasVencidos << COR_RESET << "\n";
                encontrou = true;
            }
        }
        if (!encontrou) std::cout << "Nenhum funcionario com ferias vencidas.\n";
    }
    
    //Lista funcionarios com ferias a vencer
    static void listarFeriasParaVencer(const std::vector<std::unique_ptr<Funcionario>>& lista, Data dataAtual) {
        std::cout << COR_TITULO << "\n========== FERIAS PARA VENCER ==========\n" << COR_RESET;
        bool encontrou = false;
        
        for (const auto& f : lista) {
            if (!f->isAtivo()) continue; 
            
            int diasTrabalhados = calcularDiferencaDias(f->getDataAdmissao(), dataAtual);
            
            if (diasTrabalhados >= 660 && diasTrabalhados <= 690) { 
                int diasFaltando = 690 - diasTrabalhados;
                std::cout << COR_TITULO << "[ALERTA] " << COR_RESET << f->getPrimeiroNome() 
                          << " | Mat: " << f->getMatricula() 
                          << " | Adm: " << f->getDataAdmissao().toString() 
                          << " | Faltam p/ vencer: " << COR_TITULO << diasFaltando << " dias" << COR_RESET << "\n";
                encontrou = true;
            }
        }
        if (!encontrou) std::cout << "Nenhum funcionario com ferias proximas de vencer.\n";
    }

    //listar estagiarios e contratos com contrato vencendo em 30 dias
    static void listarContratosVencendo(const std::vector<std::unique_ptr<Funcionario>>& lista, Data dataAtual) {
        std::cout << COR_TITULO << "\n========== CONTRATOS VENCENDO ==========\n" << COR_RESET;
        bool encontrou = false;

        for (const auto& f : lista) {
            
            if (!f->isAtivo()) continue; 

            Estagiario* est = dynamic_cast<Estagiario*>(f.get());
            Vendedor* pj = dynamic_cast<Vendedor*>(f.get());

            Data fimContrato = {0, 0, 0}; 

            if (est != nullptr) { 
                fimContrato = est->getFimContrato();
            } else if (pj != nullptr) {  
                fimContrato = pj->getFimContrato();
            }

            if (est != nullptr || pj != nullptr) {
                int diasParaVencer = calcularDiferencaDias(dataAtual, fimContrato);

                if (diasParaVencer > 0 && diasParaVencer <= 30) {
                    // Padrao Nome, Matricula, Admissao e Tempo Restante apenas
                    std::cout << COR_TITULO << "[ALERTA] " << COR_RESET << f->getPrimeiroNome() 
                              << " | Mat: " << f->getMatricula()
                              << " | Adm: " << f->getDataAdmissao().toString()
                              << " | Tempo restante: " << COR_TITULO << diasParaVencer << " dias" << COR_RESET << "\n";
                    encontrou = true;
                } else if (diasParaVencer <= 0) {
                    std::cout << COR_AVISO << "[EXPIRADO] " << COR_RESET << f->getPrimeiroNome() 
                              << " | Mat: " << f->getMatricula()
                              << " | Adm: " << f->getDataAdmissao().toString()
                              << " | " << COR_AVISO << "Contrato ja venceu!" << COR_RESET << "\n";
                    encontrou = true;
                }
            }
        }
        
        if (!encontrou) std::cout << "Nenhum contrato temporario vencendo nos proximos 30 dias.\n";
    }
};

#endif
