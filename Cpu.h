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
    int Execute();

    bool Ok();
    bool Dump();

    int UnOp(MyType (*pOperation)(MyType a));
    int BinOp(MyType (*pOperation)(MyType a, MyType b));

};


#endif // CPU_H_INCLUDED
