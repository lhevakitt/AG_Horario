#include "Disciplina.h"

Disciplina::Disciplina(string nome, int cargaHoraria, Professor* professor) {

    this->nome = nome;
    this->cargaHoraria = cargaHoraria;
    this->professor = professor;
    this->sigla = "abc";

    transform(this->nome.begin(), this->nome.begin() + this->sigla.size(), this->sigla.begin(), ::toupper);
}

Disciplina::~Disciplina(void) {

    delete this->professor;

}

Professor* Disciplina::getProfessor(void) {

    return this->professor;
}

int Disciplina::getCargaHoraria(void) {

    return this->cargaHoraria;
}

string Disciplina::getNome(void) {
    
    return this->nome;
}

string Disciplina::getSigla(void) {

    return this->sigla;
}

void Disciplina::salvar(Json::Value& arquivo) {

    Json::Value raiz = arquivo["Disciplinas"];
    
    arquivo["Disciplinas"][this->nome]["cargaHoraria"] = this->cargaHoraria;
    arquivo["Disciplinas"][this->nome]["professor"] = this->professor->getNome();

    this->professor->salvar(arquivo);

}

void Disciplina::print(void) {
    
    printf("Disciplina: %s", this->nome.c_str());
    printf("Carga horária: %d\n", this->cargaHoraria);
    printf("Nome do professor: %s\n\n", this->professor->getNome().c_str());
}