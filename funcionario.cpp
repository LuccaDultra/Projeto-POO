#include "funcionario.h"
#include <stdexcept> 

using namespace std;

//iniciando a variavel estatica
int Funcionario::contadorMatriculas = 2026000; 

//implementando construtor funcionario 
Funcionario::Funcionario(string n, string c, Endereco end, Data adm, double sal, TipoVinculo v, string t,string d)
    : nome(n), cpf(c), endereco(end), dataAdmissao(adm), salarioBase(sal), vinculo(v), turno(t), departamento(d) {
    
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
    
    // Todo funcionario entra como ativo por padrao
    this->ativo = true;
}

//implementacao da funcao validar cpf
bool Funcionario::validarCPF(const std::string& cpf) {
    //logica simples para verificar apenas se tiver o tam = 11, podemos melhorar
    return cpf.length() == 11; 
}

//getters
string Funcionario::getNome() const { return nome; }

// a string nome vai retornar somente a primera parte, para evitar quebra de formatacao em alguns menus
string Funcionario::getPrimeiroNome() const {
    size_t espaco = nome.find_first_of(" \t");
    if (espaco != string::npos) {
        return nome.substr(0, espaco);
    }
    return nome;
}

int Funcionario::getMatricula() const { return matricula; }
string Funcionario::getCpf() const { return cpf; }
Data Funcionario::getDataAdmissao() const { return dataAdmissao; }
double Funcionario::getSalarioBase() const { return salarioBase; }
string Funcionario::getCargo() const { return cargo; }
TipoVinculo Funcionario::getVinculo() const { return vinculo; }

//helper para converter o vinculo em string
string Funcionario::getVinculoString() const {
    if (vinculo == TipoVinculo::CLT) return "CLT";
    if (vinculo == TipoVinculo::ESTAGIARIO) return "Estagio";
    if (vinculo == TipoVinculo::PJ) return "PJ";
    return "";
}

string Funcionario::getDepartamento() const { return departamento; }
string Funcionario::getTurno() const { return turno; }
bool Funcionario::isAtivo() const { return ativo; } 

//implementacao dos setters com tratamento de erro
void Funcionario::setDepartamento(const std::string& d) { this->departamento = d; }
void Funcionario::setTurno(const std::string& t) { this->turno = t; }
void Funcionario::setSalarioBase(double s) { 
    if (s < 0) throw std::invalid_argument("Salario nao pode ser negativo.");
    this->salarioBase = s; 
}
void Funcionario::setAtivo(bool status) { this->ativo = status; }
