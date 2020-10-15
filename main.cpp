#include <iostream>
#include <fstream>
#include "Solver.h"

int main()
{
    Solver solver(0.01,1);

    std::fstream file;

    file.open("rk4.txt", std::ios::out);
    solver.compute(RK4,1);
    solver.save(file);
    file.close();

    file.open("euler.txt", std::ios::out);
    solver.compute(EULER,1);
    solver.save(file);
    file.close();

    file.open("euler_mod.txt", std::ios::out);
    solver.compute(EULER_MOD,1);
    solver.save(file);
    file.close();

    return 0;
}