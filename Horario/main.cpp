#include "Populacao.cpp"

vector<Professor*> professoresCadastrados;
vector<Disciplina*> disciplinasCadastradas;
vector<Disciplina*> disciplinasDaTurma;

string int2String(int numero) {

    string retorno;

    char buffer[100];
    itoa(numero, buffer, 100);
    retorno = string(buffer);

    return retorno;
}


vector<Turma*> cadastroOficial(void) {

    vector<Turma*> retorno;

    int numeroDeTurmas = 4;
    int diasDeAula = 4;
    int aulasPorDia = 5;
    int numeroDeAulas = 26; //Soma de todas as cargas horarias das disciplinas

    vector<Professor*> professores;
    vector<Disciplina*> disciplinas;

    Professor* nenhum = new Professor("nenhum", aulasPorDia);
    Professor* edwalquiria = new Professor("edwalquiria", aulasPorDia);
    Professor* laudjane = new Professor("laudjane", aulasPorDia);
    Professor* jadson = new Professor("jadson", aulasPorDia);
    Professor* lourenco = new Professor("lourenco", aulasPorDia);
    Professor* jessica = new Professor("jessica", aulasPorDia);
    Professor* juliana = new Professor("juliana", aulasPorDia);
    Professor* leo = new Professor("leo", aulasPorDia);
    
    // for (int dia = 0; dia <= diasDeAula; dia++) {
    //     edwalquiria->setIndisponibilidade(dia, aulasPorDia - 1);
    //     laudjane->setIndisponibilidade(dia, aulasPorDia - 1);
    //     jadson->setIndisponibilidade(dia, aulasPorDia - 1);
    //     jessica->setIndisponibilidade(dia, aulasPorDia - 1);
    //     for (int horario = 0; horario < aulasPorDia - 1; horario++) {
    //         nenhum->setIndisponibilidade(dia, horario);
    //     }
    // }
    //jessica->setIndisponibilidade(4);
    juliana->setIndisponibilidade(2);
    juliana->setIndisponibilidade(3);
    juliana->setIndisponibilidade(4);
    leo->setIndisponibilidade(0);
    leo->setIndisponibilidade(4);
    
    professores.push_back(edwalquiria);
    professores.push_back(laudjane);
    professores.push_back(jadson);
    professores.push_back(lourenco);
    professores.push_back(jessica);
    professores.push_back(juliana);
    professores.push_back(leo);
    professores.push_back(nenhum);

    //Disciplina* nenhuma = new Disciplina("nenhuma", (5 * aulasPorDia) - numeroDeAulas, nenhum);
    Disciplina* portugues = new Disciplina("portugues", 6, edwalquiria);
    Disciplina* matematica = new Disciplina("matematica", 6, laudjane);
    Disciplina* historia = new Disciplina("historia", 3, jadson);
    Disciplina* geografia = new Disciplina("geografia", 3, jadson);
    Disciplina* ingles = new Disciplina("ingles", 2, lourenco);
    Disciplina* ciencias1 = new Disciplina("ciencias1", 3, jessica);
    Disciplina* ciencias2 = new Disciplina("ciencias2", 3, leo);
    Disciplina* arte = new Disciplina("arte", 2, jessica);
    Disciplina* emocional = new Disciplina("emocional", 1, juliana);

    //disciplinas.push_back(nenhuma);
    disciplinas.push_back(portugues);
    disciplinas.push_back(matematica);
    disciplinas.push_back(historia);
    disciplinas.push_back(geografia);
    disciplinas.push_back(ingles);
    disciplinas.push_back(arte);
    disciplinas.push_back(emocional);
    disciplinas.push_back(ciencias1);
    disciplinas.push_back(ciencias2);

    for (int posicao = 0; posicao < numeroDeTurmas; posicao++) {

        string nomeDaTurma = int2String(posicao + 6) + "a_Serie";
        Turma* turma = new Turma(nomeDaTurma, numeroDeAulas, aulasPorDia);
        
        for (int index = 0; index < disciplinas.size() - 2; index++) {
            turma->adicionarDisciplina(disciplinas.at(index));
        }

        if (posicao < 2) {
            turma->adicionarDisciplina(ciencias1);
        } else {
            turma->adicionarDisciplina(ciencias2);
        }

        retorno.push_back(turma);
    }

    return retorno;

}

