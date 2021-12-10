#include "Curso.h"
#include "Menu.h"

using namespace std;

Curso::Curso(string nome_curso) {
    if (nome_curso == LEI) {
        Vucs = dados_UCs();
        Valunos = dados_Alunos();
        Vavaliacoes = dados_Avaliacoes();
    }
}

vector<Alunos> Curso::dados_Alunos() {
    /* funcao que carrega para um vetor os dados dos Alunos 
    a partir de um ficheiro */
    vector<Alunos> v_alunos;
    Alunos novo_aluno(0);
    
    ifstream MyFile("data/dados_alunos.txt");
    
    string buffer, chunk;
    
    string novo_nome;
    int novo_num; 
    
    char delimiter = ';';
    int delim_count = 0;

    /* ler uma linha do ficheiro */
    while (getline(MyFile, buffer)) {

        stringstream line(buffer);

        /* ler uma parte da linha até ao próximo delimitador
         ou até ao fim da linha */       
        while (getline(line, chunk, delimiter)) {

            /* existe 1 delimitador por linha */
            if (delim_count == 2) {
                delim_count = 0;
            }

            switch (delim_count) {
                case 0:
                    novo_nome = chunk;
                    break;

                case 1:
                    stringstream(chunk) >> novo_num;
                    break;
                
                default:
                    break;
            }
            delim_count++;
        }
        
        novo_aluno.update_aluno(novo_nome, novo_num);
        v_alunos.push_back(novo_aluno);
    }

    MyFile.close();
    return v_alunos;
}

vector<UCs> Curso::dados_UCs() {
    /* funcao que carrega para um vetor os dados das UCs 
    a partir de um ficheiro */
    vector<UCs> v_ucs;
    UCs nova_uc(0);

    ifstream MyFile("data/dados_ucs.txt");
    
    string buffer, chunk;
    
    string novo_nome;
    int novo_codigo, novo_ano, novo_sem, novo_ects; 
    
    char delimiter = ';';
    int delim_count=0;
  
    /* ler uma linha do ficheiro */
    while (getline(MyFile, buffer)) {

        stringstream line(buffer);
        
        /* ler uma parte da linha até ao próximo delimitador 
        ou até ao fim da linha */
        while (getline(line, chunk, delimiter)) {

            /* existem 4 delimitadores por linha */
            if (delim_count == 5) {
                delim_count = 0;
            }

            switch (delim_count) {
                case 0:
                    novo_nome = chunk;
                    break;

                case 1:
                    stringstream(chunk) >> novo_codigo;
                    break;
                
                case 2:
                    stringstream(chunk) >> novo_ano;
                    break;
                
                case 3:
                    stringstream(chunk) >> novo_sem;
                    break;
                
                case 4:
                    stringstream(chunk) >> novo_ects;
                    break;
            
                default:
                    break;
            }
            delim_count++;
        }
        
        nova_uc.update_uc(novo_nome, novo_codigo, novo_ano, novo_sem, novo_ects);
        v_ucs.push_back(nova_uc);
    }

    MyFile.close();
    return v_ucs;
}

