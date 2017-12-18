#include <iostream>
#include "Cpu.h"
#include "Stack.h"
#include "Assembler.h"


int main()
{

    //FileRead("5.txt", "3.txt");
    FileRead("6.txt", "3.txt");


    Cpu cpu;
    cpu.Run("3.txt");
}

