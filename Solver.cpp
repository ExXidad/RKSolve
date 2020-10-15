//
// Created by mi on 13.10.2020.
//

#include "Solver.h"

double Solver::func(const double &x, const double &y)
{
    return x * x - 2 * y;
}

void Solver::compute(const computationTypes &computationType, const double &y0)
{
    double (Solver::*computationFunction)
            (
                    const double &,
                    const double &
            );

    switch (computationType) {
        case EULER:
            computationFunction = &Solver::eulerFunction;
            break;
        case RK4:
            computationFunction = &Solver::rk4Function;
            break;
        case EULER_MOD:
            computationFunction = &Solver::eulerModFunction;
            break;
    }

    data[0][0] = 0;
    data[0][1] = y0;

    for (int i = 1; i < N; ++i) {
        double x = data[i - 1][0], y = data[i - 1][1];

        data[i][0] = h * i;
        data[i][1] = (this->*computationFunction)(x, y);
    }


}

Solver::Solver(const double &h, const double &xMax)
{
    this->h = h;
    N = int(xMax / h);
    data = new double *[N];
    for (int i = 0; i < N; ++i) {
        data[i] = new double[2];
    }
}

Solver::~Solver()
{
    for (int i = 0; i < N; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

double Solver::rk4Function(const double &x, const double &y)
{
    double k1 = func(x, y);
    double k2 = func(x + h / 2, y + h * k1 / 2);
    double k3 = func(x + h / 2, y + h * k2 / 2);
    double k4 = func(x + h, y + h * k3);

    return y + 1. / 6 * h * (k1 + 2 * k2 + 2 * k3 + k4);
}

double Solver::eulerFunction(const double &x, const double &y)
{
    return y + func(x, y) * h;
}

double Solver::eulerModFunction(const double &x, const double &y)
{
    double yNextHalf = y + h / 2 * func(x, y);
    return y + h * func(x + h / 2, yNextHalf);
}

void Solver::save(std::fstream &file)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 2; ++j) {
            file << std::setprecision(8) << data[i][j] << "\t";
        }
        file << std::endl;
    }
}
