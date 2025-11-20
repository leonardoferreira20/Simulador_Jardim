//
// Created by Leonardo Ferreira on 25/10/2025.
//

#ifndef PLANTA_H
#define PLANTA_H

#include <iostream>
#include "../Solo/Solo.h"
#include "../Settings.h"

using namespace std;

class Solo;
/**
 * @class Planta
 * @brief Classe base abstrata que representa uma planta genérica no jardim.
 *
 * Esta classe define os atributos e comportamentos comuns a todas as plantas,
 * como a quantidade de água, nutrientes e o estado de vida.
 * As subclasses (Cacto, Roseira, etc.) implementam o seu comportamento específico
 * através dos métodos virtuais puros.
 */
class Planta {
    int agua=0;
    int tempoVida=0;
    int nutrientes=0;
    bool viva;
    bool recemNascida;

public:

    Planta(int agua,int nut);
    virtual ~Planta() = default;

    // Métodos abstratos (a serem implementados pelas subclasses)
    virtual void agir(Solo& solo) = 0;
    virtual void morrer(Solo& solo) = 0;
    virtual char getSimbolo() const = 0;
    virtual string getNome() const = 0;

    // Métodos comuns a todas as plantas
    bool estaViva() const {return viva;};
    int obtemAguaP() const {return agua;};
    int obtemNutrientesP() const {return nutrientes;};
    int obtemTempoVida() const {return tempoVida;};

    //Metodos para alterar
    void alteraAgua(int quant) {agua+=quant;};
    void setAgua(int quant) {agua=quant;};
    void alteraNutrientes(int quant) {nutrientes+=quant;};
    void setNutrientes(int quant) {nutrientes=quant;};
    void alteraViva(bool v) {viva=v;};
    void aumentaTempoVida() {tempoVida++;}
    void setTempoVida(int quant) {tempoVida=quant;};

    bool isRecemNascida() const { return recemNascida; }
    void setRecemNascida(bool valor) { recemNascida = valor; }

    virtual Planta* reproduzPlanta() = 0;
};

#endif // PLANTA_H
