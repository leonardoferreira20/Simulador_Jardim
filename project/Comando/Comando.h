//
// Created by Leonardo Ferreira on 11/10/2025.
//

#ifndef COMANDO_H
#define COMANDO_H

#include <iostream>

class Interface;
class Jardim;

using namespace std;

class Comando {
    public:
    /// Criação do jardim
    static Jardim* comandoJardim(istringstream& iss, ostream& out);

    /// Gestão do tempo
    static void comandoAvanca(Jardim* jardim, istringstream& iss, ostream& out);

    /// Listagens
    static void comandoListarPlantas(Jardim* jardim, ostream& out);
    static void comandoListarPlanta(Jardim* jardim, istringstream& iss, ostream& out);
    static void comandoListarInfoSolo(Jardim* jardim, istringstream& iss, ostream& out);
    static void comandoListarArea(Jardim* jardim, ostream& out);
    static void comandoListarFerramenta(Jardim* jardim, ostream& out);

    /// Movimento e posição do jardineiro
    static void comandoEntrarJardim(Jardim* jardim, istringstream& iss, ostream& out);
    static void comandoSairJardim(Jardim* jardim, ostream& out);
    static void comandoMoverJardim(Jardim* jardim, char direcao, ostream& out);

    /// Ações de jardinagem
    static void comandoPlantar(Jardim* jardim, istringstream& iss, ostream& out);
    static void comandoColher(Jardim* jardim, istringstream& iss, ostream& out);

    /// Ferramentas
    static void comandoLargaFerramenta(Jardim* jardim, ostream& out);
    static void comandoPegaFerramenta(Jardim* jardim, istringstream& iss, ostream& out);
    static void comandoCompra(Jardim* jardim, istringstream& iss, ostream& out);

    /// VERIFICATION FUNCTIONS
    static bool converteCoordenada(const string& s, int& linha, int& coluna);
    static bool validaNomeficheiro(string nome, ostream& out); // REMOVER

    /// FICHEIROS/MEMÓRIA
    static bool procuraFicheiro(string nome,string pasta); // REMOVER
    static bool criaFicheiro(string nome, ostream& out); // A VER
    static void comandoGrava(Jardim*& jardim, istringstream& iss, ostream& out);
    static void comandoRecupera(Jardim*& jardim, istringstream& iss, ostream& out);
    static void comandoApaga(istringstream& iss, ostream& out);

    /// CORRER UM SCRIPT
    static void comandoRunscript(istringstream& iss, Interface& ui, ostream& out);

    /// AJUDA
    static void comandoAjuda(ostream& out);

    /// TERMINAR O PROGRAMA
    static void comandoFim(bool& ativo, ostream& out);
    static void limparGravacoes();
};

#endif //COMANDO_H
