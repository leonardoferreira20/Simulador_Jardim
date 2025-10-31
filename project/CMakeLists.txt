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
        # SETTINGS
        Settings.h
        Ferramenta/Tesoura/Tesoura.cpp
        Ferramenta/Tesoura/Tesoura.h
        Ferramenta/Regador/Regador.cpp
        Ferramenta/Regador/Regador.h
        Ferramenta/FerramentaZ/FerramentaZ.cpp
        Ferramenta/FerramentaZ/FerramentaZ.h
        Ferramenta/Adubo/Adubo.cpp
        Ferramenta/Adubo/Adubo.h
        Planta/ErvaDaninha/ErvaDaninha.cpp
        Planta/ErvaDaninha/ErvaDaninha.h
        Planta/Exotica/Exotica.cpp
        Planta/Exotica/Exotica.h
)
