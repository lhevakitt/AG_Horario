#include "Turma.h"

Turma::Turma(void) {

    this->diasDeAula = -1;

}

Turma::Turma(Turma& turmaDeReferencia) {

    this->nomeDaTurma = turmaDeReferencia.getNomeDaTurma();
    this->diasDeAula = turmaDeReferencia.getTotalDeDiasDeAula();
    this->aulasPorDia = turmaDeReferencia.getTotalDeAulasPorDia();
    this->numeroDeAulas = turmaDeReferencia.getTotalDeAulas();
    this->aulasNaGrade = turmaDeReferencia.getTotalDeAulasNaGrade();
    
    for (int posicao = 0; posicao < turmaDeReferencia.cadastro.size(); posicao++) {
        Disciplina* disciplina = turmaDeReferencia.cadastro.at(posicao);
        this->adicionarDisciplina(disciplina);
    }

    this->adicionarSemana();
    this->copiarSemana(&turmaDeReferencia);

}

Turma::Turma(string nomeDaTurma, int numeroDeAulas, int aulasPorDia) {
    
    this->diasDeAula = 5;
    this->nomeDaTurma = nomeDaTurma;
    this->numeroDeAulas = numeroDeAulas;
    this->aulasPorDia = aulasPorDia;
    this->aulasNaGrade = 0;

}

Turma::~Turma(void) {

    this->removerSemana();
    this->cadastro.clear();
}


string Turma::getNomeDaTurma(void) {

    return this->nomeDaTurma;
}

int Turma::getTotalDeDiasDeAula(void) {

    return this->diasDeAula;
}

int Turma::getTotalDeAulasPorDia(void) {

    return this->aulasPorDia;
}

int Turma::getTotalDeAulas(void) {

    return this->numeroDeAulas;
}

int Turma::getTotalDeAulasNaGrade(void) {

    return this->aulasNaGrade;
}


void Turma::adicionarSemana(void) {

    int posicaoInicial = this->semana.size();

    for (int posicao = posicaoInicial; posicao < this->diasDeAula; posicao++) {
        Dia<Disciplina*>* dia = new Dia<Disciplina*>(this->aulasPorDia, NULL);
        this->semana.push_back(dia);
    }
}

void Turma::removerSemana(void) {

    for (Dia<Disciplina*>* dia : this->semana) {
        delete dia;
    }

    this->semana.clear();
}


int Turma::getTotalDeDisciplinasCadastradas(void) {

    return this->cadastro.size();
}

void Turma::adicionarDisciplina(Disciplina* disciplina) {

    if (disciplina == nullptr) {
        return;
    }

    this->cadastro.push_back(disciplina);

}

Disciplina* Turma::consultarDisciplina(int posicaoNoCadastro) {

    Disciplina* retorno = nullptr;

    if (posicaoNoCadastro >= this->cadastro.size()) {
        return retorno;
    }

    retorno = this->cadastro.at(posicaoNoCadastro);
    return retorno;
}


Disciplina* Turma::getHorario(int diaDaSemana, int horarioDoDia) {

    Dia<Disciplina*>* diaSelecionado = nullptr;
    Disciplina* retorno = nullptr;

    if (diaDaSemana < 0 || diaDaSemana >= this->diasDeAula || horarioDoDia < 0 || horarioDoDia >= this->aulasPorDia) {
        return retorno;
    }

    diaSelecionado = this->semana.at(diaDaSemana);
    retorno = diaSelecionado->getHorario(horarioDoDia);

    return retorno;
}

