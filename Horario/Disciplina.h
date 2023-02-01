#include <algorithm>
#include "Professor.cpp"

class Disciplina {

    private:

        Professor* professor;
        string nome;
        string sigla;
        int cargaHoraria;

    public:

        Disciplina(string nome, int cargaHoraria, Professor* professor);
        ~Disciplina(void);

        Professor* getProfessor(void);
        int getCargaHoraria(void);
        string getNome(void);
        string getSigla(void);

        void salvar(Json::Value& arquivo);
        void print(void);

};