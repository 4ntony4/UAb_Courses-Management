#include "Menu.h"

using namespace std;

Menu::Menu(string novo_nome_curso) {
    nome_curso = novo_nome_curso;
    Curso curso(nome_curso);

    do {
        print_menu(curso);
        opcao = get_opcao(n_opcoes);

        switch (opcao) {
            case 1:
                curso.listarAlunos();
                para_continuar();
                break;
            
            case 2:
                curso.inserirAluno();
                para_continuar();
                break;

            case 3:
                curso.consultarAluno();
                para_continuar();
                break;

            case 4:
                curso.listarUCs();
                para_continuar();
                break;

            case 5:
                curso.inserirUC();
                para_continuar();
                break;

            case 6:
                curso.consultarUC();
                para_continuar();
                break;

            case 7:
                curso.inserirAvaliacao();
                para_continuar();
                break;

            case 8:
                curso.consultarAvaliacao();
                para_continuar();
                break;
            
            case 0:
                break;
            
            default:
                para_continuar();
                break;
            }
    }
    while ( opcao != 0 );
}

Menu::~Menu() {
    cout << "Obrigado!" << endl;
}

int Menu::get_opcao(int n_opcoes) {
    int nova_opcao;
    stringstream ss;
    string input = "";

    ss.clear();
    ss.str("");

    cout << "\t\tOpção: ";
    
    while (true) {
        if ( !getline(cin, input) ) {
            return -1;
        }

        ss.str(input);

        if (ss >> nova_opcao && nova_opcao >= 0 && nova_opcao < n_opcoes) {
            break;
        }

        cout << "Opção inválida, tente novamente" << endl;
        cout << "\t\tOpção: ";

        ss.clear();
        ss.str("");
        input.clear();
    }

    return nova_opcao;
}

void Menu::para_continuar() {
    string input = "";

    cout << "Prima ENTER para continuar... ";

    getline(cin, input);
}

void Menu::print_menu(Curso curso) {
    string cabecalho = a3_r + nome_curso + a3_l;

    system(CLEAR);
    print_centered_title(cabecalho, menu_line_length);
    print_menu_limits(menu_name);
    print_all_lines();
    print_menu_limits("");
    cout << endl;
}

void Menu::print_centered_title(string title, int full_length) {
    int i, empty_space = full_length - charCount(title);

    if ( empty_space > 0 ) {
        for (i = 0; i < empty_space / 2; i++) {
            cout << " ";
        }
        cout << title;
        for (i = empty_space / 2; i < full_length; i++) {
            cout << " ";
        }
    }
    else {
        cout << title;
    }

    cout << endl << endl;
}

void Menu::print_menu_limits(string s) {
    int i, left_over = menu_line_length - charCount(s);

    for (i = 0; i < left_over / 2; i++) {
        cout << margin_fill;
    }
    cout << s;
    for (i = 0; i < left_over / 2; i++) {
        cout << margin_fill;
    }
    cout << endl;
}

void Menu::print_one_line(string s) {
    int i;
    int left_over = menu_line_length
                    - charCount(margin_fill) * 2
                    - charCount(border_fill) * left_border_length
                    - charCount(s);
    
    cout << margin_fill;
    for (i = 0; i < left_border_length; i++) {
        cout << border_fill;
    }
    cout << s;
    if ( left_over >= 0 ) {
        for (i = 0; i < left_over; i++) {
            cout << body_fill;
        }
        cout << margin_fill << endl;
    }
    else {
        cout << endl;
    }
}

void Menu::print_all_lines() {
    for (int i = 0; i < n_menu_lines; i++) {
        switch (i) {
            case 1:
                print_one_line("1 - Listar Alunos");
                break;
            
            case 2:
                print_one_line("2 - Inserir Novo Aluno");
                break;

            case 3:
                print_one_line("3 - Consultar Aluno");
                break;

            case 5:
                print_one_line("4 - Listar UCs");
                break;

            case 6:
                print_one_line("5 - Inserir Nova UC");
                break;

            case 7:
                print_one_line("6 - Consultar UC");
                break;
            
            case 9:
                print_one_line("7 - Inserir Nova Avaliação");
                break;

            case 10:
                print_one_line("8 - Consultar Avaliação");
                break;

            case 12:
                print_one_line("0 - Sair");
                break;
            
            default:
                print_one_line("");
                break;
        }
    }
}

int charCount(string s) {
    /* contar número de carateres de uma string */

    int strLen = s.length();
    int u = 0;
    const char *c_str = s.c_str();
    int charCount = 0;
    
    while(u < strLen) {
        u += mblen(&c_str[u], strLen - u);
        charCount += 1;
    }
    
    return charCount;
}

int get_a_number() {
    int num = 0;
    stringstream ss;
    string input = "";

    ss.clear();
    ss.str("");

    while (true) {
        if ( !getline(cin, input) ) {
            return -1;
        }
        
        ss.str(input);

        if (ss >> num) {
            break;
        }

        cout << "Número inválido, tente novamente" << endl;

        ss.clear();
        ss.str("");
        input.clear();
    }

    return num;
}

float get_a_float() {
    float num = 0;
    stringstream ss;
    string input = "";

    ss.clear();
    ss.str("");

    while (true) {
        if ( !getline(cin, input) ) {
            return -1;
        }
        
        ss.str(input);

        if (ss >> num) {
            break;
        }

        cout << "Número inválido, tente novamente" << endl;

        ss.clear();
        ss.str("");
        input.clear();
    }

    return num;
}

char get_a_sn_char() {
    char c = {0};
    string input = "";

    while (true) {
        getline(cin, input);
        if ( input.length() == 1 &&
          (input[0] == 'S' ||
          input[0] == 's' ||
          input[0] == 'N' ||
          input[0] == 'n') ) {
            c = input[0];
            break;
        }
        cout << "Carater inválido, tente novamente" << endl;
    }

    return c;
}

string get_a_string() {
    string input = "";
    
    getline(cin, input);

    return input;
}

void print_spaces(int n) {
    for (int i = 0; i < n; i++) {
        cout << " ";
    }
}

void print_dashes(int n) {
    for (int i = 0; i < n; i++) {
        cout << "-";
    }
}