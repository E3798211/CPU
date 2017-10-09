#include "Cpu.h"


int Cpu::FileRead(double* &cmd_sequence, char* file_name)
{
    // Exceptions
    assert(file_name != nullptr);

    FILE *input = fopen(file_name, "r");
    if(input == nullptr){
        DEBUG cout << "File not found!" << endl;
        return FILE_NOT_FOUND;
    }


    if(fseek(input, 0, SEEK_END)){
        cout << "Can not set last position in " << file_name << endl;
        return FILE_POS_ERROR;
    }

    int file_size = ftell(input);
    if(file_size == EOF){
        cout << "Can not get pointer's position in " << file_name << endl;
        return FILE_POS_ERROR;
    }

    //fclose(input);
    //input = fopen(file_name, "r");
    //cout << "setvbuf = " << setvbuf(input, nullptr, _IOFBF, file_size) << endl;


    // Reading file's beginning
    rewind(input);

    char signature[] = WRONG_SIGNATURE;
    int  version     = WRONG_VERSION;

    if(!fscanf(input, "%s", signature)){
        DEBUG cout << "Can not read signature!" << endl;
        return READ_ERROR;
    }
    if(!fscanf(input, "%d", &version)){
        DEBUG cout << "Can not read processor version!" << endl;
        return READ_ERROR;
    }

    int n_cmds = -1;
    if(!fscanf(input, "%d", &n_cmds)){
        DEBUG cout << "Can not read amount of commands!" << endl;
        return READ_ERROR;
    }


    // Check if file is compatible with processor

    if(strcmp(signature, GENUINE_SIGNATURE)){
        DEBUG cout << "Bad signature! signature = |" << signature << "|" << endl;
        return BAD_SIGNATURE;
    }
    if(version != GENUINE_VERSION){
        DEBUG cout << "Bad version! version = |" << version << "|" << endl;
        return BAD_VERSION;
    }


    // Creating an array with commands
    try{
        cmd_sequence = new double [n_cmds];
    }
    catch(const std::bad_alloc& ex){
        cout << ERR_WHERE << ". Cannot allocate " << n_cmds << " doubles." << endl;
        return BAD_ALLOC;
    }

    for(int i = 0; i < n_cmds; i++){
        if(!fscanf(input, "%lg", cmd_sequence + i)){
            DEBUG cout << "Can not read command!\nLast correct command num = " << i << "." << endl;
            return READ_ERROR;
        }
    }

    return SUCCESS;
}



int Cpu::Run(char* file_name)
{
    CPU_ASSERT();

    double* cmd_sequence = nullptr;
    if(Cpu::FileRead(cmd_sequence, file_name) != SUCCESS){
        DEBUG cout << "Problems with file." << endl;

        CPU_ASSERT();
        return FILE_ERROR;
    }

    int cmd_num = 0;
    while(cmd_sequence[cmd_num] != END){
        cout << "Command num = " << cmd_num << endl;

        if(Cpu::Execute(cmd_sequence, cmd_num) == UNKNOWN_CMD){
            DEBUG cout << "!!! Unknown command!\n!!! Process terminated." << endl;

            CPU_ASSERT();
            return FATAL_ERROR;
        }
        cmd_num++;

        Cpu::PrintStack();
    }

    CPU_ASSERT();

    return SUCCESS;
}

int Cpu::Execute(double* cmd_sequence, int &cmd_num)
{
    CPU_ASSERT();

    if      (cmd_sequence[cmd_num] == PUSH){

        cmd_num++;
        Cpu::st.Push(&cmd_sequence[cmd_num]);

    }else if(cmd_sequence[cmd_num] == POP){

        cmd_num++;
        Cpu::st.Pop(&cmd_sequence[cmd_num]);

    }else if(cmd_sequence[cmd_num] == ADD){

        int res = Cpu::BinOp([] (MyType a, MyType b)-> MyType
                                    {
                                        return a + b;
                                    });
        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;


    }else if(cmd_sequence[cmd_num] == SUB){

        int res = Cpu::BinOp([] (MyType a, MyType b)-> MyType
                                    {
                                        return b - a;
                                    });
        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;


    }else if(cmd_sequence[cmd_num] == MUL){

        int res = Cpu::BinOp([] (MyType a, MyType b)-> MyType
                                    {
                                        return a * b;
                                    });
        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;


    }else if(cmd_sequence[cmd_num] == DIV){

        int res = Cpu::BinOp([] (MyType a, MyType b)-> MyType
                                    {
                                        return b / a;
                                    });
        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;


    }else if(cmd_sequence[cmd_num] == FSQRT){

        int res = Cpu::UnOp([] (MyType a)-> MyType
                                    {
                                        return std::sqrt(a);
                                    });
        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;


    }else if(cmd_sequence[cmd_num] == END){
        return END;
    }else{
        return  UNKNOWN_CMD;
    }

    CPU_ASSERT();

    return SUCCESS;
}

int Cpu::PrintStack()
{
    CPU_ASSERT();
    return st.PrintStack();
    CPU_ASSERT();
}



int Cpu::Ok()
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

