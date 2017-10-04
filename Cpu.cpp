#include "Cpu.h"


// execute

// sub -
// mul *
// fsqrt


int Cpu::Run()
{
    while(1){
        Cpu::Execute();
    }

    return 0;
}

int Cpu::Execute()
{
    char cmd[20] = "";
    MyType cmd_arg  = 0;

    cout << "Enter command: ";
    cin >> cmd >> cmd_arg;

    if      (!strcmp(cmd, "push")){
        Cpu::st.Push(&cmd_arg);
        Cpu::Dump();
    }else if(!strcmp(cmd, "pop")){
        Cpu::st.Pop(&cmd_arg);
        Cpu::Dump();
    }else if(!strcmp(cmd, "add")){
        int res = Cpu::BinOp([] (MyType a, MyType b)-> MyType
                                    {
                                        return a + b;
                                    });
        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::Dump();
    }else if(!strcmp(cmd, "subst")){
        int res = Cpu::BinOp([] (MyType a, MyType b)-> MyType
                                    {
                                        return b - a;
                                    });

        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::Dump();
    }else if(!strcmp(cmd, "mult")){
        int res = Cpu::BinOp([] (MyType a, MyType b)-> MyType
                                    {
                                        return a * b;
                                    });

        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::Dump();
    }else if(!strcmp(cmd, "div")){
        int res = Cpu::BinOp([] (MyType a, MyType b)-> MyType
                                    {
                                        return b / a;
                                    });

        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::Dump();
    }else if(!strcmp(cmd, "sqrt")){
        //int res = Cpu::Sqrt();
        int res = Cpu::UnOp([] (MyType a)-> MyType
                                    {
                                        return std::sqrt(a);
                                    });

        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::Dump();
    }

    return 0;
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
    // ASSERT

    if(st.GetNElem() < 1)
        return NOT_ENOUGH_ELEMENTS;

    MyType arg = 0;

    Cpu::st.Pop(&arg);

    MyType result = (*pOperation)(arg);

    Cpu::st.Push(&result);

    // ASSERT

    return SUCCESS;
}

int Cpu::BinOp(MyType (*pOperation)(MyType a, MyType b))
{
    // ASSERT

    if(st.GetNElem() < 2)
        return NOT_ENOUGH_ELEMENTS;

    MyType first  = 0;
    MyType second = 0;

    Cpu::st.Pop(&first);
    Cpu::st.Pop(&second);

    MyType third = (*pOperation)(first, second);

    Cpu::st.Push(&third);

    // ASSERT

    return SUCCESS;
}

