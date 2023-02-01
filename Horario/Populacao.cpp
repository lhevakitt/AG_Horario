#include "Populacao.h"

Populacao::Populacao(void) {

    this->scoreAlvo = -40.0f;

    this->tamanhoDaPopulacao = 1000;
    this->percentualDeElite = 20;
    
}

Populacao::~Populacao(void) {

    this->destruirPopulacao();    
}


void Populacao::criarPopulacao(vector<Turma*> cadastroDeTurmas) {

    Individuo* individuo = new Individuo(cadastroDeTurmas, true);

    for (int posicao = 0; posicao < this->tamanhoDaPopulacao; posicao++) {
        this->populacao.push_back(individuo);
        individuo = new Individuo(cadastroDeTurmas);
    }
}

void Populacao::destruirPopulacao(void) {

    for (Individuo* individuo : this->populacao) {
        delete individuo;
    }

    this->populacao.clear();
}


Individuo* Populacao::getTopoDaLista(void) {

    return this->populacao.at(0);
}

void Populacao::salvarTopoDaLista(void) {

    Individuo* topo = this->populacao.at(0);
    topo->salvar("Top");
    topo->exportar("Top");
}

bool Populacao::avaliarTopoDaLista(void) {

    bool retorno = false;

    Individuo* topo = this->populacao.at(0);
    float score = topo->getFitness();

    retorno = score >= this->scoreAlvo;
    return retorno;

}


void Populacao::fitness(void) {
    
    for (Individuo* individuo : this->populacao) {
        individuo->fitness();
    }
}

void Populacao::ordenar(void) {

    Util::mergeSort(this->populacao);

}


void Populacao::mutacao(void) {

    int posicaoLimiar = (this->tamanhoDaPopulacao * this->percentualDeElite) / 100;
    posicaoLimiar = 1;

    for (int posicao = posicaoLimiar; posicao < this->tamanhoDaPopulacao; posicao++) {
        Individuo* filho = this->populacao.at(posicao);
        filho->mutacao();
    }
}

void Populacao::crossover(void) {

    Individuo* pai = nullptr, *mae = nullptr, *filho = nullptr;
    int posicaoLimiar = (this->tamanhoDaPopulacao * this->percentualDeElite) / 100;
    int indexPai = 0, indexMae = 0;

    for (int posicao = posicaoLimiar; posicao < this->tamanhoDaPopulacao; posicao++) {

        indexPai = rand() % posicaoLimiar;
        pai = this->populacao.at(indexPai);
        do {
            indexMae = rand() % posicaoLimiar;
        } while (indexPai == indexMae);
        mae = this->populacao.at(indexMae);
        
        filho = this->populacao.at(posicao);
        filho->crossover(pai, mae);
    }
}

void Populacao::regenerar(void) {

    int posicaoLimiar = (this->tamanhoDaPopulacao * this->percentualDeElite) / 100;
    posicaoLimiar = 0;

    for (int posicao = posicaoLimiar; posicao < this->tamanhoDaPopulacao; posicao++) {
        Individuo* filho = this->populacao.at(posicao);
        filho->regenerar();
    }
}


void Populacao::print(int top) {

    for (Individuo* Individuo : this->populacao) {
        Individuo->print(false);
        top--;
        if (top == 0) {
            break;
        }
    }
}