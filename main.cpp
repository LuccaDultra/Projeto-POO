#include <iostream>
#include <vector>
#include <memory>
#include "funcionario.h"
#include "financeiro.h"
#include "rh.h" 
#include "interface.h"


using namespace std;

int main() {
    // Criando a lista de funcionários usando unique_ptr
    vector<unique_ptr<Funcionario>> funcionarios;

    // data atual simulada para o RH conseguir calcular ferias e contratos
    Data hoje = {21, 2, 2026};

    try {
        //Adicionando um Gerente
        // make_unique cria o objeto e já coloca no ponteiro inteligente de forma segura
        funcionarios.push_back(make_unique<FuncionarioCLT>(
            "Gustavo", "12345678901", // REMOVIDO: "RG123"
            Endereco{"Rua A", 10, "Centro", "Aracaju", "49000-000"}, 
            Data{15, 2, 2024}, 
            3500.00, true,  // Salario base + Adicional Noturno
            "Noite", "Administrativo"
        ));

        // Adicionando um Estagiário
        funcionarios.push_back(make_unique<Estagiario>(
            "Ana", "98765432100", // REMOVIDO: "RG456"
            Endereco{"Rua B", 20, "Jardins", "Aracaju", "49000-001"}, 
            Data{10, 1, 2026}, Data{15, 3, 2026}, //data fim do contrato
            30, 15.0, // 30 horas * 15 reais/hora
            "Manha", "Estagio"
        ));

        // Adicionando um Vendedor
        funcionarios.push_back(make_unique<Vendedor>(
            "Carlos", "11122233344", // REMOVIDO: "RG789"
            Endereco{"Rua C", 30, "Siqueira", "Aracaju", "49000-002"}, 
            Data{1, 2, 2025}, Data{1, 12, 2026}, //data fim do contrato 
            1500.00, 50000.00, 0.05,  // Fixo + (50k vendas * 5%)
            "Tarde", "Vendas"
        ));

        // Inicia a interface pelo método iniciar
        InterfaceCLI::iniciar(funcionarios);

    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
    }

    return 0;
}
