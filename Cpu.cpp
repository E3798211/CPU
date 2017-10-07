#include "Cpu.h"


int Cpu::Run()
{
    int status = 1;
    while(status != -1){
        status = Cpu::Execute();
    }

    cout << "Runnig ended." << endl;

    return 0;
}

int Cpu::Execute()
{
    CPU_ASSERT();

    int cmd = -1;
    MyType cmd_arg  = 0;

    cout << "Enter command: ";
    cin >> cmd >> cmd_arg;

    if      (cmd == PUSH){

        Cpu::st.Push(&cmd_arg);
        Cpu::PrintStack();

    }else if(cmd == POP){

        Cpu::st.Pop(&cmd_arg);
        Cpu::PrintStack();

    }else if(cmd == ADD){

        int res = Cpu::BinOp([] (MyType a, MyType b)-> MyType
                                    {
                                        return a + b;
                                    });
        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::PrintStack();

    }else if(cmd == SUB){

        int res = Cpu::BinOp([] (MyType a, MyType b)-> MyType
                                    {
                                        return b - a;
                                    });
        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::PrintStack();

    }else if(cmd == MUL){

        int res = Cpu::BinOp([] (MyType a, MyType b)-> MyType
                                    {
                                        return a * b;
                                    });
        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::PrintStack();

    }else if(cmd == DIV){

        int res = Cpu::BinOp([] (MyType a, MyType b)-> MyType
                                    {
                                        return b / a;
                                    });
        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::PrintStack();

    }else if(cmd == FSQRT){

        int res = Cpu::UnOp([] (MyType a)-> MyType
                                    {
                                        return std::sqrt(a);
                                    });
        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::PrintStack();

    }else if(cmd == END){
        return -1;
    }

    CPU_ASSERT();

    return 0;
}

int Cpu::PrintStack()
{
    CPU_ASSERT();
    return st.PrintStack();
    CPU_ASSERT();
}



bool Cpu::Ok()
{
    return Cpu::st.Ok();
}

bool Cpu::Dump()
{
    return Cpu::st.Dump("Cpu::Dump");
}


int Cpu::UnOp(MyType (*pOperation)(MyType a))
{
    CPU_ASSERT();

    if(st.GetNElem() < 1)
        return NOT_ENOUGH_ELEMENTS;

    MyType arg = 0;

    Cpu::st.Pop(&arg);

    MyType result = (*pOperation)(arg);

    Cpu::st.Push(&result);

    CPU_ASSERT();

    return SUCCESS;
}

int Cpu::BinOp(MyType (*pOperation)(MyType a, MyType b))
{
    CPU_ASSERT();

    if(st.GetNElem() < 2)
        return NOT_ENOUGH_ELEMENTS;

    MyType first  = 0;
    MyType second = 0;

    Cpu::st.Pop(&first);
    Cpu::st.Pop(&second);

    MyType third = (*pOperation)(first, second);

    Cpu::st.Push(&third);

    CPU_ASSERT();

    return SUCCESS;
}