vector<Avaliacoes> Curso::dados_Avaliacoes() {
    /* funcao que carrega para um vetor os dados das Avaliacoes
     a partir de um ficheiro */
    vector<Avaliacoes> v_avaliacoes;
    Alunos aluno(0);
    UCs uc(0);
    Avaliacoes nova_avaliacao(0);

    ifstream MyFile("data/dados_avaliacoes.txt");
    
    string buffer, chunk;
    
    int novo_num, novo_codigo;
    bool nova_avContinua, nova_aprovacao;
    float novo_efolioA, novo_efolioB, novo_pfolio;
    int novo_exame, nova_notaFinal;

    char delimiter = ';';
    int delim_count = 0;

    /* ler uma linha do ficheiro */
    while (getline(MyFile, buffer)) {
        
        stringstream line(buffer);

        /* ler uma parte da linha até ao próximo delimitador
         ou até ao fim da linha */
        while (getline(line, chunk, delimiter)) {

            /* existem 8 delimitadores por linha */
            if (delim_count == 9) {
                delim_count = 0;
            }

            switch (delim_count) {
                case 0:
                    stringstream(chunk) >> novo_num;
                    break;

                case 1:
                    stringstream(chunk) >> novo_codigo;
                    break;
                
                case 2:
                    istringstream(chunk) >> nova_avContinua;
                    break;
                
                case 3:
                    stringstream(chunk) >> novo_efolioA;
                    break;

                case 4:
                    stringstream(chunk) >> novo_efolioB;
                    break;
                
                case 5:
                    stringstream(chunk) >> novo_pfolio;
                    break;

                case 6:
                    stringstream(chunk) >> novo_exame;
                    break;

                case 7:
                    stringstream(chunk) >> nova_notaFinal;
                    break;

                case 8:
                    istringstream(chunk) >> nova_aprovacao;
                    break;

                default:
                    break;
            }
            delim_count++;
        }

        uc = encontrarUC(novo_codigo);
        aluno = encontrarAluno(novo_num);

        if (uc.get_codigo() != 0 && aluno.get_num() != 0) {
            nova_avaliacao.update_avaliacao(uc, aluno, nova_avContinua, novo_efolioA, novo_efolioB, novo_pfolio, novo_exame, nova_notaFinal, nova_aprovacao);
            v_avaliacoes.push_back(nova_avaliacao);
        }
    }

    MyFile.close();
    return v_avaliacoes;
}

Alunos Curso::encontrarAluno(int num) {
    /* procurar um Aluno a partir de um dado número de aluno */
    Alunos aluno(0);

    for (it_a = Valunos.begin(); it_a < Valunos.end(); it_a++) {
        if ( (*it_a).get_num() == num ) {
            aluno.update_aluno(
                (*it_a).get_nome(),
                (*it_a).get_num()
            );
            break;
        }
    }

    return aluno;
}

UCs Curso::encontrarUC(int cod) {
    /* procurar uma UC a partir de um dado código de UC */
    UCs uc(0);

    for (it_u = Vucs.begin(); it_u < Vucs.end(); it_u++) {
        if ( (*it_u).get_codigo() == cod ) {
            uc.update_uc(
                (*it_u).get_nome(),
                cod,
                (*it_u).get_ano(),
                (*it_u).get_sem(),
                (*it_u).get_ects()
            );
            break;
        }
    }

    return uc;
}

Avaliacoes Curso::encontrarAvaliacao() {
    int num, cod;

    bool aluno_found = false, uc_found = false;

    Alunos aluno(0);
    UCs uc(0);
    Avaliacoes avaliacao(0);

    cout << "Insira o número de aluno: ";
    num = get_a_number();

    /* verificar se o aluno existe */
    aluno = encontrarAluno(num);
    if (aluno.get_num() != 0) {
        aluno_found = true;
    }

    if (!aluno_found) {
        cout << "O aluno não foi encontrado." << endl;
        return avaliacao;
    }

    cout << "Insira o código da UC: ";
    cod = get_a_number();

    /* verificar se a UC existe */
    uc = encontrarUC(cod);
    if (uc.get_codigo() != 0) {
        uc_found = true;
    }

    if (!uc_found) {
        cout << "A UC não foi encontrada." << endl;
        return avaliacao;
    }

    /* procurar avaliação para o par Aluno + UC */
    for (it_av = Vavaliacoes.begin(); it_av < Vavaliacoes.end(); it_av++) {
        if ( (*it_av).get_num_aluno() == num && (*it_av).get_codigo_uc() == cod) {
            avaliacao = (*it_av);
            break;
        }
    }

    return avaliacao;
}

void Curso::listarAlunos() {
    int tamanhoLinha = NOME_AL_W + NUM_AL_W;

    cout << endl << "Lista de Alunos:" << endl;

    print_dashes(tamanhoLinha);
    cout << endl;

    print_spaces( NOME_AL_W - charCount("Nome") );
    cout << "Nome";

    print_spaces( NUM_AL_W - charCount("Número") );
    cout << "Número" << endl;

    print_dashes(tamanhoLinha);
    cout << endl;

    for (it_a = Valunos.begin(); it_a < Valunos.end(); it_a++) {
        
        print_spaces( NOME_AL_W - charCount((*it_a).get_nome()) );
        cout << (*it_a).get_nome();

        print_spaces( NUM_AL_W - charCount(to_string((*it_a).get_num())) );
        cout << (*it_a).get_num();

        cout << endl;
    }

    print_dashes(tamanhoLinha);
    cout << endl << endl;
}

