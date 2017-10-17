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

    JE,         // 16   ==
    JNE,        // 17   !=
    JA,         // 18   >
    JAE,        // 19   >=
    JB,         // 20   <
    JBE,        // 21   <=

    CALL,       // 22
    RET,        // 23

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

#define CAX      "ax"
#define CBX      "bx"
#define CCX      "cx"
#define CDX      "dx"

#define CJE      "je"
#define CJNE     "jne"
#define CJA      "ja"
#define CJAE     "jae"
#define CJB      "jb"
#define CJBE     "jbe"

#define CCALL    "call"
#define CRET     "ret"

// =====================
// ASM - only

#define CLABEL   "label"

#endif // COMMANDS_H_INCLUDED
