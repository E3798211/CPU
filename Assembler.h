#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include "CpuProperties.h"

#include "assert.h"
#include <cstdio>
#include <iostream>
#include  <cstring>

#include "Errors.h"
#include "Commands.h"

// DEBUG
//=================================================================
// Comment next line if you want to turn debug off
#define _DEBUG

#if defined (_DEBUG)
    #define DEBUG
#else
    #define DEBUG if(0)
#endif // defined

//=================================================================


struct Label {
    int  place     = -1;
    char name[128] = "NONAME";
};


using std::cin;
using std::cout;
using std::endl;

int FileRead(char* file_name1, char* file_name2);
int Pass(FILE *input, double** ram, int* n_cmd, Label** labels, int* label_num);

#endif // ASSEMBLER_H_INCLUDED
