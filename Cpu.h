#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include "CpuProperties.h"

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





class Cpu {
private:
    Stack st;
    double registers[4];

    long long int cpu_hash = 0;

    /// Hash-count
    long long int HashCount();

public:
    /// Cpu constructor
    Cpu()
    {
        registers[0] = 0;
        registers[1] = 0;
        registers[2] = 0;
        registers[3] = 0;
        cpu_hash = HashCount();
    };


    /// Reads file with commands.
    /**
        Returns error code.
        \warning Pointer cmd_sequence will be changed inside!

        \param [in, out]    cmd_sequence    Array with commands' numbers. Last num is always (-1).
        \param [in]         filename        Name of the file with compiled code.
    */
    int FileRead(double** cmd_sequence, char* filename);


    /// Run. Calls execute() in a loop.
    /**
        Returns SUCCESS if everyting is ok, FATAL_ERROR otherwise.

        \param [in] file_name   Name of the file with commands.
    */
    int Run(char* file_name);

    /// Executes command.
    /**
        Returns END if END reached, SUCCESS otherwise.
        \warning cmd_num can and probably would be changed inside!

        \param [in] cmd_sequence    List with commands.
        \param [in] cmd_num         Num of the command to be executed.
    */
    int Execute(double* cmd_sequence, int &cmd_num);

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
    bool Dump(const char* func_name = __func__, int err_code = 0);


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

    /// Jump
    /**
        \param [in] *(pCompare)(MyType a, MyType b)     Pointer to function that checks if condition is correst
        \param [in] cmd_num     Varriable responsible for next command
        \param [in] jmp_to      Jump to new command
    */
    int Jmp(int* cmd_num, int jmp_to, bool (*pCompare)(MyType a, MyType b));
};


#endif // CPU_H_INCLUDED
