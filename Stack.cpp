#include "Stack.h"

// Private

int Stack::StackResize(long long int new_size)
{
    // Exceptions
    assert(new_size > 0);

    ASSERT();

    _size = new_size;

    MyType* new_stack = nullptr;
    try{
        new_stack = new MyType [new_size];
    }
    catch(const std::bad_alloc& ex){
        DEBUG cout << ERR_WHERE << ". Cannot allocate " << new_size << " bytes." << endl;
        ASSERT();
        return BAD_ALLOC;
    }

    new_stack[0]            = EDGE;

    long long int _min = (_n_elem < new_size)? _n_elem : new_size;

    for(long long int i = 1; i < _min + 1; i++)
        new_stack[i] = _stack[i];

    for(long long int i = _min + 1; i < new_size - 1; i++)
        new_stack[i] = EMPT;

    new_stack[new_size - 1] = EDGE;

    //Swap
    MyType* tmp = _stack;
    _stack = new_stack;
    new_stack = tmp;

    // Re-hash
    _hash = HashCount();

    //Clearing memory
    delete [] new_stack;
    new_stack = nullptr;

    ASSERT();
    return SUCCESS;
}

bool Stack::IsEdge(MyType elem)
{
    return (elem == EDGE)? true : false;
}

bool Stack::IsEmpt(MyType elem)
{
    return (elem == EMPT)? true : false;
}

// Public

Stack::Stack()
{
    ASSERT();

    _stack  = new MyType[3];

    _stack[0]   = EDGE;
    _stack[1]   = EMPT;
    _stack[2]   = EDGE;

    _size       = 3;
    _n_elem     = 0;
    _hash       = HashCount();

    ASSERT();
}

Stack::~Stack()
{
    ASSERT();

    if(_stack != nullptr){
        delete [] _stack;
        _stack  = nullptr;

        _size   = DELETED;
        _n_elem = DELETED;
        _hash   = HashCount();
    }

    ASSERT();
}

/*
// SHOULD BE CHECKED!!!

Stack::Stack(MyType* elements, int n_elements)
{
    //Exceptions
    assert(elements != nullptr);
    assert(n_elements > 0);

    int new_size = 1;
    while(new_size < n_elements)
        new_size *= 2;

    _stack  = elements;
    _size   = new_size;
    _n_elem = n_elements;
}

Stack::~Stack()
{
    if (_n_elem != 0){
        delete [] _stack;
        _stack = nullptr;
    }
}

int Stack::Push(MyType* new_elem)
{
    //Exceptions
    assert(new_elem != nullptr);


    // SHOULD BE CHECKED FOR BAD ALLOC IN StackResize()


    if(_n_elem >= _size){
        _size *= 2;
        StackResize(_size);
    }

    _stack[_n_elem] = *new_elem;
    _n_elem++;

    return SUCCESS;
}
*/

int Stack::Pop(MyType* pop_elem)
{
    //Exceptions
    assert(pop_elem != nullptr);

    ASSERT();

    if(_n_elem < 1){
        DEBUG cout << "Not enough elements in the stack" << endl;
        return NOT_ENOUGH_ELEMENTS;
    }


    *pop_elem = _stack[_n_elem];
    _stack[_n_elem] = EMPT;
    _n_elem--;

    // Re-hash
    _hash = HashCount();


    // SHOULD BE CHECKED FOR BAD ALLOC IN StackResize()


    bool resize_need = false;

    if(_n_elem < 2)
        resize_need = (_n_elem < (_size - 2)/ 2)? true : false;
    else
        resize_need = (_n_elem < (_size - 4)/ 2)? true : false;

    if(resize_need)
        StackResize((_size - 2)/ 2 + 2);


    ASSERT();
    return SUCCESS;
}

int Stack::Push(MyType* new_elem)
{
    //Exceptions
    assert(new_elem != nullptr);

    ASSERT();


    // SHOULD BE CHECKED FOR BAD ALLOC IN StackResize()


    if(_n_elem > MAX_SIZE){
        cout << "Too much elements already placed" << endl;
        return OVERFLOWN;
    }

    if(_n_elem >= (_size - 2))
        StackResize((_size - 2)*2 + 2);

    _stack[_n_elem + 1] = *new_elem;
    _n_elem++;

    // Re-hash
    _hash = HashCount();

    ASSERT();
    return SUCCESS;
}


// DEBUG

int Stack::HashCount()
{
    long long int check_hash = 0;
    check_hash = check_hash*2 + _size;
    check_hash = check_hash*2 + _n_elem;

    int i = 0;
    while(i < _size){
        if      (_stack[i] == EDGE)
            check_hash = check_hash*2 + EDGE_HASH;
        else if (_stack[i] == EMPT)
            check_hash = check_hash*2 + EMPT_HASH;
        else
            check_hash = check_hash*2 +  _stack[i];

        i++;
    }

    return check_hash;
}

int Stack::Ok()
{
    if(_edge_1 != EDGE)
        return FIRST_EDGE_BROKEN;
    if(_edge_2 != EDGE)
        return SCOND_EDGE_BROKEN;

    if(_hash != HashCount())
        return HASH_WRONG;

    return SUCCESS;
}

bool Stack::Dump(const char* func_name, int err_code)
{
    cout << endl;
    cout << "Dump() in " << func_name << "():" << endl;

    switch (err_code){
        case SUCCESS:
            /*Everything is OK, just call*/
            break;
        case FIRST_EDGE_BROKEN:
            cout << "!!! EDGE BROKEN"   << endl;
            break;
        case SCOND_EDGE_BROKEN:
            cout << "!!! EDGE BROKEN"   << endl;
            break;
        case HASH_WRONG:
            cout << "!!! WRONG HASH"    << endl;
            break;
    }

    if(_edge_1 != EDGE){
        cout << "First edge broken. Can not read further" << endl;
        return false;
    }
    if(_edge_2 != EDGE){
        cout << "Last edge broken. Can not read further" << endl;
        return false;
    }

    cout << "_size\t\t= "     << _size    << endl;
    cout << "_n_elem\t\t= "   << _n_elem  << endl;
    cout << "_hash\t\t= "     << _hash    << endl;

    if(_stack == nullptr){
        cout << "_stack\t\t= nullptr" << endl;
        cout << "No elements to print" << endl;
        return false;
    }

    if(_size < 3){
        cout << "_size < 3, wrong stack size" << endl;
        cout << "Can not print elements" << endl;
        return false;
    }

    cout << endl;
    for(int i = 0; i < _size; i++){
        cout << "_stack[" << i << "]\t= ";

        if      (IsEdge(_stack[i]))
            cout << "EDGE" << endl;

        else if (IsEmpt(_stack[i]))
            cout << "EMPTY" << endl;

        else
            cout << _stack[i] << endl;
    }

    return true;
}


