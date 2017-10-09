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

    for(int i = 0; i < n_cmds; i++)
        cout << cmd_sequence[i] << endl;

    return SUCCESS;
}


int Cpu::Run()
{
    /*
    int status = 1;
    while(status != -1){
        status = Cpu::Execute();
    }

    cout << "Runnig ended." << endl;

    return 0;
    */
    double* cmd_sequence = nullptr;
    if(Cpu::FileRead(cmd_sequence, "1.txt") != SUCCESS){
        DEBUG cout << "Problems with file." << endl;
        return FILE_ERROR;
    }

    int cmd_num = 0;
    while(cmd_sequence[cmd_num] != END){
        cout << "Cpu::Run" << endl;
    }
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

