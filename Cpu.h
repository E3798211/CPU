#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include "Stack.h"
#include "Errors.h"

#include <stdio.h>
#include <string.h>
#include <cmath>


class Cpu {
private:
    Stack st;

public:
    Cpu() {};

    int Run();

    int Add();
    int Subst();
    int Mult();
    int Div();
    int Sqrt();

    bool Ok();
    bool Dump();
};


#endif // CPU_H_INCLUDED
