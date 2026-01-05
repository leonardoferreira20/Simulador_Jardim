//
// Created by Leonardo Ferreira on 11/10/2025.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <map>

#include "Comando.h"
#include "../Solo/Solo.h"
#include "../Interface/Interface.h"
#include "../Jardim/Jardim.h"
#include "../Jardineiro/Jardineiro.h"
#include "../Planta/Planta.h"
#include "../Ferramenta/Adubo/Adubo.h"
#include "../Ferramenta/Tesoura/Tesoura.h"
#include "../Ferramenta/Regador/Regador.h"
#include "../Ferramenta/VaraEspecial/VaraEspecial.h"

using namespace std;
static std::map<std::string, Jardim*> lista_gravacoes;

/// CRIAR JARDIM
Jardim* Comando::comandoJardim(istringstream& iss, ostream& out){
    int lin, col;

    if (!(iss >> lin >> col)) {
        out << "Uso: jardim <linhas> <colunas>\n" << endl;
        return nullptr;
    }

    if ((lin <= 0 || lin >= 27) || (col <= 0 || col >= 27)) {
        out << "Uso: jardim <linhas> <colunas>\n" << endl;
        return nullptr;
    }

    Jardim* jardim = new Jardim(lin, col);

    out << "Jardim criado com " << lin << " linhas e " << col << " colunas.\n";

    out << jardim->imprimir();
    return jardim;
};

