#ifndef ALUNOS_H
#define ALUNOS_H

#include <iostream>
#include <fstream>

using namespace std;

class Alunos {

    private:
        string nome;
        int num;
        
    public:
        Alunos() {};
        Alunos(bool b);
        ~Alunos() {};

        string get_nome() { return nome; };
        int get_num() {return num; };
        
        void update_aluno(string novo_nome, int novo_num);
        void print_obj_data();
        void save_aluno();
};

#endif /* ALUNOS_H */