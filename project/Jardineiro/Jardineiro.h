//
// Created by Leonardo Ferreira on 11/10/2025.
//

#ifndef JARDINEIRO_H
#define JARDINEIRO_H


class Jardineiro {
    int linha;
    int coluna;
    bool dentro;  // indica se está no jardim ou não

public:
    Jardineiro() : linha(-1), coluna(-1), dentro(false) {}

    bool estaDentro() const { return dentro; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }

    // Por agora só simulamos as ações
    void entrar(int l, int c);
    void sair();
    void mover(char dir);
};

#endif //JARDINEIRO_H