/// AVANÇAR NO TEMPO
void Comando::comandoAvanca(Jardim* jardim, istringstream& iss, ostream& out){
    if ( jardim == nullptr ){
        out << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    int n = 1;
    iss >> n;
    for (int i = 0; i < n;i++) {
        jardim->avanca(cout);
        jardim->getJardineiro().resetContadores();
    }

    out << jardim->imprimir();
};

/// LISTAR INFORMAÇaO SOBRE PLANTAS
void Comando::comandoListarPlantas(Jardim* jardim, ostream& out) {
    if (jardim == nullptr) {
        out << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    out << jardim->listarPlantas();
    out << jardim->imprimir();
    out << endl;
}

void Comando::comandoListarPlanta(Jardim* jardim, istringstream& iss, ostream& out) {
    string coords;
    int lin, col;

    if ( jardim == nullptr ) {
        out << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    if ( !(iss >> coords) ) {
        out << "Uso: lplanta <AA>\n" << endl;
        return;
    }

    if ( !converteCoordenada(coords, lin, col) ) {
        out << "Erro: Coordenadas invalidas.\n" << endl;
        return;
    }

    if ( !jardim->posicaoValida(lin, col) ) {
        out << "Erro: Posicao fora dos limites.\n" << endl;
        return;
    }

    out << jardim->listarPlanta(lin, col);
    out << jardim->imprimir();
}

/// LISTAR INFORMAÇaO SOBRE O SOLO
void Comando::comandoListarInfoSolo(Jardim* jardim, istringstream& iss, ostream& out) {
    string coords;
    int lin, col;
    int raio = 1;              // por defeito mostra vizinhos imediatos
    bool temRaio = false;

    if (jardim == nullptr) {
        out << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    if (!(iss >> coords)) {
        out << "Uso: lsolo <AA> [n]\n" << endl;
        return;
    }

    if (!converteCoordenada(coords, lin, col)) {
        out << "Erro: Coordenadas inválidas.\n" << endl;
        return;
    }

    if (iss >> raio) {         // opcional
        temRaio = true;
        if (raio < 1) raio = 1;
    } else {
        // se não foi fornecido n, mantém raio = 1 (vizinhos imediatos)
        temRaio = false;
    }

    if (!jardim->posicaoValida(lin, col)) {
        out << "Erro: Posição fora dos limites.\n" << endl;
        return;
    }

    Solo* solo = jardim->getSolo(lin, col);
    if (solo == nullptr) {
        out << "Erro inesperado: solo inexistente.\n" << endl;
        return;
    }

    // Solo principal
    out << "Solo " << char('A' + lin) << char('A' + col) << ":\n";
    out << solo->imprimirDetalhado();

    //Vizinhos
    out << "\nVizinhos (raio " << raio << "):\n";

    for (int dl = -raio; dl <= raio; dl++) {
        for (int dc = -raio; dc <= raio; dc++) {

            if (dl == 0 && dc == 0) continue;

            int nl = lin + dl;
            int nc = col + dc;

            if (!jardim->posicaoValida(nl, nc))
                continue;

            out << " - " << char('A' + nl) << char('A' + nc) << ": ";
            out << jardim->getSolo(nl, nc)->imprimirDetalhado();
        }
    }

    out << endl;
    out << jardim->imprimir();
}

void Comando::comandoListarArea(Jardim* jardim, ostream& out) {
    if (jardim == nullptr) {
        out << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    bool encontrou = false;

    for (int l = 0; l <  jardim->getNumLinhas(); ++l) {
        for (int c = 0; c < jardim->getNumColunas(); ++c) {
            Solo* solo = jardim->getSolo(l, c);
            if (solo != nullptr) {
                if ( solo->temPlanta() ) {
                    Planta* p = solo->obterPlanta();
                    out << "  (" << char('A' + l) << "," << char('A' + c) << ") - Planta: " << p->getNome() << "\n";
                    encontrou = true;
                }
                else if (solo->temFerramenta()) {
                    Ferramenta* f = solo->obterFerramenta();
                    out << "  (" << char('A' + l) << "," << char('A' + c) << ") - Ferramenta: " << f->getNome() << "\n";
                    encontrou = true;
                }
            }
        }
    }

    if (!encontrou)
        out << "  Nenhuma celula ocupada.\n";
}

/// AÇoES DO JARDINEIRO
void Comando::comandoEntrarJardim(Jardim* jardim, istringstream& iss, ostream& out) {
    string coords;
    int lin, col;

    if ( jardim == nullptr ) {
        out << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    if ( !(iss >> coords) ) {
        out << "Uso: entra <AA>\n" << endl;
        return;
    }

    if ( !converteCoordenada(coords, lin, col) ) {
        out << "Erro: Coordenadas invalidas. Use formato <AA>.\n" << endl;
        return;
    }

    if ( !jardim->posicaoValida(lin, col) ) {
        out << "Erro: Posicao fora dos limites do jardim.\n" << endl;
        return;
    }

    out << jardim->getJardineiro().entrar(lin, col);
    out << jardim->verificarEApanharFerramenta();
    out << jardim->imprimir();
}

void Comando::comandoSairJardim(Jardim* jardim, ostream& out) {

    if (jardim == nullptr) {
        out << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    if (!jardim->getJardineiro().estaDentro()) {
        out << "Erro: O jardineiro ja esta fora do jardim.\n" << endl;
        return;
    }

    out << jardim->getJardineiro().sair();
    out << jardim->imprimir();
}

void Comando::comandoMoverJardim(Jardim* jardim, char direcao, ostream& out) {
    if (jardim == nullptr) {
        out << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    Jardineiro& jardineiro = jardim->getJardineiro();

    if (!jardineiro.estaDentro()) {
        out << "Erro: O jardineiro esta fora do jardim.\n" << endl;
        return;
    }

    int lin = jardineiro.getLinha();
    int col = jardineiro.getColuna();

    switch (direcao) {
        case 'e': col--; break;
        case 'd': col++; break;
        case 'c': lin--; break;
        case 'b': lin++; break;
        default:
            out << "Erro: Direcao invalida.\n" << endl;
        return;
    }

    if (!jardim->posicaoValida(lin, col)) {
        out << "Erro: O jardineiro nao pode sair do jardim.\n" << endl;
        return;
    }

    out << jardineiro.mover(direcao);
    out << jardim->verificarEApanharFerramenta();
    out << jardim->imprimir();
}

void Comando::comandoPlantar(Jardim* jardim, istringstream& iss, ostream& out){
    string coords;
    char tipo, extra;
    int lin, col;

    if ( jardim == nullptr ) {
        out << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    if ( !(iss >> coords >> tipo) ) {
        out << "Uso: planta <AA> <tipo>\n";
        return;
    }

    if (iss>>extra) {
        out << "Uso: planta <AA> <tipo>\n";
        return;
    }

    if ( !converteCoordenada(coords, lin, col) ) {
        out << "Erro: Coordenadas invalidas. Use formato <AA>.\n" << endl;
        return;
    }

    Jardineiro& jardineiro = jardim->getJardineiro();

    if ( !jardineiro.estaDentro() ) {
        out << "Erro: O jardineiro esta fora do jardim.\n" << endl;
        return;
    }

    if ( !jardim->posicaoValida(lin, col) ) {
        out << "Erro: Posicao fora dos limites do jardim.\n" << endl;
        return;
    }

    if ( !jardineiro.podePlantar() ) {
        out << "Erro: Limite de plantacoes atingido!\n" << endl;
        return;
    }

    jardim->planta(lin, col, tipo, cout);
    jardineiro.registaPlantacao();
    out << jardim->imprimir();
}

void Comando::comandoColher(Jardim* jardim, istringstream& iss, ostream& out){
    string coords;
    int lin, col;

    if ( jardim == nullptr ) {
        out << "Erro: Crie primeiro um jardim com 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    Jardineiro& jardineiro = jardim->getJardineiro();
    if ( !jardineiro.estaDentro() ) {
        out << "Erro: O jardineiro esta fora do jardim.\n" << endl;
        return;
    }

    if ( !(iss >> coords) ) {
        out << "Use: colhe <AA>\n" << endl;
        return;
    }

    if ( !converteCoordenada(coords, lin, col) ) {
        out << "Erro: Coordenadas invalidas.\n" << endl;
        return;
    }

    if ( !jardim->posicaoValida(lin, col) ) {
        out << "Erro: Posicao fora dos limites.\n" << endl;
        return;
    }

    if ( !jardineiro.podeColher() ) {
        out << "Erro: Limite de colheitas atingido!\n" << endl;
        return;
    }

    jardim->colhe(lin, col, cout);
    jardineiro.registaColheita();
    out << jardim->imprimir();
};

/// FERRAMENTAS
void Comando::comandoListarFerramenta(Jardim* jardim, ostream& out) {

    if (jardim == nullptr) {
        out << "Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n";
        return;
    }

    bool encontrou = false;

    out << "Ferramentas disponiveis:\n";

    // Ferramentas no SOLO
    for (int l = 0; l < jardim->getNumLinhas(); l++) {
        for (int c = 0; c < jardim->getNumColunas(); c++) {

            Solo* solo = jardim->getSolo(l, c);
            if (solo != nullptr && solo->temFerramenta()) {

                Ferramenta* f = solo->obterFerramenta();
                out << "  Solo (" << char('A' + l) << char('A' + c) << ") - " << f->getNome() << " [nº serie: " << f->getNSerie() << ", capacidade: " << f->getCapacidade() << "]\n";

                encontrou = true;
            }
        }
    }

    // Ferramentas do JARDINEIRO
    Jardineiro& j = jardim->getJardineiro();

    // Ferramenta na mao
    Ferramenta* mao = j.obterFerramentaNaMao();
    if (mao != nullptr) {
        out << "  Jardineiro (na mao) - " << mao->getNome() << " [nº serie: " << mao->getNSerie() << ", capacidade: " << mao->getCapacidade() << "]\n";
        encontrou = true;
    }

    // Ferramentas no inventario
    for (int i = 0; ; i++) {
        Ferramenta* f = j.getFerramentaInventario(i);
        if (f == nullptr)
            break;

        out << "  Jardineiro (inventario) - " << f->getNome() << " [nº serie: " << f->getNSerie() << ", capacidade: " << f->getCapacidade() << "]\n";

        encontrou = true;
    }

    if (!encontrou) {
        out << "  Nenhuma ferramenta disponivel.\n";
    }
}

void Comando::comandoLargaFerramenta(Jardim* jardim, ostream& out) {
    if (jardim == nullptr) {
        out << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    Jardineiro& jardineiro = jardim->getJardineiro();

    if (!jardineiro.estaDentro()) {
        out << "Erro: O jardineiro esta fora do jardim.\n" << endl;
        return;
    }

    if (jardineiro.obterFerramentaNaMao() == nullptr) {
        out << "Erro: O jardineiro nao tem nenhuma ferramenta na mao.\n" << endl;
        return;
    }

    out << jardineiro.largarFerramenta();
    out << jardim->imprimir();
}

void Comando::comandoPegaFerramenta(Jardim* jardim, istringstream& iss, ostream& out) {
    int nSerie;

    if (jardim == nullptr) {
        out << "Erro: Crie primeiro um jardim com o comando 'jardim <linhas> <colunas>'.\n" << endl;
        return;
    }

    Jardineiro& jardineiro = jardim->getJardineiro();

    if ( !jardineiro.estaDentro() ) {
        out << "Erro: O jardineiro esta fora do jardim.\n" << endl;
        return;
    }

    if ( !(iss >> nSerie) ) {
        out << "Uso: pega <n>\n";
        return;
    }

    jardim->getJardineiro().pegarFerramenta(nSerie, cout);
    out << jardim->imprimir();
}

void Comando::comandoCompra(Jardim* jardim, istringstream& iss, ostream& out) {
    if (jardim == nullptr) {
        out << "Erro: ainda nao existe um jardim.\n";
        return;
    }

    Jardineiro& j = jardim->getJardineiro();

    if (!j.estaDentro()) {
        out << "Erro: o jardineiro tem de estar dentro do jardim para comprar ferramentas.\n";
        return;
    }

    char tipo;
    if (!(iss >> tipo)) {
        out << "Uso: compra <g|a|t|v>\n";
        return;
    }

    Ferramenta* nova = nullptr;

    switch (tipo) {
        case 'g':
            nova = new Regador();
        break;
        case 'a':
            nova = new Adubo();
        break;
        case 't':
            nova = new Tesoura();
        break;
        case 'v':
            nova = new VaraEspecial();
        break;
        default:
            out << "Erro: tipo de ferramenta invalido. Use g, a, t ou v.\n";
        return;
    }

    out << j.adicionarFerramenta(nova);

    out << "Ferramenta comprada com sucesso: " << nova->getNome() << " (nº serie " << nova->getNSerie() << ")\n";
}

/// FICHEIROS/MEMÓRIA
bool Comando::criaFicheiro( string nome, ostream& out) {
    filesystem::path ficheiro = "Save/" + nome + ".txt";
    ofstream outFile(ficheiro);
    if (!outFile) {
        out << "Erro ao criar o ficheiro: " << ficheiro << "\n" << endl;
        return false;
    }
    return true;
}

bool Comando::validaNomeficheiro(string nome, ostream& out) {
    if ((nome.find('.') != string::npos) || (nome.find('/')!= string::npos)) {
        out << "Nome invalido de ficheiro: " << nome << "\n" << endl;
        return false;
    }
    return true;
}

bool Comando::procuraFicheiro(string nome, string pasta){
    filesystem::path ficheiro = pasta + "/" + nome + ".txt";
    if (exists(ficheiro)) {
        return true;
    }
    return false;
}

void Comando::comandoGrava(Jardim*& jardim, istringstream& iss, ostream& out) {
    string nome;

    if (jardim == nullptr) {
        out << "Nao existe jardim para gravar!\n";
        return;
    }

    if (!(iss >> nome) || !iss.eof()) {
        out << "Uso: grava <nome>\n";
        return;
    }

    // se ja existir, nao deixa (sem overwrite)
    if (lista_gravacoes.find(nome) != lista_gravacoes.end()) {
        out << "Ja existe uma gravacao com o nome '" << nome << "'.\n";
        return;
    }

    lista_gravacoes[nome] = new Jardim(*jardim);

    out << "Gravacao '" << nome << "' guardada em memoria.\n";
}

void Comando::comandoRecupera(Jardim*& jardim, istringstream& iss, ostream& out){
    string nome;

    if (!(iss >> nome) || !iss.eof()) {
        out << "Uso: recupera <nome>\n";
        return;
    }

    auto it = lista_gravacoes.find(nome);
    if (it == lista_gravacoes.end()) {
        out << "Gravacao com nome '" << nome << "' nao existe.\n";
        return;
    }

    // substituir o jardim atual
    delete jardim;
    jardim = new Jardim(*it->second);
    jardim->getJardineiro().forcarFora();

    // a cópia e eliminada (como o enunciado pede)
    delete it->second;
    lista_gravacoes.erase(it);

    out << "Recuperado '" << nome << "' e removido da memoria.\n";
    out << jardim->imprimir();
}

void Comando::comandoApaga(istringstream& iss, ostream& out){
    string nome;

    if (!(iss >> nome) || !iss.eof()) {
        cout << "Uso: apaga <nome>\n";
        return;
    }

    auto it = lista_gravacoes.find(nome);
    if (it == lista_gravacoes.end()) {
        cout << "Gravacao com nome '" << nome << "' nao existe.\n";
        return;
    }

    delete it->second;
    lista_gravacoes.erase(it);

    cout << "Gravacao '" << nome << "' apagada da memoria.\n";
}

/// CORRER UM SCRIPT
void Comando::comandoRunscript(istringstream& iss, Interface& ui, ostream& out) {
    string nome, linha;
    string pasta = "Script";
    if (!(iss >> nome)) {
        out << "Uso: executa <ficheiro>\n";
        return;
    }
    if (!iss.eof()) {
        out << "Uso: executa <ficheiro>\n";
        return;
    }
    if (!validaNomeficheiro(nome, out)) {
        return;
    }
    if (procuraFicheiro(nome,pasta)){
        out << "Ficheiro com nome: " << nome << " existe!\n" << endl;
    }else {
        out << "Ficheiro com nome: " << nome << " nao existe!\n" << endl;
        return;
    }
    filesystem::path ficheiro = pasta + "/" + nome + ".txt";

    ifstream abre(ficheiro);
    if (!abre) {
        out << "Erro a abrir ficheiro!";
        return;
    }
    while (getline(abre, linha)) {
        if (linha.empty()) continue;
        out << "> " << linha << endl; //simula o > da Interface para mostrar o comando que estamos a usar
        ui.processarComando(linha, out);
    }
}

/// AJUDA
string const Comando::comandoAjuda() {
    ostringstream oss;
    oss << "Comandos disponiveis:\n"
         << " Criacao jardim:\n"
         << "   > jardim <linhas> <colunas>         - Cria um novo jardim\n"
         << " Gestao do Tempo:\n"
         << "   > avanca [n]                        - Avanca o tempo\n"
         << " Listagens:\n"
         << "   > lplantas                          - Lista todas as plantas existentes no jardim\n"
         << "   > lplanta <linha> <coluna>          - Mostra informacoes detalhadas sobre a planta na posicao indicada\n"
         << "   > larea                             - Mostra todas as posicoes ocupadas (plantas e ferramentas) no jardim\n"
         << "   > lsolo <linha> <coluna> [n]        - Mostra a informacao do solo na posicao indicada (e nas posicoes vizinhas, se n for fornecido)\n"
         << "   > lferr                             - Lista todas as ferramentas disponiveis (no solo e no inventario do jardineiro)\n"
         << " Movimento e posicao do jardineiro:\n"
         << "   > entra <linha> <coluna>            - Coloca o jardineiro dentro do jardim na posicao indicada\n"
         << "   > sai                               - Faz o jardineiro sair do jardim\n"
         << "   > e, d, c, b                        - Movem o jardineiro uma celula: esquerda, direita, cima, baixo (respetivamente)\n"
         << "   Acoes de jardinagem:\n"
         << "       > planta <linha> <coluna> <tipo> - Planta uma nova planta do tipo indicado na posicao especificada (c, r, e, x)\n"
         << "       > colhe <linha> <coluna>         - Colhe (remove) a planta na posicao indicada\n"
         << "   Ferramentas:\n"
         << "       > larga                         - Larga a ferramenta que o jardineiro tem atualmente na mao.\n"
         << "       > pega <n>                      - Pega na ferramenta com numero de serie n (se estiver na celula ou inventario).\n"
         << "       > compra <c>                    - Compra uma nova ferramenta do tipo c (ex.: g, a, t, z).\n"
         << " Ficheiros:\n"
         << "   > grava <nome_ficheiro>.txt         - Grava o ficheiro com o nome indicado\n"
         << "   > recupera <nome_ficheiro>.txt      - Abre o ficheiro guardado com o nome indicado\n"
         << "   > apaga <nome_ficheiro>.txt         - Apaga o ficheiro guardado com o nome indicado\n"
         << " Terminar:\n"
         << "   > fim                               - Termina o programa\n";
    return oss.str();
};

/// TERMINAR O PROGRAMA
void Comando::comandoFim(bool& ativo, ostream& out){
    ativo = false;
    out << "A terminar o simulador...\n";
}

/// CONVERTER CARACTERS PARA NuMEROS
bool Comando::converteCoordenada(const string& s, int& linha, int& coluna) {

    if (s.length() != 2)
        return false;

    char L = toupper(s[0]);
    char C = toupper(s[1]);

    if ( (L < 'A' || L > 'Z') || (C < 'A' || C > 'Z') ) {
        return false;
    }

    linha = L - 'A';
    coluna = C - 'A';

    return true;
}


void Comando::limparGravacoes() {
    for (auto& par : lista_gravacoes) {
        delete par.second;
    }
    lista_gravacoes.clear();
}