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
        this->lastPathWeight = 0;
        this->lastIndexOfFrom = 0;
        this->lastIndexOfTo = 0;
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

    //if list->size() == 0, no path was available
    TDALISTA<N> * path(int indexOfFrom, int indexOfTo)
    {
        if(indexOfFrom == indexOfTo)
            return new TDALISTA<N>();
        Vertex<N>* curr = beginning;
        for(int i = 0; i < indexOfFrom; i++, curr = curr->next);
        if(curr->relations->size() == 0)
            return new TDALISTA<N>();
        TDALISTA< TDALISTA< Edge<N>* >* > *toHandle = new TDALISTA< TDALISTA< Edge<N>* >* >();
        TDALISTA< Edge<N>* >* workingPath = new TDALISTA<Edge<N>* >();
        for(int i = 0; i < curr->relations->size(); i++){
            buildPaths(workingPath, toHandle, curr->relations->get(i), indexOfTo);
        }
        int n1 = 2147483647, n2 = -1;
        for(int i = 0; i < toHandle->size(); i++){
            int x = 0;
            for(int j = 0; j < toHandle->get(i)->size(); j++){
                x += toHandle->get(i)->get(j)->value;
            }
            if(x < n1){
                n1 = x;
                n2 = i;
            }
        }
        if(n2 == -1)
            return new TDALISTA<N>();
        TDALISTA<N>* toReturn = new TDALISTA<N>();
        toReturn->add(toHandle->get(n2)->get(0)->from);
        for(int i = 0; i < toHandle->get(n2)->size(); i++){
            toReturn->add(toHandle->get(n2)->get(i)->to);
        }
        this->lastIndexOfFrom = indexOfFrom;
        this->lastIndexOfTo = indexOfTo;
        this->lastPathWeight = n1;
        return toReturn;
    }

    //if int == -1, no path was available
    int pathWeight(int indexOfFrom, int indexOfTo)
    {
        if(indexOfFrom == this->lastIndexOfFrom && indexOfTo == this->lastIndexOfTo){
            int toReturn = this->lastPathWeight;
            this->lastPathWeight = 0;
            this->lastIndexOfFrom = 0;
            this->lastIndexOfTo = 0;
            return toReturn;
        }
        if(isAdjacent(indexOfFrom, indexOfTo))
            return adjacencyValue(indexOfFrom, indexOfTo);
        Vertex<N>* curr = beginning;
        for(int i = 0; i < indexOfFrom; i++, curr = curr->next);
        if(curr->relations->size() == 0)
            return -1;
        TDALISTA< TDALISTA< Edge<N>* >* > *toHandle = new TDALISTA< TDALISTA< Edge<N>* >* >();
        TDALISTA< Edge<N>* >* workingPath = new TDALISTA<Edge<N>* >();
        for(int i = 0; i < curr->relations->size(); i++){
            buildPaths(workingPath, toHandle, curr->relations->get(i), indexOfTo);
        }
        int n1 = 2147483647, n2 = -1;
        for(int i = 0; i < toHandle->size(); i++){
            int x = 0;
            for(int j = 0; j < toHandle->get(i)->size(); j++){
                x += toHandle->get(i)->get(j)->value;
            }
            if(x < n1){
                x = n1;
                n2 = i;
            }
        }
        if(n2 == -1)
            return n2;
        return n1;
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

    void buildPaths(TDALISTA< Edge<N>* > * existingPath, TDALISTA< TDALISTA< Edge<N>* >* > *toHandle, Edge<N>* current, int indexOfTo)
    {
        for(int i = 0; i < existingPath->size(); i++){
            if(existingPath->get(i) == current)
                return;
        }
        TDALISTA< Edge<N>* >* newPath = new TDALISTA< Edge<N>* >();
        for(int i = 0; i < existingPath->size(); i++){
            newPath->add(existingPath->get(i));
        }
        newPath->add(current);
        if(current->to == get(indexOfTo)){
            toHandle->add(newPath);
            return;
        }
        Vertex<N>* curr = beginning;
        for(int i = 0; i < indexOf(current->to); i++, curr = curr->next);
        if(curr->relations->size() == 0){
            newPath->empty();
            delete newPath;
            return;
        }
        for(int i = 0; i < curr->relations->size(); i++){
            buildPaths(newPath, toHandle, curr->relations->get(i), indexOfTo);
        }
    }

    int length, lastPathWeight, lastIndexOfFrom, lastIndexOfTo;
    Vertex<N>* beginning;
    Vertex<N>* ending;
    Vertex<N>* current;
};

#endif // TDALISTAGRAFO_H
