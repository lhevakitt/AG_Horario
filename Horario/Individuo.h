#include "Turma.cpp"
#include <random>

class Individuo {

    private:

        vector<Turma*> turmas;
        vector<int> posicoesParaSorteio;

        float IMPEDITIVO;
        float SEVERO;
        float ACEITAVEL;

        int numeroDeTurmas;
        int mudarHorario;
        int mudarDia;
        int mudarSemana;

        int problemasDeChoquesDeHorario;
        int problemasDeDisponibilidade;
        int problemasDeCargaHoraria;
        int problemasDeAulasDaDisciplina;
        int problemasDeAulasDoProfessor;

        float score;

    public:

        Individuo(vector<Turma*> turmasCadastradas, bool gerarNovasTurmas = true);
        ~Individuo(void);

        float getFitness(void);

        int disponibilidade(void);
        int cargaHoraria(void);
        int choquesDeHorario(void);
        int aulasDaMesmaDisciplina(void);
        int aulasDoMesmoProfessor(void);

        float fitness(void);
        void mutacao(void);
        void crossover(Individuo* pai, Individuo* mae);
        void regenerar(void);

        void salvar(string preNome);
        void exportar(string nome);
        void print(bool imprimirGrade = true);

};