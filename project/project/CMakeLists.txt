cmake_minimum_required(VERSION 3.30)
project(project)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        project
        # MAIN
        main.cpp
        # INTERFACE
        Interface/Interface.cpp
        # SOLO
        Solo/Solo.cpp
        # JARDIM
        Jardim/Jardim.cpp
        # JARDINEIRO
        Jardineiro/Jardineiro.cpp
        # COMANDO
        Comando/Comando.cpp
        # PLANTA
        Planta/Planta.cpp
        # PLANTA - CACTO
        Planta/Cacto/Cacto.cpp
        # PLANTA - ROSEIRA
        Planta/Roseira/Roseira.cpp
        # PLANTA - ERVA DANINHA
        Planta/ErvaDaninha/ErvaDaninha.cpp
        # PLANTA - EXOTICA
        Planta/Exotica/Exotica.cpp
        # FERRAMENTA
        Ferramenta/Ferramenta.cpp
        # FERRAMENTA - TESOURA
        Ferramenta/Tesoura/Tesoura.cpp
        # FERRAMENTA - REGADOR
        Ferramenta/Regador/Regador.cpp
        # FERRAMENTA - VARA ESPECIAL
        Ferramenta/VaraEspecial/VaraEspecial.cpp
        # FERRAMENTA - ADUBO
        Ferramenta/Adubo/Adubo.cpp
        # SETTINGS
        Settings.h
)
