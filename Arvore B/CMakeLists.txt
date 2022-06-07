cmake_minimum_required(VERSION 3.22)
project(btree C)

set(CMAKE_C_STANDARD 99)

add_executable(btree main.c Aluno.c Aluno.h Util.c Util.h ArvoreB.c ArvoreB.h)
