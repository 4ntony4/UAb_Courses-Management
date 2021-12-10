#ifndef AVALIACOES_H
#define AVALIACOES_H

#include "UCs.h"
#include "Alunos.h"
#include <cmath>

class Avaliacoes {

    private:
        UCs uc;
        Alunos aluno;
        bool avContinua;
        float efolioA;
        float efolioB;
        float pfolio;
        int exame;
        int notaFinal;
        bool aprovacao;

    public:
        Avaliacoes() {};
        Avaliacoes(bool b);
        ~Avaliacoes() {};

        string get_nome_uc() { return uc.get_nome(); };
        int get_codigo_uc() { return uc.get_codigo(); };
        int get_ects_uc() { return uc.get_ects(); };
        int get_num_aluno() { return aluno.get_num(); };
        bool get_avContinua() { return avContinua; };
        float get_efolioA() { return efolioA; };
        float get_efolioB() { return efolioB; };
        float get_pfolio() { return pfolio; };
        int get_exame() { return exame; };
        int get_notaFinal() { return notaFinal; };
        bool get_aprovacao() { return aprovacao; };

        void update_avaliacao(UCs nova_uc, Alunos novo_aluno, bool nova_avContinua, float novo_efolioA, float novo_efolioB, float novo_pfolio, int novo_exame, int nova_notaFinal, int nova_aprovacao);
        void update_avaliacao(UCs nova_uc, Alunos novo_aluno);
        void update_avaliacao(bool nova_avContinua);
        void update_avaliacao(float novo_efolioA, float novo_efolioB, float novo_pfolio);
        void update_avaliacao(int novo_exame);
        void update_avaliacao();

        void print_obj_data();
        void save_avaliacao();
        void delete_avaliacao(string eraseLine);
        string get_file_line();
};

#endif /* AVALIACOES_H */