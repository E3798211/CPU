#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include "Stack.h"
#include "Errors.h"
#include "Commands.h"

#include <assert.h>
#include <cstdio>
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


//const char WRONG_SIGNATURE[]    = "WRONGSIGNATURE";


#define WRONG_SIGNATURE "WRONGSIGNATURE"
const int  WRONG_VERSION        = -1;
const char GENUINE_SIGNATURE[]  = "EK";
const int  GENUINE_VERSION      = 1;


class Cpu {
private:
    Stack st;

public:
    /// Cpu constructor
    Cpu() {};


    /// Reads file with commands.
    /**
        Returns error code.

        \param [in, out]    cmd_sequence    Array with commands' numbers. Last num is always (-1).
        \param [in]         filename        Name of the file with compiled code.
    */
    int FileRead(double* cmd_sequence, char* filename);


    /// Run. Calls execute() in a loop.
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
