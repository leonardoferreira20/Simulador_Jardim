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
        /// CRIAR JARDIM
        static Jardim *comandoJardim(istringstream &iss);

        /// AVANÇAR NO TEMPO
        static void comandoAvanca(Jardim* jardim, istringstream& iss);

        /// LISTAR INFORMAÇÃO SOBRE PLANTAS
        static void comandoListarPlantas(Jardim* jardim);
        static void comandoListarPlanta(Jardim* jardim, istringstream& iss);

        /// LISTAR INFORMAÇÃO SOBRE O SOLO
        static void comandoListarInfoSolo(Jardim* jardim, istringstream& iss);
        static void comandoListarArea(Jardim* jardim);

        /// AÇÕES DO JARDINEIRO
        static void comandoEntrarJardim(Jardim* jardim, istringstream& iss);
        static void comandoSairJardim(Jardim* jardim);
        static void comandoMoverJardim(Jardim* jardim, char direcao);
        static void comandoPlantar(Jardim* jardim, istringstream& iss);
        static void comandoColher(Jardim* jardim, istringstream& iss);

        /// FERRAMENTAS
        static void comandoListarFerramenta(Jardim* jardim);
        static void comandoLargaFerramenta(Jardim* jardim); // IMPLEMENTAR
        static void comandoPegaFerramenta(Jardim* jardim, istringstream& iss); // IMPLEMENTAR
        static void comandoCompra(Jardim* jardim, istringstream& iss); // IMPLEMENTAR

        /// VERIFICATION FUNCTIONS
        static bool converteCoordenada(const string& s, int& linha, int& coluna);
        static bool validaNomeficheiro(string nome); // REMOVER

        /// FICHEIROS/MEMÓRIA
        static bool procuraFicheiro(string nome,string pasta); // REMOVER
        static bool criaFicheiro( string nome); // A VER
        static void comandoGrava(Jardim*& jardim, istringstream& iss);
        static void comandoRecupera(Jardim*& jardim, istringstream& iss);
        static void comandoApaga(istringstream& iss);

        /// CORRER UM SCRIPT
        static void comandoRunscript(istringstream& iss, Interface& ui);

        /// AJUDA
        static void comandoAjuda();

        /// TERMINAR O PROGRAMA
        static void comandoFim(bool& ativo);
        static void limparGravacoes();
};

#endif //COMANDO_H
