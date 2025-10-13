#include <iostream>
#include "Jardim/Jardim.h"
#include "Comando/Comando.h"

int main() {
    string cmd;


    cout << "-------------------------------------" << endl;
    cout << "$~ ";
    cin >> cmd;

    if ( cmd == "executa" ) {
        Jardim jardim(10, 10);

        jardim.imprimir();
    }

    return 0;
}
