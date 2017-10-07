#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include "Stack.h"
#include "Errors.h"

#include <stdio.h>
#include <string.h>
#include <cmath>


#define CPU_ASSERT()            \
    {                           \
        int err = Cpu::Ok();    \
        if(err != SUCCESS){     \
            Cpu::Dump();        \
            assert(0);          \
        }                       \
    }


class Cpu {
private:
    Stack st;

public:
    Cpu() {};

    int Run();
    int Execute();
    int PrintStack();

    bool Ok();
    bool Dump();

    int UnOp(MyType (*pOperation)(MyType a));
    int BinOp(MyType (*pOperation)(MyType a, MyType b));

};


#endif // CPU_H_INCLUDED
