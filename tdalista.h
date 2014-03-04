#ifndef TDALISTA_H
#define TDALISTA_H
#include "noded.h"

template<typename nvalue>
class TDALISTA
{
public:
    TDALISTA();
    int size();
    nvalue begin();
    nvalue end();
    nvalue next(int pos);
    nvalue get(int pos);
    int add(nvalue elem);
    int remove(int pos);
    int insert(int pos, nvalue elem);
    int indexOf(nvalue elem);
    int empty();
    bool hasnext();
    int swap(int t1, int t2);

private:
    int length;
    noded<nvalue>* beginning;
    noded<nvalue>* ending;
    noded<nvalue>* current;
    int empty(noded<nvalue> **temp);
};

#endif // TDALISTA_H
