#ifndef TDALISTA_H
#define TDALISTA_H
#include "node.h"

template<typename N>
class TDALISTA
{
public:
    TDALISTA()
    {
        length=0;
        beginning=0;
        ending=beginning;
        current = beginning;
    }

    int size()
    {
        return this->length;
    }

    N begin()
    {
        if(length > 0)
        {
            current = this->beginning;
            return this->beginning->element;
        }
        return N();
    }

    N end()
    {
        if(length > 0)
        {
            current = this->ending;
            return this->ending->element;
        }
        return N();
    }

    N next(int pos)
    {
        if(pos >= length-1 || pos < 0)
            return N();
        int posit = 0;
        Node<N>* pointer = beginning;
        while(posit < pos)
        {
            pointer = pointer->next;
            posit++;
        }
        pointer = pointer->next;
        current = pointer;
        return pointer->element;
    }

    N get(int pos)
    {
        if(pos>=length || pos<0)
            return N();
        int posit = 0;
        Node<N>* pointer = beginning;
        while(posit < pos)
        {
            pointer = pointer->next;
            posit++;
        }
        current = pointer;
        return pointer->element;
    }

    int add(N elem)
    {
        if(size() != 0)
        {
            ending->next = new Node<N>(elem);
            ending = ending->next;
            current = ending;
            length++;
        }else{
            Node<N>* newElement = new Node<N>(elem);
            beginning = newElement;
            ending = beginning;
            current = beginning;
            length++;
        }
        return 0;
    }

    int remove(int pos)
    {
        if(pos>=length || pos<0)
            return -1;
        int posit = 0;
        if(posit == pos){
            Node<N>* todelete = beginning;
            beginning = beginning->next;
            if(current == todelete)
                current = beginning;
            delete todelete;
            length--;
            return 0;
        }
        Node<N>* pointer = beginning;
        while(posit < pos-1)
        {
            pointer = pointer->next;
            posit++;
        }
        Node<N>* todelete = pointer->next;
        pointer->next = todelete->next;
        if(current == todelete)
            current = beginning;
        length--;
        delete todelete;
        return 0;
    }

    int insert(int pos, N elem)
    {
        if(pos>length || pos<0)
            return -1;
        Node<N>* newElement = new Node<N>(elem);
        Node<N>* pointer = beginning;
        int posit = 0;
        if(posit == pos){
            newElement->next = pointer;
            beginning = newElement;
            current = beginning;
            length++;
            return 0;
        }
        while(posit < pos-1)
        {
            pointer = pointer->next;
            posit++;
        }
        newElement->next = pointer->next;
        pointer->next = newElement;
        current = newElement;
        length++;
        return 0;
    }

    int empty()
    {
        Node<N>* tmp = beginning;
        beginning = 0;
        ending = 0;
        current = 0;
        length = 0;
        return empty(&tmp);
    }

    int empty(Node<N> **temp)
    {
        if(*temp == 0)
            return -1;
        Node<N>* tmp = (*temp)->next;
        delete *temp;
        if(tmp == 0)
            return 0;
        return empty(&tmp);
    }

    bool hasnext()
    {
        return current->next != 0;
    }

private:
    int length;
    Node<N>* beginning;
    Node<N>* ending;
    Node<N>* current;
};

#endif // TDALISTA_H
