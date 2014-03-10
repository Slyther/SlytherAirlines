#ifndef EDGE_H
#define EDGE_H

template<typename N>
class Edge
{
public:
    Edge(N from, N to, int value)
    {
        this->from = from;
        this->to = to;
        this->value = value;
    }

    N from, to;
    int value;
};

#endif // EDGE_H
