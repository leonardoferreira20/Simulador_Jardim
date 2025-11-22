//
// Created by Leonardo Ferreira on 23/10/2025.
//

#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>

using namespace std;

class Jardim;

class Interface {
    Jardim* jardim;
    bool ativo;

    public:
        Interface();
        ~Interface();
        void executar();
        void processarComando(const string& linha);
};

#endif //INTERFACE_H