void Turma::setHorario(Disciplina* disciplina, int diaDaSemana, int horarioDoDia) {

    Dia<Disciplina*>* diaSelecionado = nullptr;
    Disciplina* disciplinaCadastrada = nullptr;

    int disciplinasCadastradas = this->cadastro.size();

    bool achou = false;

    if (disciplina == nullptr || diaDaSemana < 0 || diaDaSemana >= this->diasDeAula || horarioDoDia < 0 || horarioDoDia >= this->aulasPorDia) {
        return;
    }

    for (int posicao = 0; (posicao < disciplinasCadastradas) && (!achou); posicao++) {
        disciplinaCadastrada = this->cadastro.at(posicao);
        string nomeCadastrado = disciplinaCadastrada->getNome();
        string nome = disciplina->getNome();
        achou = nome.compare(nomeCadastrado) == 0;
    }
    if (! achou) {
        return;
    }
    diaSelecionado = this->semana.at(diaDaSemana); 
    diaSelecionado->setHorario(horarioDoDia, disciplina); 
}


void Turma::gerarHorario(int diaDaSemana, int horarioDoDia) {

    Dia<Disciplina*>* diaSelecionado = nullptr;
    Disciplina* disciplina = nullptr;

    int disciplinaSelecionada = 0;
    int disciplinasCadastradas = this->cadastro.size();

    if (disciplinasCadastradas == 0 || diaDaSemana < 0 || diaDaSemana >= this->diasDeAula || horarioDoDia < 0 || horarioDoDia >= this->aulasPorDia) {
        return;
    }

    string nome;
    bool nenhuma = false;

    do {
        disciplinaSelecionada = rand() % disciplinasCadastradas;
        disciplina = this->cadastro.at(disciplinaSelecionada);
        nome = disciplina->getNome();
        nenhuma = nome.compare("nenhuma") == 0;
    } while (horarioDoDia != this->aulasPorDia - 1 && nenhuma);
    
    diaSelecionado = this->semana.at(diaDaSemana); 
    diaSelecionado->setHorario(horarioDoDia, disciplina);   
}

void Turma::gerarDia(int diaDaSemana) {

    if (diaDaSemana < 0 || diaDaSemana >= this->diasDeAula) {
        return;
    }

    for (int aula = 0; aula < this->aulasPorDia; aula++) {
        this->gerarHorario(diaDaSemana, aula);
    }
    
}

void Turma::gerarSemana(void) {

    for (int dia = 0; dia < this->diasDeAula; dia++) {
        this->gerarDia(dia);
    }
}


void Turma::alterarHorario(int diaDaSemana, int horarioDoDia) {

    Dia<Disciplina*>* dia = nullptr;
    Disciplina* novaDisciplina = nullptr, *antigaDisciplina = nullptr;

    if (diaDaSemana < 0 || diaDaSemana >= this->diasDeAula || horarioDoDia < 0 || horarioDoDia >= this->aulasPorDia) {
        return;
    }

    dia = this->semana.at(diaDaSemana);
    antigaDisciplina = dia->getHorario(horarioDoDia);

    switch (horarioDoDia) 
    {
    case 0:
    case 2:
        novaDisciplina = dia->getHorario(1);
        break;
    case 1:
        novaDisciplina = dia->getHorario(0);
        break;
    case 3:
        novaDisciplina = dia->getHorario(4);
        break;
    case 4:
        novaDisciplina = dia->getHorario(3);
        break;
    default:
        novaDisciplina = dia->getHorario(this->aulasPorDia - 2);
        break;
    }

    bool nenhuma = novaDisciplina->getNome().compare("nenhuma") == 0;

    while (antigaDisciplina == novaDisciplina || nenhuma) {
        int index = rand() % this->cadastro.size();
        novaDisciplina = this->cadastro.at(index);
        nenhuma = novaDisciplina->getNome().compare("nenhuma") == 0;
    }

    dia->setHorario(horarioDoDia, novaDisciplina);

}

void Turma::alterarDia(int diaDaSemana) {

    if (diaDaSemana < 0 || diaDaSemana >= this->diasDeAula) {
        return;
    }

    int horarioDoDia = rand() % 3;

    this->alterarHorario(diaDaSemana, horarioDoDia);
    this->alterarHorario(diaDaSemana, this->aulasPorDia - 1);
}

void Turma::alterarSemana(void) {

    for (int dia = 0; dia < this->diasDeAula; dia++) {
        this->alterarDia(dia);
    }
}


