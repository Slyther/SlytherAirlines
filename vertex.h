#ifndef VERTEX_H
#define VERTEX_H
#include "tdalista.h"
#include "edge.h"

template<typename N>
class Vertex
{
public:
    Vertex(N element)
    {
        this->element = element;
        next = 0;
        relations = new TDALISTA< Edge<N>* >();
    }

    N element;
    Vertex<N>* next;
    TDALISTA< Edge<N>* >* relations;
};

#endif // VERTEX_H
