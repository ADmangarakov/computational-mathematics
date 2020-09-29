# cmake_minimum_required(VERSION <specify CMake version here>)
project(equation_solver)

set(CMAKE_CXX_STANDARD 14)

add_executable(equation_solver main.cpp Equation.cpp Equation.h EquationRoot.cpp EquationRoot.h)