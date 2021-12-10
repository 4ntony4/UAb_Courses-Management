#include "Alunos.h"
#include "Menu.h"

using namespace std;

Alunos::Alunos(bool b) {
    /* criar uma instância do objeto com valores a zero 
    para posterior comparação ou modificação */ 
    if (!b) {
        nome = "";
        num = 0;
    }
}

void Alunos::update_aluno(string novo_nome, int novo_num) {
    nome = novo_nome;
    num = novo_num;
}

void Alunos::print_obj_data() {
    int tamanhoColuna1 = 7;
    int tamanhoColuna2 = charCount(nome) + 2;
    int tamanhoLinha = tamanhoColuna1 + tamanhoColuna2; 

    print_dashes(tamanhoLinha);
    cout << endl;

    print_spaces( tamanhoColuna1 - charCount("Nome:") );
    cout << "Nome:";

    print_spaces( tamanhoColuna2 - charCount(nome) );
    cout << nome << endl;

    print_spaces( tamanhoColuna1 - charCount("Número:") );
    cout << "Número:";

    print_spaces(2);
    cout << num << endl;
    
    print_dashes(tamanhoLinha);
    cout << endl;
}

void Alunos::save_aluno() {
    /* guarda dados formatados de um aluno num ficheiro */
    ofstream MyFile;
    char delimiter = ';';

    MyFile.open("data/dadosAlunos.dat", ios::app);

    MyFile << nome << delimiter << num << endl;

    MyFile.close();
}