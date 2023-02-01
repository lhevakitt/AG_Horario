#include "Professor.h"


void Professor::cadastrar(string novoNome, int numeroDeAulas) {
 
    this->nome = novoNome;
    this->numeroDeAulas = numeroDeAulas;
    this->diasDaSemana = 5;

    for (int posicao = 0; posicao < this->diasDaSemana; posicao++) {
        this->agenda.push_back(new Dia<bool>(numeroDeAulas, true));
    }
}

Professor::Professor(string novoNome) {

    this->cadastrar(novoNome, 5);
}

Professor::Professor(string novoNome, int numeroDeAulas) {

   this->cadastrar(novoNome, numeroDeAulas);
}

Professor::~Professor(void) {

    for (Dia<bool>* dia : this->agenda) {
       delete dia;
    }

    this->agenda.clear();
}


string Professor::getNome(void) {

    return this->nome;
}

bool Professor::getDisponibilidade(int diaDaSemana, int horarioDoDia) {

    bool retorno = false;

    Dia<bool>* dia = nullptr;

    if (diaDaSemana < 0 || diaDaSemana > 4 || horarioDoDia < 0 || horarioDoDia > this->numeroDeAulas) {
        return retorno;
    }

    dia = this->agenda.at(diaDaSemana);

    if (dia == nullptr) {
        return retorno;
    }

    retorno = dia->getHorario(horarioDoDia);

    return retorno;
}

void Professor::setIndisponibilidade(int diaDaSemana) {

    Dia<bool>* dia = nullptr;

    if (diaDaSemana < 0 || diaDaSemana > 4) {
        return;
    }

    dia = this->agenda.at(diaDaSemana);
    
    for (int horario = 0; horario < this->numeroDeAulas; horario++) {
        this->setIndisponibilidade(diaDaSemana, horario);
    }
    
}

void Professor::setIndisponibilidade(int diaDaSemana, int horarioDoDia) {

    Dia<bool>* dia = nullptr;

    if (diaDaSemana < 0 || diaDaSemana > 4 || horarioDoDia < 0 || horarioDoDia > this->numeroDeAulas) {
        return;
    }

    dia = this->agenda.at(diaDaSemana);

    if (dia == nullptr) {
        return;
    }

    dia->setHorario(horarioDoDia, false);

}

void Professor::setIndisponibilidade(string diaDaSemana, int horarioDoDia) {

    int diaDaSemanaInt = Dia<bool>::getDiaDaSemana(diaDaSemana);
    this->setIndisponibilidade(diaDaSemanaInt, horarioDoDia);
}


void Professor::salvar(Json::Value& arquivo) {

    Json::Value lista(Json::arrayValue);
    Dia<bool>* diaDaSemana = nullptr;
    string diaDaSemanaString;

    arquivo["Professores"][this->nome]["numeroDeAulas"] = this->numeroDeAulas;

    for (int dia = 0; dia < this->diasDaSemana; dia++) {
        lista.clear();
        diaDaSemana = this->agenda.at(dia);
        diaDaSemanaString = diaDaSemana->getDiaDaSemana(dia);
        for (int horario = 0; horario < this->numeroDeAulas; horario++) {
            bool disponibilidade = diaDaSemana->getHorario(horario);
            lista.append(disponibilidade);
        }
        arquivo["Professores"][this->nome]["agenda"][diaDaSemanaString] = lista;
    }
}

void Professor::print(void) {

    Dia<bool>* dia = NULL;

    int posicao = 0;
    int tamanho = this->agenda.size();

    printf("Professor %s\n\n", this->nome.c_str());

    for (posicao = 0; posicao < tamanho; posicao++) {

        printf("Dia [%d]:\n", posicao);
        dia = this->agenda.at(posicao);

        if (dia == nullptr) {
            printf("Professor não trabalha neste dia\n");
        } else {
            dia->print();   
        }
        printf("\n");
    }

}