cmake_minimum_required(VERSION 3.24)
project(CPPprojekt)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPPprojekt main.cpp Towar.cpp Sklep.cpp Siec.cpp Klient.cpp Miasto.cpp ObiektHandlowy.h ObiektHandlowy.cpp)