void Curso::listarUCs() {
    int tamanhoLinha = NOME_UC_W + COD_UC_W + ANO_UC_W + SEM_UC_W + ECTS_UC_W;

    cout << endl << "Lista de UCs:" << endl;

    print_dashes(tamanhoLinha);
    cout << endl;

    print_spaces( NOME_UC_W - charCount("UC") );
    cout << "UC";

    print_spaces( COD_UC_W - charCount("Código") );
    cout << "Código";

    print_spaces( ANO_UC_W - charCount("Ano") );
    cout << "Ano";

    print_spaces( SEM_UC_W - charCount("Sem") );
    cout << "Sem";

    print_spaces( ECTS_UC_W - charCount("ECTS") );
    cout << "ECTS" << endl;

    print_dashes(tamanhoLinha);
    cout << endl;

    for (it_u = Vucs.begin(); it_u < Vucs.end(); it_u++) {
        
        print_spaces( NOME_UC_W - charCount((*it_u).get_nome()) );
        cout << (*it_u).get_nome();

        print_spaces( COD_UC_W - charCount(to_string((*it_u).get_codigo())) );
        cout << (*it_u).get_codigo();

        print_spaces( ANO_UC_W - charCount(to_string((*it_u).get_ano())) );
        cout << (*it_u).get_ano();

        print_spaces( SEM_UC_W - charCount(to_string((*it_u).get_sem())) );
        cout << (*it_u).get_sem();

        print_spaces( ECTS_UC_W - charCount(to_string((*it_u).get_ects())) );
        cout << (*it_u).get_ects();

        cout << endl;
    }

    print_dashes(tamanhoLinha);
    cout << endl << endl;
}

void Curso::consultarAluno() {
    /* procurar um aluno a partir de um número de aluno dado pelo utilizador,
     calcular o número de ucs e ects onde houve aprovação bem como a média
      atual do aluno */
    int num;
    bool found = false;
    Alunos aluno(0);
    int count_ucs_aprovadas = 0;
    int count_ects_aprovados = 0;
    int sum_ects_x_nota = 0;
    float media = 0;
    int default_precision = cout.precision();
    int tamanhoLinha = NOME_UC_W + ECTS_UC_W + NOTA_FINAL_W;

    cout << "Insira o número de aluno: ";
    num = get_a_number();

    aluno = encontrarAluno(num);
    if (aluno.get_num() != 0) {
        found = true;
    }

    if (found) {
        cout << endl << "Aluno: " << aluno.get_nome() << endl;
        cout << "Unidades curriculares onde obteve aprovação:" << endl;

        print_dashes(tamanhoLinha);
        cout << endl;
        
        print_spaces( NOME_UC_W - charCount("UC") );
        cout << "UC";

        print_spaces( ECTS_UC_W - charCount("ECTS") );
        cout << "ECTS";
        
        print_spaces( NOTA_FINAL_W - charCount("Nota") );
        cout << "Nota" << endl;

        print_dashes(tamanhoLinha);
        cout << endl;

        for (it_av = Vavaliacoes.begin(); it_av < Vavaliacoes.end(); it_av++) {
            if ( (*it_av).get_num_aluno() == num && (*it_av).get_aprovacao() == true ) {

                print_spaces( NOME_UC_W - charCount((*it_av).get_nome_uc()) );
                cout << (*it_av).get_nome_uc();

                print_spaces( ECTS_UC_W - charCount(to_string((*it_av).get_ects_uc())) );
                cout << (*it_av).get_ects_uc();

                print_spaces( NOTA_FINAL_W - charCount(to_string((*it_av).get_notaFinal())) );
                cout << (*it_av).get_notaFinal();

                cout << endl;

                count_ucs_aprovadas++;
                count_ects_aprovados+=(*it_av).get_ects_uc();
                sum_ects_x_nota+=(*it_av).get_ects_uc()*(*it_av).get_notaFinal();
            }
        }

        print_dashes(tamanhoLinha);
        cout << endl;

        cout << "Total de UCs: " << count_ucs_aprovadas << endl;
        cout << "Total de ECTS: " << count_ects_aprovados << endl;

        /* evitar divisão por zero */
        if ( count_ects_aprovados != 0 ) {
            media = (float)sum_ects_x_nota/(float)count_ects_aprovados;
        }

        /* definir precisão para 3 casas decimais */
        cout.setf(ios::fixed);
        cout.precision(3);

        cout << "Média: " << media << endl << endl;

        /* restaurar precisão default */
        cout.unsetf(ios::fixed);
        cout.precision(default_precision);

        if (count_ects_aprovados == 180) {
            cout << "Parabéns! Concluiu a LEI!" << endl;
        }
    }
    else {
        cout << endl << "Aluno não encontrado." << endl << endl;
    }
}

