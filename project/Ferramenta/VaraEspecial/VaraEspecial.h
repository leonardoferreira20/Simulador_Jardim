//
// Created by jonhr on 31/10/2025.
//

#ifndef VaraEspecial_H
#define VaraEspecial_H

#include "../Ferramenta.h"
#include "../../Settings.h"

class VaraEspecial : public Ferramenta {
    int contador;
public:
    explicit VaraEspecial(int cap = Settings::VaraEspecial::capacidade, int d = Settings::VaraEspecial::dose);
    void utiliza(Solo& solo) override;
    void fazChuva(Jardim* Jardim);
};



#endif //VaraEspecial_H
