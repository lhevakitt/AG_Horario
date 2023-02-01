#include "Individuo.h"

Individuo::Individuo(vector<Turma*> turmasCadastradas, bool gerarNovasTurmas) {

    this->ACEITAVEL = -2.5f;
    this->SEVERO = -5.0f;
    this->IMPEDITIVO = -10.0f;

    this->mudarHorario = 75;
    this->mudarDia = 20;
    this->mudarSemana = 5;

    Turma *novaTurma = nullptr, *turma = nullptr;

    this->numeroDeTurmas = turmasCadastradas.size();

    for (int contador = 0; contador < this->numeroDeTurmas; contador++) {

        turma = turmasCadastradas.at(contador);

        novaTurma = new Turma(*turma);

        if (gerarNovasTurmas) {
            novaTurma->removerSemana();
            novaTurma->adicionarSemana();
            novaTurma->gerarSemana();
        }
        
        this->turmas.push_back(novaTurma);
        this->posicoesParaSorteio.push_back(contador);
    }   

    this->score = 0.0f;

    this->problemasDeCargaHoraria = 0;
    this->problemasDeChoquesDeHorario = 0;
    this->problemasDeDisponibilidade = 0;
    this->problemasDeAulasDaDisciplina = 0;
    this->problemasDeAulasDoProfessor = 0;

}

Individuo::~Individuo(void) {

    for (Turma* turma : this->turmas) {
        delete turma;
    }
}


float Individuo::getFitness(void) {

    return this->score;
}


int Individuo::disponibilidade(void) {

    this->problemasDeDisponibilidade = 0;

    for (Turma* turma : this->turmas) {
        this->problemasDeDisponibilidade += turma->disponibilidade();
    }

    return this->problemasDeDisponibilidade;
}

int Individuo::cargaHoraria(void) {

    this->problemasDeCargaHoraria = 0;

    for (Turma* turma : this->turmas) {
        this->problemasDeCargaHoraria += turma->cargaHoraria();
    }

    return this->problemasDeCargaHoraria;
}

int Individuo::choquesDeHorario(void) {

    this->problemasDeChoquesDeHorario = 0;

    Turma *turma1 = nullptr, *turma2 = nullptr;

    for (int posicaoInicial = 0; posicaoInicial < this->numeroDeTurmas - 1; posicaoInicial++) {
        turma1 = this->turmas.at(posicaoInicial);
        for (int posicao = posicaoInicial + 1; posicao < this->numeroDeTurmas; posicao++) {
            turma2 = this->turmas.at(posicao);
            this->problemasDeChoquesDeHorario += turma1->choqueDeHorario(turma2);
        }
    }

    return this->problemasDeChoquesDeHorario;
}

int Individuo::aulasDaMesmaDisciplina(void) {

    this->problemasDeAulasDaDisciplina = 0;

    for (Turma* turma : this->turmas) {
        this->problemasDeAulasDaDisciplina += turma->aulasDaMesmaDisciplina();
    }

    return this->problemasDeAulasDaDisciplina;
}

int Individuo::aulasDoMesmoProfessor(void) {

    this->problemasDeAulasDoProfessor = 0;

    for (Turma* turma : this->turmas) {
        this->problemasDeAulasDoProfessor += turma->aulasDoMesmoProfessor();
    }

    //Evitar punição dupla para 3 aulas da mesma disciplina
    this->problemasDeAulasDoProfessor -= this->problemasDeAulasDaDisciplina;
    
    return this->problemasDeAulasDoProfessor;
}


float Individuo::fitness(void) {

    this->score = 0.0f;

    this->score += ((float) this->choquesDeHorario()) * this->IMPEDITIVO;
    this->score += ((float) this->cargaHoraria()) * this->IMPEDITIVO;
    this->score += ((float) this->disponibilidade()) * this->SEVERO;
    this->score += ((float) this->aulasDaMesmaDisciplina()) * this->SEVERO;
    this->score += ((float) this->aulasDoMesmoProfessor()) * this->ACEITAVEL;

    return this->score;
}

