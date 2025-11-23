//
// Created by jonhr on 31/10/2025.
//

#include "VaraEspecial.h"

using namespace std;

    VaraEspecial::VaraEspecial(int cap, int d):Ferramenta(cap,d) {

    }

    void VaraEspecial::utiliza(Solo& solo) {
        if (solo.obterPlanta()!=nullptr) {
            Planta* p = solo.obterPlanta();
            p->alteraNutrientes(20);
            p->alteraAgua(20);
        }
    }

    void VaraEspecial::fazChuva(Jardim* jardim) {
        for (int i=0;i<jardim->getNumLinhas();i++) {
            for (int j=0;i<jardim->getNumColunas();i++) {
                Solo* solo = jardim->getSolo(i,j);
                utiliza(*solo);
            }
        }
    }