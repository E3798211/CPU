#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include "Stack.h"
#include "Errors.h"

#include <stdio.h>
#include <string.h>
#include <cmath>

#define BINOPERATOR( op )           \\



class Cpu {
private:
    Stack st;

public:
    Cpu() {};

    int Run();
    int Execute();

    int Add();
    int Subst();
    int Mult();
    int Div();
    int Sqrt();

    bool Ok();
    bool Dump();

};


#endif // CPU_H_INCLUDED
