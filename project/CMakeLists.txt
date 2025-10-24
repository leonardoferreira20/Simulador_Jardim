cmake_minimum_required(VERSION 3.30)
project(project)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        project
        # MAIN
        main.cpp
        # INTERFACE
        Interface/Interface.cpp
        Interface/Interface.h
        # SOLO
        Solo/Solo.cpp
        Solo/Solo.h
        # JARDIM
        Jardim/Jardim.cpp
        Jardim/Jardim.h
        # JARDINEIRO
        Jardineiro/Jardineiro.cpp
        Jardineiro/Jardineiro.h
        # COMANDO
        Comando/Comando.cpp
        Comando/Comando.h
        # SETTINGS
        Settings.h
)
