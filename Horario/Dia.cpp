#include "Dia.h"

template<class Exemplo>
Dia<Exemplo>::Dia(int horarios, Exemplo valorInicial) {

    if (horarios < 0) {
        return;
    }

    this->horarios = new Exemplo[horarios];
    this->tamanho = horarios;

    fill(this->horarios, this->horarios + this->tamanho, valorInicial);
}

template<class Exemplo>
Dia<Exemplo>::~Dia() {

    delete this->horarios;
}

template<class Exemplo>
string Dia<Exemplo>::getDiaDaSemana(int dia) {

    string retorno;

    switch(dia) {
    case 0:
        retorno = "Segunda";
        break;
    case 1:
        retorno = "Terca";
        break;
    case 2:
        retorno = "Quarta";
        break;
    case 3:
        retorno = "Quinta";
        break;
    case 4:
        retorno = "Sexta";
        break;
    case 5:
        retorno = "Sabado";
        break;
    case 6:
        retorno = "Domingo";
        break;
    default:
        retorno = "Nenhum";
    }

    return retorno;
}

template<class Exemplo>
int Dia<Exemplo>::getDiaDaSemana(string dia) {

    int retorno = -1;

    if (dia.compare("Segunda") == 0) {
        retorno = 0;
    } else if (dia.compare("Terca") == 0) {
        retorno = 1;
    } else if (dia.compare("Quarta") == 0) {
        retorno = 2;
    } else if (dia.compare("Quinta") == 0) {
        retorno = 3;
    } else if (dia.compare("Sexta") == 0) {
        retorno = 4;
    } else if (dia.compare("Sabado") == 0) {
        retorno = 5;
    } else if (dia.compare("Domingo") == 0) {
        retorno = 6;
    }

    return retorno;
}

template<class Exemplo>
Exemplo Dia<Exemplo>::getHorario(int posicao) {

    Exemplo retorno;

    if (posicao < 0 || posicao >= this->tamanho) {
        return retorno;
    }
            
    retorno = this->horarios[posicao];
    return retorno;
}

template<class Exemplo>
void Dia<Exemplo>::setHorario(int posicao, Exemplo valor) {

    if (posicao < 0 || posicao >= this->tamanho) {
        return;
    }

    this->horarios[posicao] = valor;
}

template<class Exemplo>
int Dia<Exemplo>::getTotalDeHorarios(void) {

    return this->tamanho;
}

template<class Exemplo>
void Dia<Exemplo>::print(void) {

    int posicao = 0;
    
    for (posicao = 0; posicao < this->tamanho; posicao++) {
        
        if (is_same<Exemplo, bool>::value) {
            bool valor = this->horarios[posicao];
            printf(valor ? "[%d] - true\n" : "[%d] - false\n", posicao);
        }    
        
    }
    printf("\n");
}