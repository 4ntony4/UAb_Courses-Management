#ifndef UCS_H
#define UCS_H

#include <iostream>
#include <fstream>

using namespace std;

class UCs {

    private:
        string nome;
        int codigo;
        int ano;
        int sem;
        int ects;
    
    public:
        UCs() {};
        UCs(bool b);
        ~UCs() {};

        string get_nome() { return nome; };
        int get_codigo() { return codigo; };
        int get_ano() { return ano; };
        int get_sem() { return sem; };
        int get_ects() { return ects; };
        
        void update_uc(string novo_nome, int novo_codigo, int novo_ano, int novo_sem, int novo_ects);
        void print_obj_data();
        void save_uc();
};

#endif /* UCS_H */