void carregarProfessores(Json::Value dados) {
    //-------------------------
    // CADASTRO DE PROFESSORES
    //-------------------------
    Professor* novoProfessor = nullptr;
    Json::Value professores = dados["Professores"]; 
    Json::Value::Members membros = professores.getMemberNames();
    for (int index = 0; index < membros.size(); index++) {
        string nome = membros[index];
        bool achou = false;
        for (int posicao = 0; (posicao < professoresCadastrados.size()) && (! achou); posicao++) {
            novoProfessor = professoresCadastrados.at(posicao);
            string nomeDoProfessor = novoProfessor->getNome();
            achou = nome.compare(nomeDoProfessor) == 0;
        }
        if (achou) {
            continue;
        }
        int numeroDeAulas = professores[nome]["numeroDeAulas"].asInt();
        novoProfessor = new Professor(nome, numeroDeAulas);
        Json::Value::Members diasDaSemana = professores[nome]["agenda"].getMemberNames();
        for (int dia = 0; dia < diasDaSemana.size(); dia++) {
            string diaDaSemanaString = diasDaSemana[dia];
            Json::Value horarios = professores[nome]["agenda"][diaDaSemanaString];
            for (Json::Value::ArrayIndex horario = 0; horario < horarios.size(); horario++) { 
                bool disponivel = horarios[horario].asBool();
                if (! disponivel) {
                    novoProfessor->setIndisponibilidade(diaDaSemanaString, horario);
                }
            }
        }
        professoresCadastrados.push_back(novoProfessor);
    }
}

void carregarDisciplinas(Json::Value dados) {
    //-------------------------
    //CADASTRO DE DISCIPLINAS
    //-------------------------
    Disciplina* novaDisciplina = nullptr;
    Json::Value disciplinas = dados["Disciplinas"];
    Json::Value::Members membros = disciplinas.getMemberNames();
    for (int index = 0; index < membros.size(); index++) {
        string nome = membros[index];
        bool achou = false;
        for (int posicao = 0; (posicao < disciplinasCadastradas.size()) && (!achou); posicao++) {
            novaDisciplina = disciplinasCadastradas.at(posicao);
            string nomeDaDisciplina = novaDisciplina->getNome();
            achou = nome.compare(nomeDaDisciplina) == 0;
        }
        if (achou) {
            disciplinasDaTurma.push_back(novaDisciplina);
            continue;
        }
        int cargaHoraria = disciplinas[nome]["cargaHoraria"].asInt();
        string nomeDoProfessor = disciplinas[nome]["professor"].asString();
        Professor* novoProfessor = nullptr;
        for (int posicao = 0; posicao < professoresCadastrados.size(); posicao++) {
            novoProfessor = professoresCadastrados.at(posicao);
            string novoNome = novoProfessor->getNome();
            achou = novoNome.compare(nomeDoProfessor) == 0;
            if (achou) {
                break;
            }
            novoProfessor = nullptr;
        }
        if (novoProfessor == nullptr) {
            return;
        }
        novaDisciplina = new Disciplina(nome, cargaHoraria, novoProfessor);
        disciplinasCadastradas.push_back(novaDisciplina);
        disciplinasDaTurma.push_back(novaDisciplina);
    }
}

