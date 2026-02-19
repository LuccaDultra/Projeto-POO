#include "funcionario.h"
#include <stdexcept> //oara lancar erros

using namespace std;

//iniciando a variavel estatica
int Funcionario::contadorMatriculas = 2026000; 

//implementando construtor funcionario
Funcionario::Funcionario(string n, string c, string r, Endereco end, Data adm, double sal, TipoVinculo v)
    : nome(n), cpf(c), rg(r), endereco(end), dataAdmissao(adm), salarioBase(sal), vinculo(v) {
    
    //validacao de CPF
    if (!validarCPF(c)) {
        throw std::invalid_argument("Erro: CPF invalido! Deve conter 11 digitos.");
    }
    this->cpf = c;

    //validacao de salario
    if (sal < 0) {
        throw std::invalid_argument("Erro: Salario nao pode ser negativo.");
    }
    
    //validacao de data
    if (!adm.valida()) {
        throw std::invalid_argument("Erro: Data de admissao invalida.");
    }

    //iteracao da matricula
    this->matricula = ++contadorMatriculas; 
}

//implementacao da funcao validar cpf
bool Funcionario::validarCPF(const std::string& cpf) {
    //logica simples para verificar apenas se tiver o tam = 11, podemos melhorar
    return cpf.length() == 11; 
}

//getters
string Funcionario::getNome() const { return nome; }
int Funcionario::getMatricula() const { return matricula; }
string Funcionario::getCpf() const { return cpf; }
Data Funcionario::getDataAdmissao() const { return dataAdmissao; }
double Funcionario::getSalarioBase() const { return salarioBase; }
string Funcionario::getRg() const { return rg; }
string Funcionario::getCargo() const { return cargo; }