void Turma::copiarHorario(Turma* turmaOrigem, int diaDaSemana, int horarioDoDia) {

    Dia<Disciplina*>* diaOrigem = nullptr, *diaDestino = nullptr;
    Disciplina* disciplina = nullptr;

    if (diaDaSemana < 0 || diaDaSemana >= this->diasDeAula || diaDaSemana >= turmaOrigem->semana.size()) {
        return;
    }

    if (horarioDoDia < 0 || horarioDoDia >= this->aulasPorDia) {
        return;
    }

    diaOrigem = turmaOrigem->semana.at(diaDaSemana);
    disciplina = diaOrigem->getHorario(horarioDoDia);
    diaDestino = this->semana.at(diaDaSemana);
    diaDestino->setHorario(horarioDoDia, disciplina);
}

void Turma::copiarDia(Turma* turmaOrigem, int diaDaSemana) {

    for (int horario = 0; horario < this->aulasPorDia; horario++) {
        this->copiarHorario(turmaOrigem, diaDaSemana, horario);
    }
}

void Turma::copiarSemana(Turma* turmaOrigem) {

    for (int dia = 0; dia < this->diasDeAula; dia++) {
        this->copiarDia(turmaOrigem, dia);
    }
}


int Turma::disponibilidade(void) {

    int retorno = 0;

    Dia<Disciplina*>* diaDaSemana = nullptr;
    Disciplina* disciplina = nullptr;
    Professor* professor = nullptr;

    bool disponivel = false;

    for (int dia = 0; dia < this->diasDeAula; dia++) {
        diaDaSemana = this->semana.at(dia);
        for (int horario = 0; horario < this->aulasPorDia; horario++) {
            disciplina = diaDaSemana->getHorario(horario);
            professor = disciplina->getProfessor();
            disponivel = professor->getDisponibilidade(dia, horario);
            if (! disponivel) {
                retorno++;
            }
        }
    }

    return retorno;
}

int Turma::cargaHoraria(void) {

    int retorno = 0;
    
    Disciplina* aula = nullptr;

    for (Disciplina* disciplina : this->cadastro) {
        int alvo = disciplina->getCargaHoraria();
        int contador = 0;
        for (Dia<Disciplina*>* dia : this->semana) {
            for (int horario = 0; horario < this->aulasPorDia; horario++) {
                aula = dia->getHorario(horario);
                if (aula == disciplina) {
                    contador++;
                }
            }
        }
        retorno = retorno + abs(contador - alvo);
    }

    return retorno;
}

int Turma::choqueDeHorario(Turma* outraTurma) {

    int retorno = 0;

    if (outraTurma == nullptr) {
        return retorno;
    }

    Dia<Disciplina*> *diaDaTurma = nullptr, *diaDaOutraTurma = nullptr;
    Disciplina *aulaDaTurma = nullptr, *aulaDaOutraTurma = nullptr;
    Professor *professor = nullptr, *professorDaOutraTurma = nullptr;
    
    for (int dia = 0; dia < this->diasDeAula; dia++) {
        diaDaTurma = this->semana.at(dia);
        diaDaOutraTurma = outraTurma->semana.at(dia);

        for (int aula = 0; aula < this->aulasPorDia; aula++) {
            aulaDaTurma = diaDaTurma->getHorario(aula);
            aulaDaOutraTurma = diaDaOutraTurma->getHorario(aula);

            professor = aulaDaTurma->getProfessor();
            professorDaOutraTurma = aulaDaOutraTurma->getProfessor();

            if (professor == professorDaOutraTurma) {
                retorno++;
            }
        }
    }

    return retorno;
}

int Turma::aulasDaMesmaDisciplina(void) {

    int retorno = 0;

    for (Dia<Disciplina*>* dia : this->semana) {
        Disciplina* disciplinaAnterior = nullptr;
        int contador = 0;
        for (int horario = 0; horario < this->aulasPorDia; horario++) {
            Disciplina* disciplina = dia->getHorario(horario);
            if (disciplina == disciplinaAnterior) {
                contador++;
            } else {
                contador = 0;
            }
            if (contador >= 2) {
                retorno++;
            }
            disciplinaAnterior = disciplina;
        }
    }

    return retorno;
}

