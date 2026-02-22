#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <ctime> // Para data atual

//corres p personalizar o termianl
#define COR_TITULO "\033[0m" //amarelo
#define COR_ERRO "\033[31m"   //vermelho
#define COR_AVISO "\033[31m"  //vermelho
#define COR_SAIDA "\033[31m"  //vermelho(Deficit/Pagamento)
#define COR_SIM "\033[32m"    //verde
#define COR_NAO "\033[31m"    //vermelho
#define COR_RESET "\033[0m"   //restaura a cor padrao

//struct do endereco
struct Endereco {
    std::string rua;
    int numero;
    std::string bairro;
    std::string cidade;
    std::string cep;
};

//struct para data
struct Data {
    int dia, mes, ano;

    //metodo para validar se a data faz sentido, vamos aprimorar isso com a evolucao do codigo
    bool valida() const {
        if (mes < 1 || mes > 12 || dia < 1 || dia > 31) return false;
        if (ano < 1900 || ano > 2100) return false;
        return true;
    }

    static Data hoje() {
        std::time_t t = std::time(nullptr);
        std::tm* agora = std::localtime(&t);
        
        return { agora->tm_mday, agora->tm_mon + 1, agora->tm_year + 1900 };
    }


    //metodo auxiliar para imprimir a data no formato dd/mm/aa
    std::string toString() const {
        return std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(ano);
    }
};

#endif
