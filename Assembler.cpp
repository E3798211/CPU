#include "Assembler.h"

int FileRead(char* file_name1, char* file_name2)
{
    // Exceptions
    assert(file_name1 != nullptr);
    assert(file_name2 != nullptr);


    FILE *input = fopen(file_name1, "r");
    if(input == nullptr){
        DEBUG cout << "File " << file_name1 << " not found!" << endl;
        return FILE_NOT_FOUND;
    }
    FILE *output = fopen(file_name2, "w");
    if(output == nullptr){
        DEBUG cout << "File " << file_name2 << " not found!" << endl;
        return FILE_NOT_FOUND;
    }

    // Reading from input
    char   cmd[128] = "NOCOMMAND";
    double num      = -1;

    double ram[RAM_SIZE] = {0};     //  ?
    int    n_cmd    = 0;


    rewind(input);
    while(fscanf(input, "%s", cmd) > 0){

        if(n_cmd >= RAM_SIZE){
            DEBUG cout << "Too much commands for the processor." << endl;
            return OVERFLOWN;
        }


        if      (!strcmp(cmd, CPUSH)){
            if(fscanf(input, "%lg", &num) == 0){
                DEBUG cout << "Expected numeric symbol as " << n_cmd << " command." << endl;
                return FATAL_ERROR;
            }
            ram[n_cmd++] = PUSH;
            ram[n_cmd++] = num;

        }else if(!strcmp(cmd, CPOP)){
            ram[n_cmd++] = POP;
        }else if(!strcmp(cmd, CADD)){
            ram[n_cmd++] = ADD;
        }else if(!strcmp(cmd, CSUB)){
            ram[n_cmd++] = SUB;
        }else if(!strcmp(cmd, CDIV)){
            ram[n_cmd++] = DIV;
        }else if(!strcmp(cmd, CMUL)){
            ram[n_cmd++] = MUL;
        }else if(!strcmp(cmd, CFSQRT)){
            ram[n_cmd++] = FSQRT;
        }else if(!strcmp(cmd, CSIN)){
            ram[n_cmd++] = SIN;
        }else if(!strcmp(cmd, CCOS)){
            ram[n_cmd++] = COS;
        }else if(!strcmp(cmd, COUT)){
            ram[n_cmd++] = OUT;
        }else if(!strcmp(cmd, CIN)){
            ram[n_cmd++] = IN;


        }else if(!strcmp(cmd, CEND)){
            ram[n_cmd++] = END;
        }else{
            DEBUG cout << "Invalid syntax: " << cmd << endl;
            return FATAL_ERROR;
        }
    }

    fprintf(output, "%s %d %d\n", GENUINE_SIGNATURE, GENUINE_VERSION, n_cmd);
    for(int i = 0; i < n_cmd; i++)
        fprintf(output, "%lg\n", ram[i]);

    fclose(input);
    fclose(output);

    return SUCCESS;
}