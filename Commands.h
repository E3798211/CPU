#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

enum CMDS{
    END  = -1,
    PUSH = 1,
    POP,

    ADD,        // 3
    SUB,        // 4
    DIV,        // 5
    MUL,        // 6
    FSQRT,      // 7

    UNKNOWN_CMD
};

#endif // COMMANDS_H_INCLUDED
