cmake_minimum_required(VERSION 3.30)
project(project)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        project main.cpp

        #SOLO
        Solo/Solo.cpp
        Solo/Solo.h
        #Jardim
        Jardim/Jardim.cpp
        Jardim/Jardim.h
        #Jardineiro
        Jardineiro/Jardineiro.cpp
        Jardineiro/Jardineiro.h
        #Settings
        Settings.h
)