void carregarTurmas(string nomeDoArquivo, vector<Turma*>& cadastroDeTurmas) {

    Json::Reader arquivo;
    Json::Value dados;
    
    ifstream entrada;
    entrada.open(nomeDoArquivo);
    if (! entrada.is_open()) {
        return;
    }
    arquivo.parse(entrada, dados);

    carregarProfessores(dados);
    carregarDisciplinas(dados);
    
    //-------------------------
    //CADASTRO DE TURMAS
    //-------------------------
    Turma* novaTurma = nullptr;
    Json::Value turmas = dados["Turmas"];
    Json::Value::Members membros = turmas.getMemberNames();
    Disciplina* novaDisciplina = nullptr;
    for (int index = 0; index < membros.size(); index++) {
        string nome = membros[index];
        int diasDeAula = turmas[nome]["diasDeAula"].asInt(); //NOT USED
        int aulasPorDia = turmas[nome]["aulasPorDia"].asInt();
        int aulasNaGrade = 29;
        novaTurma = new Turma(nome, aulasNaGrade, aulasPorDia);
        novaTurma->adicionarSemana();
        for (int posicao = 0; posicao < disciplinasDaTurma.size(); posicao++) {
            novaDisciplina = disciplinasDaTurma.at(posicao);
            novaTurma->adicionarDisciplina(novaDisciplina);
        }
        Json::Value::Members diasDaSemana = turmas[nome]["agenda"].getMemberNames();
        for (int dia = 0; dia < diasDaSemana.size(); dia++) {
            string diaDaSemanaString = diasDaSemana[dia];
            int diaDaSemana = Dia<bool>::getDiaDaSemana(diaDaSemanaString);
            Json::Value aulasDoDia = turmas[nome]["agenda"][diaDaSemanaString];
            for (int horario = 0; horario < aulasPorDia; horario++) {
                string nomeDaDisciplina = aulasDoDia[horario].asString();
                novaDisciplina = nullptr;
                bool achou = false;
                for (int posicao = 0; (posicao < disciplinasCadastradas.size()) && (!achou); posicao++) {
                    novaDisciplina = disciplinasCadastradas.at(posicao);
                    string nomeCadastrado = novaDisciplina->getNome();
                    achou = nomeDaDisciplina.compare(nomeCadastrado) == 0;
                }
                novaTurma->setHorario(novaDisciplina, diaDaSemana, horario);
            }
        }
    }
    //-------------------------
    //FIM DO CADASTRO
    //-------------------------
    cadastroDeTurmas.push_back(novaTurma);
    disciplinasDaTurma.clear();

}


void TesteIndividuo(vector<Turma*> cadastroDeTurmas) {

    Individuo* um = new Individuo(cadastroDeTurmas);
    
    um->fitness();
    um->print();
 
    delete um;
}


int main() { 

    srand(time(nullptr));

    vector<Turma*> cadastroDeTurmas;

    //carregarTurmas("Top_6a_Serie.json", cadastroDeTurmas);
    //carregarTurmas("Top_7a_Serie.json", cadastroDeTurmas);
    //carregarTurmas("Top_8a_Serie.json", cadastroDeTurmas);
    //carregarTurmas("Top_9a_Serie.json", cadastroDeTurmas);
    
    cadastroDeTurmas = cadastroOficial();
   
    //TesteIndividuo(cadastroDeTurmas);
    //return 0;

    Populacao* populacao = new Populacao();

    int iteracao = 0;
    int limite = 20000;
    bool sair = false;

    populacao->criarPopulacao(cadastroDeTurmas);
    
    while (!sair) {
        iteracao++;

        if (iteracao % limite == 0) {

            printf("\n\n----------------------\n");
            printf("Recriando a Populacao\n");
            printf("----------------------\n\n\n");

            populacao->salvarTopoDaLista();    
            populacao->destruirPopulacao();

            cadastroDeTurmas.clear();
            carregarTurmas("Top_6a_Serie.json", cadastroDeTurmas);
            carregarTurmas("Top_7a_Serie.json", cadastroDeTurmas);
            carregarTurmas("Top_8a_Serie.json", cadastroDeTurmas);
            carregarTurmas("Top_9a_Serie.json", cadastroDeTurmas);
            
            populacao->criarPopulacao(cadastroDeTurmas);
        }
        populacao->fitness();
        populacao->ordenar();
        populacao->crossover();
        populacao->mutacao();
        //populacao->regenerar();

        if (iteracao % 100 == 1) {
            printf(">> ITERACAO %05d\t", iteracao);
            populacao->print(1);
        }

        sair = populacao->avaliarTopoDaLista();
    }
    populacao->salvarTopoDaLista();    
    printf("\n\n#################################################");
    printf(">> Horario encontrado em %d Iteracoes\n", iteracao);
    printf("\n\n#################################################");
}