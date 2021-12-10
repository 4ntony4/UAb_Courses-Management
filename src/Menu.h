#ifndef MENU_H
#define MENU_H

#include "Curso.h"
#include <sstream>

#define CLEAR "@cls||clear"
#define LEI "LEI"

/* larguras para impressão de dados */
#define NOME_AL_W 20
#define NUM_AL_W 10
#define NOME_UC_W 46
#define COD_UC_W 8
#define ANO_UC_W 5
#define SEM_UC_W 5
#define ECTS_UC_W 6
#define NOTA_FINAL_W 7

using namespace std;

class Menu {

    private:
        string nome_curso;
        int opcao;
        const int n_opcoes = 9; 
        const int n_menu_lines = 14;
        const string menu_name = " MENU ";
        const int menu_line_length = 34;
        const string margin_fill = "/";
        const string body_fill = " ";
        const string border_fill = " ";
        const int left_border_length = 3;
        const string a3_r = ">>> ";  // 3 arrows to the right
        const string a3_l = " <<<";  // 3 arrows to the left
    
    public:
        Menu() {};
        Menu(string novo_nome_curso);
        ~Menu();

        int get_opcao(int n_opcoes);
        
        void para_continuar();
        void print_menu(Curso curso);
        void print_centered_title(string title, int full_length);
        void print_menu_limits(string s);
        void print_one_line(string s);
        void print_all_lines();
};

int charCount(string s);
int get_a_number();
float get_a_float();
char get_a_sn_char();
string get_a_string();
void print_spaces(int n);
void print_dashes(int n);

#endif /* MENU_H */