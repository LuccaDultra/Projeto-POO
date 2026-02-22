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
    Endereco endereco;
    
    // info p grade e organograma
    std::string departamento; 
    std::string turno;        

    //controle interno, numero da contratacao
    static int contadorMatriculas; //conta o n de matriculas
    int matricula;                 //salva o n de matricula
    
    // Controle de status do funcionario na empresa
    bool ativo; 
    
    //outras infos de contratacao, podemos adicionar mais coisas no futuro
    Data dataAdmissao;
    double salarioBase;
    TipoVinculo vinculo;
    std::string cargo;

    //metodo auxiliar privado pra validar o cpf
    bool validarCPF(const std::string& cpf);

public:
    //construtor do funcionario
    Funcionario(std::string nome, std::string cpf, Endereco end, Data admissao, double salario, TipoVinculo v,std::string turno = "Manha", std::string departamento = "Geral");
    
    //destrutor virtual
    virtual ~Funcionario() = default;

    //Metodo que podem ser usados
    virtual double calcularSalario() const = 0; 
    virtual void render() const = 0;
    
    // Metodos virtuais para exibir dados completos e calcular rescisao 
    virtual void exibirDetalhes() const = 0;
    virtual double calcularRescisao(bool justaCausa) const = 0;

    //getters
    std::string getNome() const;
    std::string getPrimeiroNome() const;
    int getMatricula() const;
    std::string getCpf() const;
    Data getDataAdmissao() const;
    double getSalarioBase() const;
    std::string getCargo() const;
    TipoVinculo getVinculo() const;
    std::string getVinculoString() const;
    std::string getDepartamento() const; 
    std::string getTurno() const;
    bool isAtivo() const; 

    //setters para permitir a edicao de dados no gerenciamento
    void setDepartamento(const std::string& d);
    void setTurno(const std::string& t);
    void setSalarioBase(double s);
    void setAtivo(bool status);
};

#endif
