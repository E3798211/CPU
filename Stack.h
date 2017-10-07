#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "Errors.h"

#include <iostream>
#include <assert.h>


// DEBUG
//=================================================================
// Comment next line if you want to turn debug off
#define _DEBUG

#if defined (_DEBUG)
    #define DEBUG
#else
    #define DEBUG if(0)
#endif // defined

//=================================================================


#define ERR_WHERE "In " << __FILE__ << ": " << __func__ << "(): " << ex.what()


#define ASSERT()  {                                         \
            int err = Stack::Ok();                          \
            if(err != SUCCESS){                             \
                Stack::Dump(__func__, err);                 \
                assert (0);                                 \
            }                                               \
        }

/// Type of data to be saved in stack
typedef double MyType;

const MyType EDGE   = 123456789;
const MyType EMPT   = 987654321;
const int DELETED   = -1;

const int EDGE_HASH = 1;
const int EMPT_HASH = 2;

const long long int MAX_SIZE = 10000000000;

/// Stack class
class Stack {
private:
    /// First canary
    int _edge_1 = EDGE;

    /// Current size
    long long int _size   = 0;

    /// Current amount of elements in stack
    long long int _n_elem = 0;

    /// Array that contains elements
    MyType* _stack = nullptr;

    /// Resizing stack
    /**
        \param new_size     New size of the stack
    */
    int StackResize(long long int new_size);

    // Hash :)
    long long int _hash = 0;

    /// Hash-counter
    int HashCount();

public:
    /// Default constructor
    Stack();
//  Stack(MyType* elements, int n_elements);

    /// Destructor
    ~Stack();

    /// Pop element
    int Pop(MyType* pop_elem);

    /// Push element
    /**
        \param [in] new_elem    New element in stack.
    */
    int Push(MyType* new_elem);

    long long int GetSize();
    long long int GetNElem();



    // DEBUG
    bool IsEdge(MyType elem);
    bool IsEmpt(MyType elem);

    // Verifier
    int  Ok();

    bool Dump(const char* func_name = __func__, int err_code = SUCCESS);

    // Print elements
    int PrintStack();
private:
    /// Last canary
    int _edge_2 = EDGE;
};


using std::cout;
using std::cin;
using std::endl;

#endif // STACK_H_INCLUDED
