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

#define CEND     "end"
#define CPUSH    "push"
#define CPOP     "pop"
#define CADD     "add"
#define CSUB     "sub"
#define CDIV     "div"
#define CMUL     "mul"
#define CFSQRT   "FSQRT"

// out  - печать последнего числа
// in   - ввод с клавиатуры
// sin
// cos

// 4 переменные в процессоре -> pop меняется
// push работает с регистрами - можно поменять номер команды в коде
// push 5   ==  1 0 5
// push dx  ==  1 1 4

#endif // COMMANDS_H_INCLUDED
