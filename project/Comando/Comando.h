//
// Created by Leonardo Ferreira on 11/10/2025.
//

#ifndef COMANDO_H
#define COMANDO_H

#include <iostream>
#include "../Jardim/Jardim.h"

using namespace std;

class Comando {
    public:
        static void comandoAjuda();

        static void comandoJardim(Jardim*& jardim, istringstream& iss);
        static void comandoAvanca(Jardim* jardim, istringstream& iss);

        static void comandoListarPlantas(Jardim* jardim);
        static void comandoListaPlanta();
        static void comandoListarPosicoesOcupadas();
        static void comandoListarInfoSolo();
        static void comandoListarFerramenta();

        static void comandoEntrarJardim();
        static void comandoSairJardim();
        static void comandoMoverJardim();

        static void comandoPlantar(Jardim* jardim, istringstream& iss);
        static void comandoColher(Jardim* jardim, istringstream& iss);

        static void comandoFim(bool& ativo);
};

#endif //COMANDO_H
