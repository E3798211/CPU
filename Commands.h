#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

const int WRONG_COMMAND = -1000;

enum CMDS{
    END  = -1,
    PUSH = 1,
    POP,

    ADD,        // 3
    SUB,        // 4
    DIV,        // 5
    MUL,        // 6
    FSQRT,      // 7
    SIN,        // 8
    COS,        // 9

    OUT,        // 10
    IN,         // 11

    AX,         // 12
    BX,         // 13
    CX,         // 14
    DX,         // 15

    UNKNOWN_CMD
};

const int PUSH_TO_REG = 1;
const int PUSH_TO_STK = 0;

#define CEND     "end"
#define CPUSH    "push"
#define CPOP     "pop"
#define CADD     "add"
#define CSUB     "sub"
#define CDIV     "div"
#define CMUL     "mul"
#define CFSQRT   "fsqrt"
#define CSIN     "sin"
#define CCOS     "cos"
#define COUT     "out"
#define CIN      "in"
#define CAX       "ax"
#define CBX       "bx"
#define CCX       "cx"
#define CDX       "dx"



// 4 переменные в процессоре -> pop меняется
// push работает с регистрами - можно поменять номер команды в коде
// push 5   ==  1 0 5
// push dx  ==  1 1 4

#endif // COMMANDS_H_INCLUDED
