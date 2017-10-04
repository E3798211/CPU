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
        int res = Cpu::Add();

        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::Dump();
    }else if(!strcmp(cmd, "subst")){
        int res = Cpu::Subst();

        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::Dump();
    }else if(!strcmp(cmd, "mult")){
        int res = Cpu::Mult();

        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::Dump();
    }else if(!strcmp(cmd, "div")){
        int res = Cpu::Div();

        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::Dump();
    }else if(!strcmp(cmd, "sqrt")){
        int res = Cpu::Sqrt();

        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;

        Cpu::Dump();
    }

    return 0;
}

int Cpu::Add()
{
    // ASSERT

    if(st.GetNElem() < 2)
        return NOT_ENOUGH_ELEMENTS;

    MyType first  = 0;
    MyType second = 0;

    Cpu::st.Pop(&first);
    Cpu::st.Pop(&second);

    MyType third = first + second;      // ?

    Cpu::st.Push(&third);

    // ASSERT

    return SUCCESS;
}

int Cpu::Subst()
{
    // ASSERT

    if(st.GetNElem() < 2)
        return NOT_ENOUGH_ELEMENTS;

    MyType first  = 0;
    MyType second = 0;

    Cpu::st.Pop(&first);
    Cpu::st.Pop(&second);

    MyType third = second - first;      // ?

    Cpu::st.Push(&third);

    // ASSERT

    return SUCCESS;
}

int Cpu::Mult()
{
    // ASSERT

    if(st.GetNElem() < 2)
        return NOT_ENOUGH_ELEMENTS;

    MyType first  = 0;
    MyType second = 0;

    Cpu::st.Pop(&first);
    Cpu::st.Pop(&second);

    MyType third = second * first;      // ?

    Cpu::st.Push(&third);

    // ASSERT

    return SUCCESS;
}

int Cpu::Div()
{
    // ASSERT

    if(st.GetNElem() < 2)
        return NOT_ENOUGH_ELEMENTS;

    MyType first  = 0;
    MyType second = 0;

    Cpu::st.Pop(&first);
    Cpu::st.Pop(&second);

    MyType third = second / first;      // ?

    Cpu::st.Push(&third);

    // ASSERT

    return SUCCESS;
}

int Cpu::Sqrt()
{
    // ASSERT

    if(st.GetNElem() < 1)
        return NOT_ENOUGH_ELEMENTS;

    MyType sqrt_arg = 0;

    Cpu::st.Pop(&sqrt_arg);

    MyType sqrt = std::sqrt(sqrt_arg);

    Cpu::st.Push(&sqrt);

    // ASSERT

    return SUCCESS;
}

bool Cpu::Ok()
{
    return Cpu::st.Ok();
}

bool Cpu::Dump()
{
    return Cpu::st.Dump("Cpu::Dump");
}

