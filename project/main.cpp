#include <iostream>
#include "Jardim/Jardim.h"
#include "Comando/Comando.h"

int main() {
    //Jardim jardim(26, 26);
    string cmd;
    Comando comando;

    //printf("%s\n", comando.executaComando(comando));

    cout << "-------------------------------------" << endl;
    cout << "$~";
    cin >> cmd;
    cout << "-------------------------------------" << endl;

    /*switch (cmd) {
        case "executa":
            comando.executaComando();
        case "sair": {

        }
        default:
            return 0;
    }*/

    return 0;
}
