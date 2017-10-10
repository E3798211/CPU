#include <iostream>
#include "Cpu.h"
#include "Stack.h"
#include "Assembler.h"


int main()
{
    FileRead("2.txt", "3.txt");

    Cpu cpu;
    cpu.Run("3.txt");
}
