#ifndef CURSO_H
#define CURSO_H

#include "UCs.h"
#include "Alunos.h"
#include "Avaliacoes.h"
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Curso {
    
    private:
        vector<UCs> Vucs;
        vector<UCs>::iterator it_u;

        vector<Alunos> Valunos;
        vector<Alunos>::iterator it_a;

        vector<Avaliacoes> Vavaliacoes;
        vector<Avaliacoes>::iterator it_av;
        vector<Avaliacoes>::iterator it_wanted;

    public:
        Curso() {};
        Curso(string nome_curso);
        ~Curso() {};
        
        vector<Alunos> dados_Alunos();
        vector<UCs> dados_UCs();
        vector<Avaliacoes> dados_Avaliacoes();
        Alunos encontrarAluno(int num);
        UCs encontrarUC(int cod);
        Avaliacoes encontrarAvaliacao();
        void listarAlunos();
        void listarUCs();
        void consultarAluno();
        void consultarUC();
        void consultarAvaliacao();
        void inserirAluno();
        void inserirUC();
        bool inserirAvaliacao();
};

#endif /* CURSO_H */