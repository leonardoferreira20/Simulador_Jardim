#ifndef EXOTICA_H
#define EXOTICA_H

#include "../Planta.h"
#include "../../Settings.h"

class Exotica : public Planta {
public:
    explicit Exotica(int ag = Settings::Exotica::inicial_agua, int nut = Settings::Exotica::inicial_nutrientes);

    Planta* clone() const override;

    void agir(Solo& solo) override;
    void morrer(Solo& solo, ostream& out) override;

    char getSimbolo() const override;
    string getNome() const override;

    bool isFeia() override;              // <-- OBRIGATÓRIO (Planta tem puro)

    bool podeReproduzir() override;
    Planta* reproduzPlanta() override;
};

#endif //EXOTICA_H