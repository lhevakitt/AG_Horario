#include "Util.h"

class Populacao {

    private:

        vector<Individuo*> populacao;
    
        float scoreAlvo;

        int tamanhoDaPopulacao;
        int percentualDeElite;

    public:

        Populacao(void);
        ~Populacao(void);

        void criarPopulacao(vector<Turma*> cadastroDeTurmas);
        void destruirPopulacao(void);

        Individuo* getTopoDaLista(void);
        void salvarTopoDaLista(void);
        bool avaliarTopoDaLista(void);
        
        void fitness(void);
        void ordenar(void);

        void mutacao(void);
        void crossover(void);
        void regenerar(void);

        void print(int top = 10);
        
};