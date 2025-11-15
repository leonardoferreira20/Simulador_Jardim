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
        # PLANTA - Erva Daninha
        Planta/ErvaDaninha/ErvaDaninha.cpp
        # PLANTA - Exotica
        Planta/Exotica/Exotica.cpp
        # Ferramenta - Exotica
        Ferramenta/Ferramenta.cpp
        # Ferramenta - Tesoura
        Ferramenta/Tesoura/Tesoura.cpp
        # Ferramenta - Regador
        Ferramenta/Regador/Regador.cpp
        # Ferramenta - VaraEspecial
        Ferramenta/VaraEspecial/VaraEspecial.cpp
        # Ferramenta - Adubo
        Ferramenta/Adubo/Adubo.cpp
        # SETTINGS
        Settings.h
)
