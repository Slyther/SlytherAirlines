#ifndef TDALISTA_H
#define TDALISTA_H
#include "node.h"

template<typename N>
class TDALISTA
{
public:
    TDALISTA()
    {
        length = 0;
        beginning = 0;
        ending = beginning;
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

    N next()
    {
        if(current == 0)
            return N();
        if(current->next == 0)
            return N();
        return current->next;
    }

    N get(int pos)
    {
        if(pos>=this->length || pos<0)
            return N();
        Node<N>* pointer = this->beginning;
        for(int i = 0; i < pos; i++, pointer = pointer->next);
        this->current = pointer;
        return pointer->element;
    }

    void add(N elem)
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

    void empty()
    {
        for(int i = size()-1; i >= 0; i--){
            remove(i);
        }
    }

    int indexOf(N elem)
    {
        for(int i = 0; i < this->length; i++){
            if(elem == this->get(i))
                return i;
        }
        return -1;
    }

    bool hasnext()
    {
        return this->current->next != 0;
    }

private:
    int length;
    Node<N>* beginning;
    Node<N>* ending;
    Node<N>* current;
};

#endif // TDALISTA_H
