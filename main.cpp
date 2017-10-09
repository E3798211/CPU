#include <iostream>
#include "Cpu.h"
#include "Stack.h"
#include "Assembler.h"

struct Str{
    int _edge_1 = EDGE;
    long long int _size   = 0;
    long long int _n_elem = 0;
    MyType* _stack = nullptr;
};

int main()
{
    //Cpu cpu;
    //cpu.Run("1.txt");

    /*
    Stack st;
    Str* hack = (Str*)&st;

    hack->_stack = nullptr;

    MyType a = 5;
    st.Push(&a);
    */

    FileRead("2.txt", "3.txt");
}
