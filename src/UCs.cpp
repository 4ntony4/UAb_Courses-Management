#include "UCs.h"
#include "Menu.h"

using namespace std;

UCs::UCs(bool b) {
    /* criar uma instância do objeto com valores a zero 
    para posterior comparação ou modificação */ 
    if (!b) {
        nome = "";
        codigo = 0;
        ano = 0;
        sem = 0;
        ects = 0;
    }
}

void UCs::update_uc(string novo_nome, int novo_codigo, int novo_ano, int novo_sem, int novo_ects) {
    nome = novo_nome;
    codigo = novo_codigo;
    ano = novo_ano;
    sem = novo_sem;
    ects = novo_ects;
}

void UCs::print_obj_data() {
    int tamanhoColuna1 = 9;
    int tamanhoColuna2 = charCount(nome) + 2;
    int tamanhoLinha = tamanhoColuna1 + tamanhoColuna2;

    print_dashes(tamanhoLinha);
    cout << endl;

    print_spaces( tamanhoColuna1 - charCount("UC:") );
    cout << "UC:";

    print_spaces(2);
    cout << nome << endl;

    print_spaces( tamanhoColuna1 - charCount("Código:") );
    cout << "Código:";

    print_spaces(2);
    cout << codigo << endl;

    print_spaces( tamanhoColuna1 - charCount("Ano:") );
    cout << "Ano:";

    print_spaces(2);
    cout << ano << endl;

    print_spaces( tamanhoColuna1 - charCount("Semestre:") );
    cout << "Semestre:";

    print_spaces(2);
    cout << sem << endl;

    print_spaces( tamanhoColuna1 - charCount("ECTS:") );
    cout << "ECTS:";

    print_spaces(2);
    cout << ects << endl;

    print_dashes(tamanhoLinha);
    cout << endl;
}

void UCs::save_uc() {
    /* guarda dados formatados de uma UC num ficheiro */
    ofstream MyFile;
    char delimiter = ';';

    MyFile.open("data/dados_ucs.txt", ios::app);

    MyFile << nome << delimiter << codigo << delimiter << ano << delimiter << sem << delimiter << ects << endl;

    MyFile.close();
}