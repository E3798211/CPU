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



    if(fseek(input, 0, SEEK_END)){
        DEBUG cout << "Can not set last position in " << file_name1 << endl;
        return FILE_POS_ERROR;
    }

    int file_size = ftell(input);
    if(file_size == EOF){
        cout << "Can not get pointer's position in " << file_name1 << endl;
        return FILE_POS_ERROR;
    }

    // Reading from input
    char   cmd[128] = "NOCOMMAND";
    double num      = -1;
    int    n_cmd    = 0;

    // Empty string is left first - it will be filled at the end when we know amount of commands
    fprintf(output, "%s", "                     \n");

    rewind(input);
    while(fscanf(input, "%s", cmd) > 0){
        if      (!strcmp(cmd, CPUSH)){
            if(fscanf(input, "%lg", &num) == 0){
                DEBUG cout << "Expected numeric symbol on " << /*ftell(input)*/n_cmd << " position." << endl;
                return FATAL_ERROR;
            }
            fprintf(output, "%d %lg\n", PUSH, num);
            n_cmd++;

        }else if(!strcmp(cmd, CPOP)){
            /*
            if(fscanf(input, "%lg", &num) == 0){
                DEBUG cout << "Expected numeric symbol on " << /n_cmd << " position." << endl;
                return FATAL_ERROR;
            }
            */
            fprintf(output, "%d\n", POP);
            /*
            n_cmd++;
            */

        }else if(!strcmp(cmd, CADD)){
            fprintf(output, "%d\n", ADD);
        }else if(!strcmp(cmd, CSUB)){
            fprintf(output, "%d\n", SUB);
        }else if(!strcmp(cmd, CDIV)){
            fprintf(output, "%d\n", DIV);
        }else if(!strcmp(cmd, CMUL)){
            fprintf(output, "%d\n", MUL);
        }else if(!strcmp(cmd, CFSQRT)){
            fprintf(output, "%d\n", FSQRT);
        }else if(!strcmp(cmd, CEND)){
            fprintf(output, "%d\n", END);
        }else{
            DEBUG cout << "Oops" << endl;
            return FATAL_ERROR;
        }

        //cout << "11" << endl;
        n_cmd++;
    }

    //Writing first line
    fseek(output, 0, SEEK_SET);


    // VERSION


    fprintf(output, "EK %d %d", 1, n_cmd);

    return SUCCESS;
}
