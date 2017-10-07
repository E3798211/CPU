#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include "Stack.h"
#include "Errors.h"
#include "Commands.h"

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
    /// Cpu constructor
    Cpu() {};


    /// Run. Calls execute().
    int Run();

    /// Executes command.
    /**
        Returns (-1) if END reached, 0 otherwise.
    */
    int Execute();

    /// Prints stack content.
    /**
        Returns amount of printed elements.
    */
    int PrintStack();


    /// Verificator.
    /**
        Returns SUCCSESS if everithing is ok, error code othewise.
    */
    int Ok();

    /// Dump.
    /**
        Returns TRUE if Dump() printed maximum info, FALSE otherwise (some error happened).
    */
    bool Dump();


    /// Unary operion
    /**
        \param [in] *(pOperation)(MyType a)     Pointer to function to be executed on "a".
    */
    int UnOp(MyType (*pOperation)(MyType a));

    /// Binary operion
    /**
        \param [in] *(pOperation)(MyType a, MyType b)     Pointer to function to be executed on "a" and "b".
    */
    int BinOp(MyType (*pOperation)(MyType a, MyType b));

};


#endif // CPU_H_INCLUDED
