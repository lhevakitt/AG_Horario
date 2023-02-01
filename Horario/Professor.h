#include "Dia.cpp"
#include "jsoncpp.cpp"
#include <fstream>
#include <iostream>

class Professor {

    private:

        vector<Dia<bool>*> agenda;

        string nome;
        int numeroDeAulas;
        int diasDaSemana;

        void cadastrar(string novoNome, int numeroDeAulas);

    public:

        Professor(string novoNome);
        Professor(string novoNome, int numeroDeAulas);
        ~Professor(void);

        string getNome(void);

        bool getDisponibilidade(int diaDaSemana, int horarioDoDia);
        void setIndisponibilidade(int diaDaSemana);
        void setIndisponibilidade(int diaDaSemana, int horarioDoDia);
        void setIndisponibilidade(string diaDaSemana, int horarioDoDia);
        
        void salvar(Json::Value& arquivo);
        void print(void);

};