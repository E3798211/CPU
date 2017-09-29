#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Stack.h"



const int CMD_SEQ_LEN = 5;


const int PUSH  = 1;
const int POP   = 2;


int CmdArgument (const char* cmd);

int main()
{
    Stack st;
    while(1){
        char cmd[20] = "";
        MyType cmd_arg  = 0;

        cout << "Enter command: ";
        cin >> cmd >> cmd_arg;

        if      (!strcmp(cmd, "push")){
            st.Push(&cmd_arg);
            st.Dump();
        }else if(!strcmp(cmd, "pop")){
            st.Pop(&cmd_arg);
            st.Dump();
        }
    }
}