int Turma::aulasDoMesmoProfessor(void) {

    int retorno = 0;
    for (Disciplina* disciplina : this->cadastro) {
        Professor* professor = disciplina->getProfessor();
        for (Dia<Disciplina*>* dia : this->semana) {
            int contador = 0;
            for (int horario = 0; horario < this->aulasPorDia; horario++) {
                Disciplina* disciplinaDoHorario = dia->getHorario(horario);
                Professor* professorDoHorario = disciplinaDoHorario->getProfessor();

                if (professorDoHorario == professor) {
                    contador++;
                }
            }
            if (contador > 2) {
                retorno++;
            }
        }
    }

    return retorno;
}


void Turma::corrigirAulasLivres(void) {

    Disciplina* nenhuma = nullptr;

    for (Disciplina* disciplinaCadastrada : this->cadastro) {
        string nome = disciplinaCadastrada->getNome();

        if (nome.compare("nenhuma") == 0) {
            nenhuma = disciplinaCadastrada;
            break;
        }
    }

    if (nenhuma == nullptr) {
        return;
    }

    for (int dia = 0; dia < this->diasDeAula; dia++) {
        Dia<Disciplina*>* diaDaSemana = this->semana.at(dia);
        Disciplina* disciplinaDaGrade = nullptr;
        for (int horario = 0; horario < this->aulasPorDia - 1; horario++) {
            do {
                if (disciplinaDaGrade == nenhuma) {
                    this->alterarHorario(dia, horario);
                }
                disciplinaDaGrade = diaDaSemana->getHorario(horario);
            } while (disciplinaDaGrade == nenhuma);
        }
        int percentual = rand() % 5;
        if (percentual != 0) {
            this->setHorario(nenhuma, dia, this->aulasPorDia - 1);
        }
    }

    
}


void Turma::salvar(string nomeDoArquivo) {
    
    ofstream saida;
    Json::Value arquivo;
    Json::Value lista(Json::arrayValue);

    Dia<Disciplina*>* diaDaSemana = nullptr;
    Disciplina* disciplina = nullptr;
    string nome;
    string diaDaSemanaString;

    arquivo["Turmas"][this->nomeDaTurma]["diasDeAula"] = this->diasDeAula;
    arquivo["Turmas"][this->nomeDaTurma]["aulasPorDia"] = this->aulasPorDia;

    for (int dia = 0; dia < this->diasDeAula; dia++) {
        lista.clear();
        diaDaSemana = this->semana.at(dia);
        diaDaSemanaString = diaDaSemana->getDiaDaSemana(dia);
        for (int horario = 0; horario < this->aulasPorDia; horario++) {
            disciplina = diaDaSemana->getHorario(horario);
            nome = disciplina->getNome();
            lista.append(nome);
        }
        arquivo["Turmas"][this->nomeDaTurma]["agenda"][diaDaSemanaString] = lista;
    }

    for (int posicao = 0; posicao < this->cadastro.size(); posicao++) {
        disciplina = this->cadastro.at(posicao);
        disciplina->salvar(arquivo);
    }

    saida.open(nomeDoArquivo);
    saida << arquivo << endl;
    saida.close();
}


void Turma::print(void) {

    Dia<Disciplina*>* diaDaSemana = nullptr;
    Disciplina* disciplina = nullptr;

    for (int horario = 0; horario < this->aulasPorDia; horario++) {
        string linha;
        for (int dia = 0; dia < this->diasDeAula; dia++) {
            diaDaSemana = this->semana.at(dia);
            disciplina = diaDaSemana->getHorario(horario);
            linha += disciplina->getSigla() + "\t";
        }
        linha += "\n";
        printf(linha.c_str());
    }
    printf("\n");
}