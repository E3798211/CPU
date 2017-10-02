#include <iostream>
#include "Cpu.h"

const int CMD_SEQ_LEN = 5;


const int PUSH  = 1;
const int POP   = 2;


int CmdArgument (const char* cmd);

int main()
{
    Cpu cpu;

    cpu.Run();
}
