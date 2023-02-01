#include "Individuo.cpp"

namespace Util {

    void mergeSort(vector<Individuo*>& lista) {

        vector<Individuo*> listaEsquerda;
        vector<Individuo*> listaDireita;
        
        int posicaoEsquerda = 0;
        int posicaoDireita = 0;
        int tamanhoEsquerdo = 0;
        int tamanhoDireito = 0;
        int tamanho = lista.size();

        bool sair = false;
        
        if (tamanho == 1) {
             return;
        }

        listaEsquerda = vector<Individuo*>(lista.begin(), lista.begin() + tamanho / 2);
        listaDireita = vector<Individuo*>(lista.begin() + tamanho / 2, lista.end());
        
        mergeSort(listaEsquerda);
        mergeSort(listaDireita);

        tamanhoEsquerdo = listaEsquerda.size();
        tamanhoDireito = listaDireita.size();

        lista.clear();
        do {
            Individuo* esquerdo = listaEsquerda.at(posicaoEsquerda);
            Individuo* direito = listaDireita.at(posicaoDireita);

            float fitnessEsquerdo = esquerdo->getFitness();
            float fitnessDireito = direito->getFitness();

            if (fitnessEsquerdo > fitnessDireito) {
                lista.push_back(esquerdo);
                posicaoEsquerda++;
            } else {
                lista.push_back(direito);
                posicaoDireita++;
            }

            sair = (posicaoDireita >= tamanhoDireito) || (posicaoEsquerda >= tamanhoEsquerdo);
        } while (! sair);

        if (posicaoDireita >= tamanhoDireito) {
            for (int posicao = posicaoEsquerda; posicao < tamanhoEsquerdo; posicao++) {
                Individuo* esquerdo = listaEsquerda.at(posicao);
                lista.push_back(esquerdo);
            }
        } else if (posicaoEsquerda >= tamanhoEsquerdo) {
            for (int posicao = posicaoDireita; posicao < tamanhoDireito; posicao++) {
                Individuo* direito = listaDireita.at(posicao);
                lista.push_back(direito);
            }
        }
    }
}