void Individuo::mutacao(void) {

    Turma* turma = nullptr;

    int percentual = rand() % 100;
    int turmaSelecionada = 0;
    int diasDeAula = 0;
    int diaSelecionado = 0;
    int aulasPorDia = 0;
    int aulaSelecionada = 0;

    turmaSelecionada = rand() % this->numeroDeTurmas;
    turma = this->turmas.at(turmaSelecionada);
    diasDeAula = turma->getTotalDeDiasDeAula();
    diaSelecionado = rand() % diasDeAula;
    aulasPorDia = turma->getTotalDeAulasPorDia();
    aulaSelecionada = rand() % aulasPorDia;

    if (percentual < this->mudarSemana) {

        turma->gerarSemana();

    } else if (percentual < this->mudarDia) {

        turma->gerarDia(diaSelecionado);

    } else if (percentual < this->mudarHorario) {

        turma->alterarHorario(diaSelecionado, aulaSelecionada);
    }
}

void Individuo::crossover(Individuo* pai, Individuo* mae) {

    Turma* turma = nullptr, *novaTurma = nullptr;

    auto random = default_random_engine {};
    shuffle (this->posicoesParaSorteio.begin(), this->posicoesParaSorteio.end(), random);
   
    for (int index = 0; index < this->numeroDeTurmas; index++) {
        
        turma = this->turmas.at(index);
        int posicaoDoSorteio = this->posicoesParaSorteio.at(index);
        if (posicaoDoSorteio % 2 == 0) {
            novaTurma = pai->turmas.at(posicaoDoSorteio);
        } else {
            novaTurma = mae->turmas.at(posicaoDoSorteio);
        }
        turma->copiarSemana(novaTurma);
    }
}


void Individuo::salvar(string preNome) {

    for (Turma* turma : this->turmas) {
        string nomeDaTurma = turma->getNomeDaTurma();
        string nomeDoArquivo = preNome + "_" + nomeDaTurma + ".json";
        turma->salvar(nomeDoArquivo);
    }
}

void Individuo::exportar(string nome) {

    fstream arquivo;
    string nomeDoArquivo = nome + ".csv";
    arquivo.open(nomeDoArquivo, fstream::out);

    if (! arquivo.is_open()) {
        return;
    }

    for (Turma* turma : this->turmas) {
        string nomeDaTurma = turma->getNomeDaTurma();
        arquivo << nomeDaTurma << endl;

        int diasDeAula = turma->getTotalDeDiasDeAula();
        for (int dia = 0; dia < diasDeAula; dia++) {
            string diaDaSemana = Dia<bool>::getDiaDaSemana(dia);
            arquivo << diaDaSemana << ",";
        }
        arquivo << endl;

        int aulasPorDia = turma->getTotalDeAulasPorDia();
        for (int horario = 0; horario < aulasPorDia; horario++) {
            for (int dia = 0; dia < diasDeAula; dia++) {
                Disciplina* disciplina = turma->getHorario(dia, horario);
                string nomeDaDisciplina = disciplina->getNome();
                arquivo << nomeDaDisciplina << ",";
            }
            arquivo << endl;
        }

        int tamanhoDoCadastro = turma->getTotalDeDisciplinasCadastradas();
        for (int posicao = 0; posicao < tamanhoDoCadastro; posicao++) {
            Disciplina* disciplina = turma->consultarDisciplina(posicao);
            Professor* professor = disciplina->getProfessor();

            string nomeDaDisciplina = disciplina->getNome();
            string nomeDoProfessor = professor->getNome();
            arquivo << nomeDaDisciplina << "," << nomeDoProfessor << endl;
        }
        
    }
    arquivo.close();
}

void Individuo::print(bool imprimirGrade) {

    int contador = 0;

    if (imprimirGrade) {
        for (Turma* turma : this->turmas) {

            contador++;
            printf("--------------------\n");
            printf("TURMA [%d]\n", contador);
            printf("--------------------\n\n");

            turma->print();
        }
    }
    //printf("#################\n");
    printf("SCORE = %0.1f\t - Choques = %d / CH = %d / Disp = %d / 3-Disc = %d / 3-Prof = %d\n",
        this->score, 
        this->problemasDeChoquesDeHorario,
        this->problemasDeCargaHoraria,
        this->problemasDeDisponibilidade,
        this->problemasDeAulasDaDisciplina,
        this->problemasDeAulasDoProfessor
    );
    //printf("#################\n\n");

}