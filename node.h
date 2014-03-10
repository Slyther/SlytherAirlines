#ifndef NODE_H
#define NODE_H

template<typename N>
    class Node
    {
    public:
        Node(N element)
        {
            this->element=element;
            this->next = 0;
        }

        N element;
        Node<N>* next;
    };
#endif // NODE_H