void Curso::consultarUC() {
    /* procurar uma UC a partir de um código de UC dado pelo utilizador
     e calcular o total de aprovações bem como a média das aprovações */
    int cod;
    bool found = false;
    UCs uc(0);
    int count_aprovacoes = 0, sum_notas = 0;
    float media = 0;
    int default_precision = cout.precision();
    int tamanhoLinha;
    string title = "Unidade Curricular: ";

    cout << "Insira o código da UC: ";
    cod = get_a_number();

    uc = encontrarUC(cod);
    if (uc.get_codigo() != 0) {
        found = true;
    }

    if (found) {
        tamanhoLinha = charCount(uc.get_nome()) + charCount(title);

        for (it_av = Vavaliacoes.begin(); it_av < Vavaliacoes.end(); it_av++) {
            if ( (*it_av).get_codigo_uc() == cod && (*it_av).get_aprovacao() == true ) {
                count_aprovacoes++;
                sum_notas+=(*it_av).get_notaFinal();
            }
        }

        print_dashes(tamanhoLinha);
        cout << endl;

        cout << title << uc.get_nome() << endl;
        cout << "Total de alunos aprovados: " << count_aprovacoes << endl;
        
        /* evitar divisão por zero */
        if (count_aprovacoes != 0 ) {
            media = (float)sum_notas/(float)count_aprovacoes;
        }

        /* definir precisão para 3 casas decimais */
        cout.setf(ios::fixed);
        cout.precision(3);
    
        cout << "Média: " << media << endl;

        /* restaurar precisão default */
        cout.unsetf(ios::fixed);
        cout.precision(default_precision);

        print_dashes(tamanhoLinha);
        cout << endl;
    }
    else {
        cout << endl << "UC não encontrada." << endl << endl;
    }
}

void Curso::consultarAvaliacao() {
    Avaliacoes avaliacao(0);

    avaliacao = encontrarAvaliacao();

    if ( !avaliacao.get_num_aluno() ) {
        cout << "Avaliação não encontrada." << endl << endl;
    }
    else {
        avaliacao.print_obj_data();
    }    
}

void Curso::inserirAluno() {
    int novo_num;
    string novo_nome;
    bool found = false;
    Alunos aluno(0);

    cout << "Insira o novo número de aluno: ";
    novo_num = get_a_number();

    /* verificar se o Aluno existe */
    aluno = encontrarAluno(novo_num);
    if (aluno.get_num() != 0) {
        found = true;
    }

    if (found) {
        cout << "Este número de aluno já existe." << endl;
    }
    else if (novo_num <= 0) {
        cout << "Número inválido." << endl;
    }
    else {
        cout << "Insira o novo nome do aluno: ";
        novo_nome = get_a_string();

        aluno.update_aluno(novo_nome, novo_num);
        Valunos.push_back(aluno);
        aluno.save_aluno();

        cout << "Aluno inserido com sucesso." << endl;
        aluno.print_obj_data();
    }
}

