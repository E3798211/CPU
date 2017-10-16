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

    double* ram = new double [RAM_SIZE];
    int n_cmd   = 0;


    rewind(input);

    // =================================
    int err = Pass(input, &ram, &n_cmd);
    if(err != SUCCESS)
        return err;
    // =================================

    fprintf(output, "%s %d %d\n", GENUINE_SIGNATURE, GENUINE_VERSION, n_cmd);
    for(int i = 0; i < n_cmd; i++)
        fprintf(output, "%lg\n", ram[i]);

    fclose(input);
    fclose(output);

    return SUCCESS;
}


int Pass(FILE *input, double** ram, int* n_cmd)
{
    char   cmd[128] = "NOCOMMAND";
    double num      = -1;


    while(fscanf(input, "%s", cmd) > 0){

        if(*n_cmd >= RAM_SIZE){
            DEBUG cout << "Too much commands for the processor." << endl;
            return OVERFLOWN;
        }


        if      (!strcmp(cmd, CPUSH)){

            int push_where = 0;

            if(fscanf(input, "%lg", &num) == 0){
                if(fscanf(input, "%s", cmd) == 0){
                    DEBUG cout << "Invalid syntax: " << cmd << endl;
                    return FATAL_ERROR;
                }else{
                    if      (!strcmp(cmd, CAX))   push_where = AX;
                    else if (!strcmp(cmd, CBX))   push_where = BX;
                    else if (!strcmp(cmd, CCX))   push_where = CX;
                    else if (!strcmp(cmd, CDX))   push_where = DX;
                    else                          push_where = WRONG_COMMAND;

                    if(push_where == WRONG_COMMAND){
                        DEBUG cout << "Invalid syntax: " << cmd << endl;
                        return FATAL_ERROR;
                    }

                    // if we are here everything is ok

                    (*ram)[(*n_cmd)++] = PUSH;
                    (*ram)[(*n_cmd)++] = PUSH_TO_REG;

                    if      (push_where == AX)    (*ram)[(*n_cmd)++] = AX;
                    else if (push_where == BX)    (*ram)[(*n_cmd)++] = BX;
                    else if (push_where == CX)    (*ram)[(*n_cmd)++] = CX;
                    else if (push_where == DX)    (*ram)[(*n_cmd)++] = DX;
                }
            }else{
                (*ram)[(*n_cmd)++] = PUSH;
                (*ram)[(*n_cmd)++] = PUSH_TO_STK;
                (*ram)[(*n_cmd)++] = num;
            }


        }else if(!strcmp(cmd, CPOP)){
            //ram[n_cmd++] = POP;
            if(fscanf(input, "%s", cmd) == 0){
                DEBUG cout << "Invalid syntax: " << cmd << endl;
                return FATAL_ERROR;
            }

            int push_where = 0;

            if      (!strcmp(cmd, CAX))   push_where = AX;
            else if (!strcmp(cmd, CBX))   push_where = BX;
            else if (!strcmp(cmd, CCX))   push_where = CX;
            else if (!strcmp(cmd, CDX))   push_where = DX;
            else                          push_where = WRONG_COMMAND;

            if(push_where == WRONG_COMMAND){
                DEBUG cout << "Invalid syntax: " << cmd << endl;
                return FATAL_ERROR;
            }

            // if we are here everything is ok

            (*ram)[(*n_cmd)++] = POP;

            if      (push_where == AX)    (*ram)[(*n_cmd)++] = AX;
            else if (push_where == BX)    (*ram)[(*n_cmd)++] = BX;
            else if (push_where == CX)    (*ram)[(*n_cmd)++] = CX;
            else if (push_where == DX)    (*ram)[(*n_cmd)++] = DX;


        }else if(!strcmp(cmd, CADD)){
            (*ram)[(*n_cmd)++] = ADD;
        }else if(!strcmp(cmd, CSUB)){
            (*ram)[(*n_cmd)++] = SUB;
        }else if(!strcmp(cmd, CDIV)){
            (*ram)[(*n_cmd)++] = DIV;
        }else if(!strcmp(cmd, CMUL)){
            (*ram)[(*n_cmd)++] = MUL;
        }else if(!strcmp(cmd, CFSQRT)){
            (*ram)[(*n_cmd)++] = FSQRT;
        }else if(!strcmp(cmd, CSIN)){
            (*ram)[(*n_cmd)++] = SIN;
        }else if(!strcmp(cmd, CCOS)){
            (*ram)[(*n_cmd)++] = COS;

        }else if(!strcmp(cmd, COUT)){
            (*ram)[(*n_cmd)++] = OUT;
        }else if(!strcmp(cmd, CIN)){
            (*ram)[(*n_cmd)++] = IN;

        }else if(!strcmp(cmd, CJE)){
            if(fscanf(input, "%lg", &num)){
                (*ram)[(*n_cmd)++] = JE;
                (*ram)[(*n_cmd)++] = num;
            }else{
                DEBUG cout << "Expected num as " << n_cmd << " command" << endl;
            }

        }else if(!strcmp(cmd, CJNE)){
            if(fscanf(input, "%lg", &num)){
                (*ram)[(*n_cmd)++] = JNE;
                (*ram)[(*n_cmd)++] = num;
            }else{
                DEBUG cout << "Expected num as " << n_cmd << " command" << endl;
            }
        }else if(!strcmp(cmd, CJA)){
            if(fscanf(input, "%lg", &num)){
                (*ram)[(*n_cmd)++] = JA;
                (*ram)[(*n_cmd)++] = num;
            }else{
                DEBUG cout << "Expected num as " << n_cmd << " command" << endl;
            }
        }else if(!strcmp(cmd, CJAE)){
            if(fscanf(input, "%lg", &num)){
                (*ram)[(*n_cmd)++] = JAE;
                (*ram)[(*n_cmd)++] = num;
            }else{
                DEBUG cout << "Expected num as " << n_cmd << " command" << endl;
            }
        }else if(!strcmp(cmd, CJB)){
            if(fscanf(input, "%lg", &num)){
                (*ram)[(*n_cmd)++] = JB;
                (*ram)[(*n_cmd)++] = num;
            }else{
                DEBUG cout << "Expected num as " << n_cmd << " command" << endl;
            }
        }else if(!strcmp(cmd, CJBE)){
            if(fscanf(input, "%lg", &num)){
                (*ram)[(*n_cmd)++] = JBE;
                (*ram)[(*n_cmd)++] = num;
            }else{
                DEBUG cout << "Expected num as " << n_cmd << " command" << endl;
            }




        }else if(!strcmp(cmd, CEND)){
            (*ram)[(*n_cmd)++] = END;
        }else{
            DEBUG cout << "Invalid syntax: " << cmd << endl;
            return FATAL_ERROR;
        }
    }

    return SUCCESS;
}
