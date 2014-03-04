#include "noded.h"

template<typename n>
noded<n>::noded(n element)
{
    this->element = element;
    this->next = 0;
    this->previous = 0;
}
