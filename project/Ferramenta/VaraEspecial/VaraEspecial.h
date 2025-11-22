//
// Created by jonhr on 31/10/2025.
//

#ifndef VaraEspecial_H
#define VaraEspecial_H

#include "../Ferramenta.h"
#include "../../Settings.h"

class VaraEspecial : public Ferramenta {
    public:
        VaraEspecial() : Ferramenta(Settings::VaraEspecial::capacidade, Settings::VaraEspecial::dose) {}

        char getSimbolo() const override { return 'V'; }
        string getNome() const override { return "Vara Especial"; }

        void utiliza(Solo& /*solo*/) override;
};



#endif //VaraEspecial_H