void Curso::inserirUC() {
    int novo_codigo, novo_ano, novo_sem, novo_ects;
    string novo_nome;
    bool found = false;
    UCs uc(0);

    cout << "Insira o novo código da UC: ";
    novo_codigo = get_a_number();

    /* verificar se a UC existe */
    uc = encontrarUC(novo_codigo);
    if (uc.get_codigo() != 0) {
        found = true;
    }

    if (found) {
        cout << "Este código de UC já existe." << endl;
    }
    else if (novo_codigo <= 0) {
        cout << "Código inválido." << endl;
    }
    else {
        cout << "Insira o novo nome da UC: ";
        novo_nome = get_a_string();

        cout << "Insira o ano da UC: ";
        novo_ano = get_a_number();

        cout << "Insira o semestre da UC: ";
        novo_sem = get_a_number();

        cout << "Insira o número de ECTS da UC: ";
        novo_ects = get_a_number();

        uc.update_uc(novo_nome, novo_codigo, novo_ano, novo_sem, novo_ects);
        Vucs.push_back(uc);
        uc.save_uc();

        cout << "UC inserida com sucesso." << endl;
        uc.print_obj_data();
    }    
}

bool Curso::inserirAvaliacao() {
    int num, cod;

    bool aluno_found = false, uc_found = false, avaliacao_found = false;
    
    Alunos aluno(0);
    UCs uc(0);
    Avaliacoes avaliacao(0), avaliacao_melhoria(0);

    char opcao;
    float novo_efolioA = -1;
    float novo_efolioB = -1;
    float novo_pfolio = -1;
    int novo_exame = -1;

    cout << "Insira o número de aluno: ";
    num = get_a_number();

    /* verificar se o Aluno existe */
    aluno = encontrarAluno(num);
    if (aluno.get_num() != 0) {
        aluno_found = true;
    }

    if (!aluno_found) {
        cout << "O aluno não foi encontrado." << endl;
        return false;
    }

    cout << "Insira o código da UC: ";
    cod = get_a_number();

    /* verificar se a UC existe */
    uc = encontrarUC(cod);
    if (uc.get_codigo() != 0) {
        uc_found = true;
    }

    if (!uc_found) {
        cout << "A UC não foi encontrada." << endl;
        return false;
    }

    /* verificar se já existe alguma avaliação
     para o par Aluno + UC */
    for (it_av = Vavaliacoes.begin(); it_av < Vavaliacoes.end(); it_av++) {
        if ( (*it_av).get_num_aluno() == num && (*it_av).get_codigo_uc() == cod) {
            avaliacao_found = true;
            it_wanted = it_av;
            break;
        }
    }

    /* para uma avaliação nova */
    if (!avaliacao_found) {
        avaliacao.update_avaliacao(uc, aluno);

        cout << "Avaliação Contínua? (s/n): ";
        opcao = get_a_sn_char();

        /* Foi escolhida Avaliação Contínua */
        if ( opcao == 'S' || opcao == 's' ) {
            
            /* atualizar tipo de avaliação */
            avaliacao.update_avaliacao(true);

            cout << "Insira a nota do e-Fólio A: ";
            novo_efolioA = get_a_float();
            
            cout << "Insira a nota do e-Fólio B: ";
            novo_efolioB = get_a_float();

            if ( novo_efolioA + novo_efolioB > 8 ) {
                cout << "Algo correu mal. A soma dos e-Fólios não pode ultrapassar 8 valores." << endl;
                return false;
            }
            else if ( novo_efolioA + novo_efolioB < 3.5 ) {
                cout << "Não tem nota suficiente para ir a p-Fólio. Terá de fazer exame." << endl;
            }
            else {
                cout << "Insira a nota do p-Fólio: ";
                novo_pfolio = get_a_float();

                if ( novo_pfolio < 0 || novo_pfolio > 12 ) {
                    cout << "Algo correu mal. A nota do p-Fólio deve estar compreendida entre 0 e 12 valores." << endl;
                    return false;
                }
            }

            /* atualizar notas de avaliação contínua */
            avaliacao.update_avaliacao(novo_efolioA, novo_efolioB, novo_pfolio);

            /* calcular nota final e estado de aprovação */
            avaliacao.update_avaliacao();
        }
        /* Foi escolhido Exame Final */
        else {

            /* atualizar tipo de avaliação */
            avaliacao.update_avaliacao(false);

            cout << "Insira a nota do Exame: ";
            novo_exame = get_a_number();

            if ( novo_exame < 0 || novo_exame > 20) {
                cout << "Algo correu mal. A nota do Exame deve estar compreendida entre 0 e 20 valores." << endl;
                return false;
            }

            /* atualizar nota de exame */
            avaliacao.update_avaliacao(novo_exame);

            /* calcular nota final e estado de aprovação */
            avaliacao.update_avaliacao();
        }

        Vavaliacoes.push_back(avaliacao);
        avaliacao.save_avaliacao();

        cout << "Avaliação inserida com sucesso." << endl;
        avaliacao.print_obj_data();

        return true;
    }
    /* para uma avaliação existente */
    else {
        /* O aluno já foi aprovado */
        if ( (*it_wanted).get_aprovacao() ) {

            /* O aluno já tem nota máxima */
            if ( (*it_wanted).get_notaFinal() == 20 ) {
                cout << "O aluno já foi aprovado com 20 valores. Não há melhoria possível!" << endl;
                return true;
            }

            cout << "O aluno já foi aprovado com " << (*it_wanted).get_notaFinal() << " valores." << endl;

            /* Melhoria de Nota */
            cout << "Inserir melhoria de nota? (s/n): ";
            opcao = get_a_sn_char();

            /* Foi escolhida Melhoria */
            if ( opcao == 'S' || opcao == 's' ) {

                avaliacao_melhoria = (*it_wanted);

                cout << "Avaliação Contínua? (s/n): ";
                opcao = get_a_sn_char();

                /* Foi escolhida Avaliação Contínua */
                if ( opcao == 'S' || opcao == 's' ) {

                    /* atualizar tipo de avaliação */
                    avaliacao_melhoria.update_avaliacao(true);

                    cout << "Insira a nota do e-Fólio A: ";
                    novo_efolioA = get_a_float();
                    
                    cout << "Insira a nota do e-Fólio B: ";
                    novo_efolioB = get_a_float();

                    if ( novo_efolioA + novo_efolioB > 8 ) {
                        cout << "Algo correu mal. A soma dos e-Fólios não pode ultrapassar 8 valores." << endl;
                        return false;
                    }
                    else if ( novo_efolioA + novo_efolioB < 3.5 ) {
                        cout << "Não tem nota suficiente para ir a p-Fólio. Terá de fazer exame." << endl;

                        /* atualizar notas de avaliação contínua */
                        avaliacao_melhoria.update_avaliacao(novo_efolioA, novo_efolioB, -1);
                    }
                    else {
                        cout << "Insira a nota do p-Fólio: ";
                        novo_pfolio = get_a_float();

                        if ( novo_pfolio < 0 || novo_pfolio > 12 ) {
                            cout << "Algo correu mal. A nota do p-Fólio deve estar compreendida entre 0 e 12 valores." << endl;
                            return false;
                        }

                        /* atualizar notas de avaliação contínua */
                        avaliacao_melhoria.update_avaliacao(novo_efolioA, novo_efolioB, novo_pfolio);
                    }

                    /* garantir que a nota de algum exame anterior é apagada */
                    avaliacao_melhoria.update_avaliacao(-1);

                    /* calcular nota final e estado de aprovação */
                    avaliacao_melhoria.update_avaliacao();

                }
                /* Foi escolhido Exame Final */
                else {

                    /* atualizar tipo de avaliação */
                    avaliacao_melhoria.update_avaliacao(false);

                    /* garantir que as notas de avaliação contínua
                     anteriores são apagadas */
                    avaliacao_melhoria.update_avaliacao(-1, -1, -1);

                    cout << "Insira a nota do Exame: ";
                    novo_exame = get_a_number();

                    if ( novo_exame < 0 || novo_exame > 20) {
                        cout << "Algo correu mal. A nota do Exame deve estar compreendida entre 0 e 20 valores." << endl;
                        return false;
                    }

                    /* atualizar nota de exame */
                    avaliacao_melhoria.update_avaliacao(novo_exame);

                    /* calcular nota final e estado de aprovação */
                    avaliacao_melhoria.update_avaliacao();
                }

                /* Houve Melhoria */
                if ( avaliacao_melhoria.get_notaFinal() > (*it_wanted).get_notaFinal() ) {

                    /* apagar avaliação anterior no respetivo ficheiro */
                    (*it_wanted).delete_avaliacao((*it_wanted).get_file_line());

                    /* substituir avaliação no vetor Vavaliacoes */
                    (*it_wanted) = avaliacao_melhoria;

                    /* gravar nova avaliação no respetivo ficheiro */
                    (*it_wanted).save_avaliacao();
                    
                    cout << "Melhoria inserida com sucesso!" << endl;

                    (*it_wanted).print_obj_data();

                    return true;
                }
                /* Não houve Melhoria */
                else {
                    cout << "Nao houve melhoria. Nota anterior mantida." << endl;
                    (*it_wanted).print_obj_data();

                    return true;
                }
            }

            /* Não foi escolhida Melhoria */
            else {
                cout << "Não é possível inserir uma nova avaliação previamente aprovada que não seja uma melhoria de nota." << endl;

                return false;
            }
        }
        /* O aluno ainda não foi aprovado */
        else {
            avaliacao.update_avaliacao(uc, aluno);

            cout << "Já existe avaliação, mas o aluno ainda não foi aprovado." << endl;

            cout << "Avaliação Contínua? (s/n): ";
            opcao = get_a_sn_char();

            /* Foi escolhida Avaliação Contínua */
            if ( opcao == 'S' || opcao == 's' ) {

                /* atualizar tipo de avaliação */
                avaliacao.update_avaliacao(true);

                cout << "Insira a nota do e-Fólio A: ";
                novo_efolioA = get_a_float();

                cout << "Insira a nota do e-Fólio B: ";
                novo_efolioB = get_a_float();

                if ( novo_efolioA + novo_efolioB > 8 ) {
                    cout << "Algo correu mal. A soma dos e-Fólios não pode ultrapassar 8 valores." << endl;
                    return false;
                }
                else if ( novo_efolioA + novo_efolioB < 3.5 ) {
                    cout << "Não tem nota suficiente para ir a p-Fólio. Terá de fazer exame." << endl;

                    /* atualizar notas de avaliação contínua */
                    avaliacao.update_avaliacao(novo_efolioA, novo_efolioB, -1);
                }
                else {
                    cout << "Insira a nota do p-Fólio: ";
                    novo_pfolio = get_a_float();

                    if ( novo_pfolio < 0 || novo_pfolio > 12 ) {
                        cout << "Algo correu mal. A nota do p-Fólio deve estar compreendida entre 0 e 12 valores." << endl;
                        return false;
                    }

                    /* atualizar notas de avaliação contínua */
                    avaliacao.update_avaliacao(novo_efolioA, novo_efolioB, novo_pfolio);
                }
            }
            /* Foi escolhido Exame Final */
            else {

                /* atualizar tipo de avaliacao */
                avaliacao.update_avaliacao(false);

                cout << "Insira a nota do Exame: ";
                novo_exame = get_a_number();

                if ( novo_exame < 0 || novo_exame > 20) {
                    cout << "Algo correu mal. A nota do Exame deve estar compreendida entre 0 e 20 valores." << endl;
                    return false;
                }

                /* atualizar nota de exame */
                avaliacao.update_avaliacao(novo_exame);
            }

            /* calcular nota final e estado de aprovação */
            avaliacao.update_avaliacao();

            /* apagar avaliação anterior no respetivo ficheiro */
            (*it_wanted).delete_avaliacao((*it_wanted).get_file_line());

            /* substituir avaliação no vetor Vavaliacoes */
            (*it_wanted) = avaliacao;

            /* gravar nova avaliação no respetivo ficheiro */
            (*it_wanted).save_avaliacao();

            cout << "Avaliação substituída com sucesso!" << endl;

            (*it_wanted).print_obj_data();

            return true;
        }
    }
}