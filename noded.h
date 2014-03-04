#ifndef NODED_H
#define NODED_H

template<typename n>
class noded
{
public:
    noded(n element);
    n element;
    noded<n>* next;
    noded<n>* previous;
};

#endif // NODED_H
