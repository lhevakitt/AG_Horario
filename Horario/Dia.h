
#include <vector>
#include <string>
#include <type_traits>
#include "stdio.h"

using namespace std;

template <class Exemplo>
class Dia {

private:

    Exemplo* horarios;
    int tamanho;
    
public:
    
    Dia(int horarios, Exemplo valorInicial);
    ~Dia();

    static string getDiaDaSemana(int dia);
    static int getDiaDaSemana(string dia);
    Exemplo getHorario(int posicao);
    void setHorario(int posicao, Exemplo valor);

    int getTotalDeHorarios(void);

    void print(void);
};