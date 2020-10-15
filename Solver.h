//
// Created by mi on 13.10.2020.
//

#ifndef HORIZRK_SOLVER_H
#define HORIZRK_SOLVER_H

#include "MyTypedefs.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace myTypedefs;

enum computationTypes
{
    EULER, EULER_MOD, RK4
};

class Solver
{
private:
    double **data;
    int N;
    double h, xMax;

private:
    double func(const double &x, const double &y);

    double rk4Function(const double &x, const double &y);

    double eulerFunction(const double &x, const double &y);

    double eulerModFunction(const double &x, const double &y);

public:
    Solver(const double &h, const double &xMax);
    ~Solver();

    void compute(const computationTypes &computationType, const double &y0);

    void save(std::fstream &file);
};


#endif //HORIZRK_SOLVER_H
