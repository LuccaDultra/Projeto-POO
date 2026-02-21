#include <iostream>
#include <vector>
#include <memory>
#include "funcionario.h"
#include "Financeiro.h"

using namespace std;

int main() {
    // Criando a lista de funcionários usando unique_ptr
    vector<unique_ptr<Funcionario>> funcionarios;

    try {
        //Adicionando um Gerente
        // make_unique cria o objeto e já coloca no ponteiro inteligente de forma segura
        funcionarios.push_back(make_unique<FuncionarioCLT>(
            "Gustavo", "12345678901", "RG123", 
            Endereco{"Rua A", 10, "Centro", "Aracaju", "49000-000"}, 
            Data{15, 9, 2025}, 
            3500.00, true // Salario base + Adicional Noturno
        ));

        // Adicionando um Estagiário
        funcionarios.push_back(make_unique<Estagiario>(
            "Ana", "98765432100", "RG456", 
            Endereco{"Rua B", 20, "Jardins", "Aracaju", "49000-001"}, 
            Data{10, 1, 2026}, 
            30, 15.0 // 30 horas * 15 reais/hora
        ));

        // Adicionando um Vendedor
        funcionarios.push_back(make_unique<Vendedor>(
            "Carlos", "11122233344", "RG789", 
            Endereco{"Rua C", 30, "Siqueira", "Aracaju", "49000-002"}, 
            Data{1, 2, 2025}, 
            1500.00, 50000.00, 0.05 // Fixo + (50k vendas * 5%)
        ));

        // Testando o Polimorfismo
        cout << ">>> Testando Polimorfismo e Hierarquia <<<\n";
        RelatorioFinanceiro::folhaPagamento(funcionarios);

        // Teste específico de custo por vínculo
        double custoEstagiarios = RelatorioFinanceiro::custoPorVinculo(funcionarios, TipoVinculo::ESTAGIARIO);
        cout << "\nCusto apenas com Estagiarios: " << custoEstagiarios << endl;

    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
    }

    return 0;
}
