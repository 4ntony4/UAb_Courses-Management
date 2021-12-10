#include "Avaliacoes.h"
#include "Menu.h"

using namespace std;

Avaliacoes::Avaliacoes(bool b) {
    /* criar uma instância do objeto com valores a zero ou sem significado
    para posterior comparação ou modificação */ 
    if (!b) {
        UCs nova_uc(0);
        Alunos novo_aluno(0);

        uc = nova_uc;
        aluno = novo_aluno;
        avContinua = false;
        efolioA = -1;
        efolioB = -1;
        pfolio = -1;
        exame = -1;
        notaFinal = -1;
        aprovacao = false;
    }
}

void Avaliacoes::update_avaliacao(UCs nova_uc, Alunos novo_aluno, bool nova_avContinua, float novo_efolioA, float novo_efolioB, float novo_pfolio, int novo_exame, int nova_notaFinal, int nova_aprovacao) {
    /* atualizar todos os atributos 
     de um objeto da classe Avaliacoes */
    uc = nova_uc;
    aluno = novo_aluno;
    avContinua = nova_avContinua;
    efolioA = novo_efolioA;
    efolioB = novo_efolioB;
    pfolio = novo_pfolio;
    exame = novo_exame;
    notaFinal = nova_notaFinal;
    aprovacao = nova_aprovacao;
}

void Avaliacoes::update_avaliacao(UCs nova_uc, Alunos novo_aluno) {
    uc = nova_uc;
    aluno = novo_aluno;
}

void Avaliacoes::update_avaliacao(bool nova_avContinua) {
    avContinua = nova_avContinua;
}

void Avaliacoes::update_avaliacao(float novo_efolioA, float novo_efolioB, float novo_pfolio) {
    efolioA = novo_efolioA;
    efolioB = novo_efolioB;
    pfolio = novo_pfolio;
}

void Avaliacoes::update_avaliacao(int novo_exame) {
    exame = novo_exame;
}

void Avaliacoes::update_avaliacao() {
    /* cálculo da nota final consoante o tipo de avaliação
     e atualização do atributo aprovacao */
    float pfolio_temp;

    if ( pfolio != -1 ) {
        pfolio_temp = pfolio;
    }
    else {
        pfolio_temp = 0;
    }

    if ( avContinua == true ) {
        
        notaFinal = (int)round(efolioA + efolioB + pfolio_temp);
        
        if ( notaFinal >= 10 && pfolio >= 5.5 ) {
            aprovacao = true;
        }
        else {
            aprovacao = false;
        }
    }
    else {

        notaFinal = exame;
        
        if ( notaFinal >=  10 ) {
            aprovacao = true;
        }
        else {
            aprovacao = false;
        }
    }
}

void Avaliacoes::print_obj_data() {
    int tamanhoColuna1 = 11;
    int tamanhoColuna2 = 2;
    int tamanhoLinha;
    int max = charCount(uc.get_nome());

    if ( charCount(aluno.get_nome()) > max ) {
        max = charCount(aluno.get_nome());
    }

    tamanhoColuna2 += max;
    tamanhoLinha = tamanhoColuna1 + tamanhoColuna2;

    print_dashes(tamanhoLinha);
    cout << endl;

    print_spaces( tamanhoColuna1 - charCount("Aluno:") );
    cout << "Aluno:";

    print_spaces(2);
    cout << aluno.get_nome() << endl;

    print_spaces( tamanhoColuna1 - charCount("UC:") );
    cout << "UC:";

    print_spaces(2);
    cout << uc.get_nome() << endl;

    print_spaces( tamanhoColuna1 - charCount("Avaliação:") );
    cout << "Avaliação:";

    print_spaces(2);
    if (avContinua) {

        cout << "Contínua" << endl;

        print_spaces( tamanhoColuna1 - charCount("e-Fólio A:") );
        cout << "e-Fólio A:";

        print_spaces(2);
        cout << efolioA << endl;

        print_spaces( tamanhoColuna1 - charCount("e-Fólio B:") );
        cout << "e-Fólio B:";

        print_spaces(2);
        cout << efolioB << endl;

        if ( pfolio != -1 ) {
            print_spaces( tamanhoColuna1 - charCount("p-Fólio:") );
            cout << "p-Fólio:";

            print_spaces(2);
            cout << pfolio << endl;
        }
    }
    else {
        cout << "Exame Final" << endl;

        print_spaces( tamanhoColuna1 - charCount("Exame:") );
        cout << "Exame:";

        print_spaces(2);
        cout << exame << endl;
    }

    print_spaces( tamanhoColuna1 - charCount("Nota Final:") );
    cout << "Nota Final:";

    print_spaces(2);
    cout << notaFinal << endl;

    print_spaces( tamanhoColuna1 - charCount("Estado:") );
    cout << "Estado:";

    print_spaces(2);
    if (aprovacao) {
        cout << "APROVADO" << endl;
    }
    else {
        cout << "REPROVADO" << endl;
    }

    print_dashes(tamanhoLinha);
    cout << endl;
}

void Avaliacoes::save_avaliacao() {
    /* guarda dados formatados de uma avaliação num ficheiro */
    ofstream MyFile;
    char delimiter = ';';

    MyFile.open("data/dados_avaliacoes.txt", ios::app);

    MyFile << aluno.get_num() << delimiter << uc.get_codigo() << delimiter << avContinua << delimiter << efolioA << delimiter << efolioB << delimiter << pfolio << delimiter << exame << delimiter << notaFinal << delimiter << aprovacao << endl;

    MyFile.close();
}

void Avaliacoes::delete_avaliacao(string eraseLine) {
    /* apaga dados formatados de uma avaliação num ficheiro */
    string path = "data/dados_avaliacoes.txt";
    const char *p = path.c_str();
    string line;

    ifstream fin;
    ofstream fout;

    fin.open(path);
    fout.open("data/temp.txt");

    while ( getline(fin, line) ) {
        /* escrever todas as linhas para o ficheiro temporário excepto a linha a apagar */
        if ( line != eraseLine ) {
            fout << line << endl;
        }
    }

    fout.close();
    fin.close();

    remove(p);
    rename("data/temp.txt", p);
}

string Avaliacoes::get_file_line() {
    /* converte os dados de uma avaliação numa string */
    string path = "data/tempLine.txt";
    const char *p = path.c_str();
    string line;
    char delimiter = ';';

    ofstream fout(path);

    fout << aluno.get_num() << delimiter << uc.get_codigo() << delimiter << avContinua << delimiter << efolioA << delimiter << efolioB << delimiter << pfolio << delimiter << exame << delimiter << notaFinal << delimiter << aprovacao << endl;

    fout.close();

    ifstream fin(path);

    getline(fin, line);

    remove(p);

    return line;
}