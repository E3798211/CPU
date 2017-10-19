#include "Cpu.h"


long long int Cpu::HashCount()
{
    long long int _hash = 0;

    _hash += (uintptr_t)&st;
    _hash += (uintptr_t)&call_st;
    _hash += (uintptr_t)registers;

    if(registers != nullptr){
        for(int i = 0; i < 4; i++)
            _hash += registers[i];
    }

    return _hash;
}


int Cpu::FileRead(double** cmd_sequence, char* file_name)
{
    // Exceptions
    assert(file_name != nullptr);

    FILE *input = fopen(file_name, "r");
    if(input == nullptr){
        DEBUG cout << "File not found!" << endl;
        return FILE_NOT_FOUND;
    }


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
        *cmd_sequence = new double [n_cmds];
    }
    catch(const std::bad_alloc& ex){
        cout << ERR_WHERE << ". Cannot allocate " << n_cmds << " doubles." << endl;
        return BAD_ALLOC;
    }

    for(int i = 0; i < n_cmds; i++){
        if(!fscanf(input, "%lg", (*cmd_sequence) + i)){
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
    if(Cpu::FileRead(&cmd_sequence, file_name) != SUCCESS){
        DEBUG cout << "Unexpected problems with file." << endl;

        CPU_ASSERT();
        return FILE_ERROR;
    }

    int cmd_num = 0;
    while(cmd_sequence[cmd_num] != END){
        //cout << "Command num = " << cmd_num << endl;
        //cout << "\n";
        //cout << "// ================== GO" << endl;
        if(Cpu::Execute(cmd_sequence, cmd_num) == UNKNOWN_CMD){
            DEBUG cout << "!!! Unknown command!\n!!! Process terminated." << endl;
            DEBUG cout << "cmd_num = " << cmd_num << endl;

            CPU_ASSERT();
            return FATAL_ERROR;
        }
        cmd_num++;
        //cin.get();

        //Cpu::PrintRam();
        //Cpu::PrintRegisters();
        //Cpu::PrintStack();
        //Cpu::PrintCallStack();
    }

    //cout << "At the end:" << endl;
    //Cpu::PrintStack();
    //for(int i = 0; i < 4; i++)
        //cout << "reg[" << i << "] = " << registers[i] << endl;

    CPU_ASSERT();

    return SUCCESS;
}

int Cpu::Execute(double* cmd_sequence, int &cmd_num)
{
    CPU_ASSERT();

    if      (cmd_sequence[cmd_num] == PUSHNUM){
        cmd_num++;
        Cpu::st.Push(&cmd_sequence[cmd_num]);
    }else if(cmd_sequence[cmd_num] == PUSHREG){
        cmd_num++;

        int reg_num = -1;
        if      (cmd_sequence[cmd_num] == AX)     reg_num = 0;
        else if (cmd_sequence[cmd_num] == BX)     reg_num = 1;
        else if (cmd_sequence[cmd_num] == CX)     reg_num = 2;
        else if (cmd_sequence[cmd_num] == DX)     reg_num = 3;

        if(reg_num < 0){
            DEBUG cout << "Unknown command " << cmd_sequence[cmd_num] << endl;
            return UNKNOWN_CMD;
        }

        Cpu::st.Push(registers + reg_num);
        cpu_hash = HashCount();
    }else if(cmd_sequence[cmd_num] == PUSHRAM){
        cmd_num++;

        int place_in_ram = cmd_sequence[cmd_num];
        Cpu::st.Push(&ram[place_in_ram]);
    }else if(cmd_sequence[cmd_num] == PUSHRAMREG){
        cmd_num++;

        int reg_num = -1;
        if      (cmd_sequence[cmd_num] == AX)     reg_num = 0;
        else if (cmd_sequence[cmd_num] == BX)     reg_num = 1;
        else if (cmd_sequence[cmd_num] == CX)     reg_num = 2;
        else if (cmd_sequence[cmd_num] == DX)     reg_num = 3;

        if(reg_num < 0){
            DEBUG cout << "Unknown command " << cmd_sequence[cmd_num] << endl;
            return UNKNOWN_CMD;
        }

        int place_in_ram = registers[reg_num];
        Cpu::st.Push(&ram[place_in_ram]);

    }else if(cmd_sequence[cmd_num] == POPREG){
        cmd_num++;

        int reg_num = -1;
        if      (cmd_sequence[cmd_num] == AX)     reg_num = 0;
        else if (cmd_sequence[cmd_num] == BX)     reg_num = 1;
        else if (cmd_sequence[cmd_num] == CX)     reg_num = 2;
        else if (cmd_sequence[cmd_num] == DX)     reg_num = 3;

        if(reg_num < 0){
            DEBUG cout << "Unknown command " << cmd_sequence[cmd_num] << endl;
            return UNKNOWN_CMD;
        }

        double tmp = -1;
        if(Cpu::st.Pop(&tmp) == SUCCESS){
            Cpu::registers[reg_num] = tmp;
            cpu_hash = HashCount();
        }else{
            DEBUG cout << "Nothing have been pushed in register." << endl;
        }

    }else if(cmd_sequence[cmd_num] == POPRAM){
        cmd_num++;

        int place_in_ram = cmd_sequence[cmd_num];

        double tmp = -1;
        if(Cpu::st.Pop(&tmp) == SUCCESS){
            ram[place_in_ram] = tmp;
            cpu_hash = HashCount();
        }else{
            DEBUG cout << "Nothing have been pushed in RAM." << endl;
        }

    }else if(cmd_sequence[cmd_num] == POPRAMREG){
        cmd_num++;

        int reg_num = -1;
        if      (cmd_sequence[cmd_num] == AX)     reg_num = 0;
        else if (cmd_sequence[cmd_num] == BX)     reg_num = 1;
        else if (cmd_sequence[cmd_num] == CX)     reg_num = 2;
        else if (cmd_sequence[cmd_num] == DX)     reg_num = 3;

        if(reg_num < 0){
            DEBUG cout << "Unknown command " << cmd_sequence[cmd_num] << endl;
            return UNKNOWN_CMD;
        }

        int place_in_ram = registers[reg_num];
        double tmp = -1;
        if(Cpu::st.Pop(&tmp) == SUCCESS){
            ram[place_in_ram] = tmp;
            cpu_hash = HashCount();
        }else{
            DEBUG cout << "Nothing have been pushed in RAM." << endl;
        }

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


    }else if(cmd_sequence[cmd_num] == SIN){

        int res = Cpu::UnOp([] (MyType a)-> MyType
                                    {
                                        return std::sin(a);
                                    });
        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;


    }else if(cmd_sequence[cmd_num] == COS){

        int res = Cpu::UnOp([] (MyType a)-> MyType
                                    {
                                        return std::cos(a);
                                    });
        if(res == NOT_ENOUGH_ELEMENTS)
            cout << "\nNot enought elements in the stack" << endl;


    }else if(cmd_sequence[cmd_num] == OUT){

        if(Cpu::st.GetNElem() > 0){
            cout << "Last elem = " << Cpu::st.GetLastElem() << endl;
        }else
            cout << "Stack is empty" << endl;

    }else if(cmd_sequence[cmd_num] == IN){

        double tmp = 0;
        cout << "Enter: ";
        while(scanf("%lg", &tmp) == 0){
            cout << "Invalid input." << endl;
        }
        Cpu::st.Push(&tmp);

    }else if(cmd_sequence[cmd_num] == JE){
        //cout << "je\n";
        cmd_num++;
        Cpu::Jmp(&cmd_num, cmd_sequence[cmd_num], [] (MyType a, MyType b)
                                                        {
                                                            return (a == b);
                                                        });
    }else if(cmd_sequence[cmd_num] == JNE){
        //cout << "jne\n";
        cmd_num++;
        Cpu::Jmp(&cmd_num, cmd_sequence[cmd_num], [] (MyType a, MyType b)
                                                        {
                                                            return (a != b);
                                                        });

    }else if(cmd_sequence[cmd_num] == JA){
        //cout << "ja\n";
        cmd_num++;
        Cpu::Jmp(&cmd_num, cmd_sequence[cmd_num], [] (MyType a, MyType b)
                                                        {
                                                            return (a > b);
                                                        });

    }else if(cmd_sequence[cmd_num] == JAE){
        //cout << "jae\n";
        cmd_num++;
        Cpu::Jmp(&cmd_num, cmd_sequence[cmd_num], [] (MyType a, MyType b)
                                                        {
                                                            return (a >= b);
                                                        });

    }else if(cmd_sequence[cmd_num] == JB){
        //cout << "jb\n";
        cmd_num++;
        Cpu::Jmp(&cmd_num, cmd_sequence[cmd_num], [] (MyType a, MyType b)
                                                        {
                                                            return (a < b);
                                                        });

    }else if(cmd_sequence[cmd_num] == JBE){
        //cout << "jbe\n";
        cmd_num++;
        Cpu::Jmp(&cmd_num, cmd_sequence[cmd_num], [] (MyType a, MyType b)
                                                        {
                                                            return (a <= b);
                                                        });

    }else if(cmd_sequence[cmd_num] == CALL){
        double tmp = cmd_num + 2;
        call_st.Push(&tmp);                     // Remembering place where we should return return

        cmd_num++;
        cmd_num = cmd_sequence[cmd_num] - 1;    // (-1) because in the end of the loop cmd_num will be incremented
        //cout << "call to " << cmd_num << endl;

    }else if(cmd_sequence[cmd_num] == RET){
        double tmp = cmd_num;
        call_st.Pop(&tmp);
        cmd_num = tmp - 1;    // (-1) because in the end of the loop cmd_num will be incremented
    }



    else if(cmd_sequence[cmd_num] == END){
        return END;
    }else{
        DEBUG cout << "Unknown command " << cmd_sequence[cmd_num] << endl;
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
    if(cpu_hash != HashCount())
        return CPU_HASH_WRONG;

    return Cpu::st.Ok();
}

bool Cpu::Dump(const char* func_name, int err_code)
{
    cout << endl;
    cout << "Dump() in " << func_name << "():" << endl;

    if(err_code != CPU_HASH_WRONG){
        cout << "registers[0] = " << registers[0] << endl;
        cout << "registers[1] = " << registers[1] << endl;
        cout << "registers[2] = " << registers[2] << endl;
        cout << "registers[3] = " << registers[3] << endl;
    }
    return Cpu::st.Dump("Cpu::Dump", err_code);
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

int Cpu::Jmp(int* cmd_num, int jmp_to, bool (*pCompare)(MyType a, MyType b))
{
    CPU_ASSERT();

    MyType first  = 0;
    MyType second = 0;

    Cpu::st.Pop(&first);
    Cpu::st.Pop(&second);

    if(pCompare(second, first)){
        *(cmd_num) = jmp_to - 1;    // Because in the end of the loop command num will be incremented
        //cout << "jumped to " << jmp_to << endl;
    }else{
        //cout << "didn't jump" << endl;
        //exit(5);
    }


    CPU_ASSERT();

    return SUCCESS;
}


int Cpu::PrintRegisters()
{
    cout << "registers:" << endl;

    cout << "[0] =\t" << registers[0] << endl;
    cout << "[1] =\t" << registers[1] << endl;
    cout << "[2] =\t" << registers[2] << endl;
    cout << "[3] =\t" << registers[3] << endl;
}

int Cpu::PrintRam()
{
    cout << "Ram: " << endl;

    for(int i = 0; i < 10; i++)
        cout << "[" << i << "] = \t" << ram[i] << endl;
}

int Cpu::PrintCallStack()
{
    cout << "CallStack:" << endl;
    return call_st.PrintStack();
}

