//
// Created by Leonardo Ferreira on 11/10/2025.
//

#ifndef SOLO_H
#define SOLO_H

#include <string>

using namespace std;

class Solo {
    public:
        string imprimirSolo ();

        void adicionaAgua ();

        void retiraAgua ();
    private:
        int agua;
        int nutrientes;
};



#endif //SOLO_H
