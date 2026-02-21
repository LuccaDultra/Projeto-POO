#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include "utils.h"
#include <string>

//enum class do tipo de vinculo do funcionario
enum class TipoVinculo { CLT, ESTAGIARIO, PJ };

//classe base do funcionario
class Funcionario {
protected: 
    //informacoes sensiveis como protected
    std::string nome;
    std::string cpf;
    std::string rg;
    Endereco endereco;
    
    //controle interno, numero da contratacao
    static int contadorMatriculas; //conta o n de matriculas
    int matricula;                 //salva o n de matricula
    
    //outras infos de contratacao, podemos adicionar mais coisas no futuro
    Data dataAdmissao;
    double salarioBase;
    TipoVinculo vinculo;
    std::string cargo;

    //metodo auxiliar privado pra validar o cpf
    bool validarCPF(const std::string& cpf);

public:
    //construtor do funcionariop
    Funcionario(std::string nome, std::string cpf, std::string rg, Endereco end, Data admissao, double salario, TipoVinculo v);
    
    //destrutor virtual
    virtual ~Funcionario() = default;

    //Metodo que podem ser usados
    virtual double calcularSalario() const = 0; 
    virtual void render() const = 0;

    //getters
    std::string getNome() const;
    int getMatricula() const;
    std::string getCpf() const;
    Data getDataAdmissao() const;
    double getSalarioBase() const;
    std::string getRg() const;
    std::string getCargo() const;
    TipoVinculo getVinculo() const;
};

#endif
