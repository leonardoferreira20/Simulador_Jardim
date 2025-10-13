cmake_minimum_required(VERSION 3.30)
project(project)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        project
        # MAIN
        main.cpp
        #SOLO
        Solo/Solo.cpp
        Solo/Solo.h
        #Jardim
        Jardim/Jardim.cpp
        Jardim/Jardim.h
        #Jardineiro
        Jardineiro/Jardineiro.cpp
        Jardineiro/Jardineiro.h
        #Comando
        Comando/Comando.cpp
        Comando/Comando.h
        #Settings
        Settings.h
)
