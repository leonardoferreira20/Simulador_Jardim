#ifndef ERVADANINHA_H
#define ERVADANINHA_H

#include "../Planta.h"
#include "../../Settings.h"

class ErvaDaninha : public Planta {
    int ultimaReproducao;   // instante (tempoVida) da última reprodução

public:
    explicit ErvaDaninha(int ag = Settings::ErvaDaninha::inicial_agua,
                         int nut = Settings::ErvaDaninha::inicial_nutrientes);

    Planta* clone() const override;

    void agir(Solo& solo) override;
    void morrer(Solo& solo, ostream& out) override;

    char getSimbolo() const override;
    string getNome() const override;

    Planta* reproduzPlanta() override;
    bool podeReproduzir() override;

    bool isFeia() override { return true; }
    bool reproduzEmSoloOcupado() const override { return true; } // erva pode substituir
};

#endif //ERVADANINHA_H
