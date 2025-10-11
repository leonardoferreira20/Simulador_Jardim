//
// Created by Leonardo Ferreira on 11/10/2025.
//

#ifndef COMANDO_H
#define COMANDO_H

#include <string>

using namespace std;

class Comando {
    public:
      Comando();

      Comando(const string& comando);
      void executaComando(const string& comando);

      private:
        string comando;
};

#endif //COMANDO_H
