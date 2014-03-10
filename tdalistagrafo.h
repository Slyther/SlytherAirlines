#ifndef TDALISTAGRAFO_H
#define TDALISTAGRAFO_H
#include "vertex.h"
#include "edge.h"
#include "tdalista.h"

template<typename N>
class TDALISTAGRAFO
{
public:
    TDALISTAGRAFO()
    {
        this->length = 0;
        this->beginning = 0;
        this->ending = this->beginning;
        this->current = this->beginning;
    }

    int size()
    {
        return this->length;
    }

    N begin()
    {
        if(this->length > 0)
        {
            this->current = this->beginning;
            return this->beginning->element;
        }
        return N();
    }

    N end()
    {
        if(this->length > 0)
        {
            this->current = this->ending;
            return this->ending->element;
        }
        return N();
    }

    N get(int pos)
    {
        if(pos>=this->length || pos<0)
            return N();
        int posit = 0;
        Vertex<N>* pointer = this->beginning;
        while(posit < pos)
        {
            pointer = pointer->next;
            posit++;
        }
        this->current = pointer;
        return pointer->element;
    }

    int add(N elem)
    {
        if(this->size() != 0)
        {
            this->ending->next = new Vertex<N>(elem);
            this->ending = this->ending->next;
            this->current = this->ending;
            this->length++;
        }else{
            Vertex<N>* newElement = new Vertex<N>(elem);
            this->beginning = newElement;
            this->ending = this->beginning;
            this->current = this->beginning;
            this->length++;
        }
        return 0;
    }

    int addEdge(int indexOfFrom, int indexOfTo, int value)
    {
        N from = this->get(indexOfFrom);
        N to = this->get(indexOfTo);
        if(from == N() || to == N())
            return -1;
        Vertex<N>* VFrom = this->beginning;
        Vertex<N>* VTo = this->beginning;
        for(int i = 0; i < indexOfFrom; i++, VFrom = VFrom->next);
        for(int i = 0; i < indexOfTo; i++, VTo = VTo->next);
        VFrom->relations->add(new Edge<N>(VFrom->element, VTo->element, value));
        return 0;
    }

    int removeEdge(int indexOfFrom, int indexOfTo)
    {
        N from = this->get(indexOfFrom);
        N to = this->get(indexOfTo);
        if(from == N() || to == N())
            return -1;
        Vertex<N>* VFrom = this->beginning;
        Vertex<N>* VTo = this->beginning;
        for(int i = 0; i < indexOfFrom; i++, VFrom = VFrom->next);
        for(int i = 0; i < indexOfTo; i++, VTo = VTo->next);
        for(int i = 0; i < VFrom->relations->size(); i++){
            if(VFrom->relations->get(i)->to == VTo->element){
                VFrom->relations->remove(i);
                return 0;
            }
        }
        return -1;
    }

    bool isAdjacent(int indexOfFrom, int indexOfTo)
    {
        N from = this->get(indexOfFrom);
        N to = this->get(indexOfTo);
        if(from == N() || to == N())
            return false;
        Vertex<N>* VFrom = this->beginning;
        Vertex<N>* VTo = this->beginning;
        for(int i = 0; i < indexOfFrom; i++, VFrom = VFrom->next);
        for(int i = 0; i < indexOfTo; i++, VTo = VTo->next);
        for(int i = 0; i < VFrom->relations->size(); i++){
            if(VFrom->relations->get(i)->to == VTo->element)
                return true;
        }
        return false;
    }

    int adjacencyValue(int indexOfFrom, int indexOfTo)
    {
        if(isAdjacent(indexOfFrom, indexOfTo)){
            Vertex<N>* VFrom = this->beginning;
            Vertex<N>* VTo = this->beginning;
            for(int i = 0; i < indexOfFrom; i++, VFrom = VFrom->next);
            for(int i = 0; i < indexOfTo; i++, VTo = VTo->next);
            for(int i = 0; i < VFrom->relations->size(); i++){
                if(VFrom->relations->get(i)->to == VTo->element)
                    return VFrom->relations->get(i)->value;
            }
        }
        return -1;
    }

    bool hasPath(int indexOfFrom, int idexOfTo)
    {
        return true;
    }

    TDALISTA<N> * path(int indexOfFrom, int indexOfTo)
    {
        TDALISTA<N> *toReturn = new TDALISTA<N>();
        return toReturn;
    }

    int pathWeight(int indexOfFrom, int indexOfTo)
    {
        int toReturn = 0;
    }

    int remove(int pos)
    {
        if(pos>=this->length || pos<0)
            return -1;
        int posit = 0;
        if(posit == pos){
            Vertex<N>* todelete = this->beginning;
            Vertex<N>* tmp = this->beginning;
            while(tmp->next != 0){
                for(int i = 0; i < tmp->relations->size(); i++){
                    if(tmp->relations->get(i)->to == todelete->element)
                        return -1;
                }
                tmp = tmp->next;
            }
            this->beginning = this->beginning->next;
            if(this->current == todelete)
                this->current = this->beginning;
            delete todelete;
            this->length--;
            return 0;
        }
        Vertex<N>* pointer = this->beginning;
        while(posit < pos-1)
        {
            pointer = pointer->next;
            posit++;
        }
        Vertex<N>* todelete = pointer->next;
        Vertex<N>* tmp = this->beginning;
        while(tmp->next != 0){
            for(int i = 0; i < tmp->relations->size(); i++){
                if(tmp->relations->get(i)->to == todelete->element)
                    return -1;
            }
            tmp = tmp->next;
        }
        pointer->next = todelete->next;
        if(this->current == todelete)
            this->current = this->beginning;
        this->length--;
        delete todelete;
        return 0;
    }

    int empty()
    {
        Vertex<N>* tmp = this->beginning;
        this->beginning = 0;
        this->ending = 0;
        this->current = 0;
        this->length = 0;
        return this->empty(&tmp);
    }

    int empty(Vertex<N> **temp)
    {
        if(*temp == 0)
            return -1;
        Vertex<N>* tmp = (*temp)->next;
        delete *temp;
        if(tmp == 0)
            return 0;
        return this->empty(&tmp);
    }

    int indexOf(N elem)
    {
        int n = -1;
        for(int i = 0; i < this->length; i++){
            n = i;
            if(elem == this->get(i))
                return n;
        }
        return -1;
    }

    bool hasnext()
    {
        return this->current->next != 0;
    }

private:
    int length;
    Vertex<N>* beginning;
    Vertex<N>* ending;
    Vertex<N>* current;
};

#endif // TDALISTAGRAFO_H
