#include "Disciplina.cpp"


class Turma {

    private:
        
        vector<Dia<Disciplina*>*> semana;
        vector<Disciplina*> cadastro;
                
        string nomeDaTurma;
        int diasDeAula;
        int aulasPorDia;
        int numeroDeAulas;
        int aulasNaGrade;

    public:

        Turma(void);
        Turma(Turma& turmaDeReferencia);
        Turma(string nomeDaTurma, int numeroDeAulas, int aulasPorDia);
        ~Turma(void);

        string getNomeDaTurma(void);
        int getTotalDeDiasDeAula(void);
        int getTotalDeAulasPorDia(void);
        int getTotalDeAulas(void);
        int getTotalDeAulasNaGrade(void);
        
        void adicionarSemana(void);
        void removerSemana(void);

        int getTotalDeDisciplinasCadastradas(void);
        void adicionarDisciplina(Disciplina* disciplina);
        Disciplina* consultarDisciplina(int posicaoNoCadastro);
        
        Disciplina* getHorario(int diaDaSemana, int horarioDoDia);
        void setHorario(Disciplina* disciplina, int diaDaSemana, int horarioDoDia);
        
        void gerarHorario(int diaDaSemana, int horarioDoDia);
        void gerarDia(int diaDaSemana);
        void gerarSemana(void);

        void alterarHorario(int diaDaSemana, int horarioDoDia);
        void alterarDia(int diaDaSemana);
        void alterarSemana(void);

        void copiarHorario(Turma* turmaOrigem, int diaDaSemana, int horarioDoDia);
        void copiarDia(Turma* turmaOrigem, int diaDaSemana);
        void copiarSemana(Turma* turmaOrigem);

        int disponibilidade(void);
        int cargaHoraria(void);
        int choqueDeHorario(Turma* outraTurma);
        int aulasDaMesmaDisciplina(void);
        int aulasDoMesmoProfessor(void);
        
        void corrigirAulasLivres(void);

        void salvar(string nomeDoArquivo);
        void print(void);
};