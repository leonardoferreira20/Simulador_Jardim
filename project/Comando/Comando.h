//
// Created by Leonardo Ferreira on 11/10/2025.
//

#ifndef COMANDO_H
#define COMANDO_H

#include <string>
#include "../Jardim/Jardim.h"

using namespace std;

class Comando {
    public:
        static void comandoJardim(Jardim*& jardim, istringstream& iss);
        static void comandoAvanca(Jardim* jardim, istringstream& iss);
        static void comandoAjuda();
        static void comandoFim(bool& ativo);
};

#endif //COMANDO_H
