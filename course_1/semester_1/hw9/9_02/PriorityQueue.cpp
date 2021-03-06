#include "PriorityQueue.h"

struct QueueElement
{
    int key;
    MapElement *value;
    QueueElement *next;
};

struct PriorityQueue
{
    QueueElement *minimal;
    int size;
};

QueueElement *createElement(int key, MapElement *value, QueueElement *next)
{
    QueueElement *newElem = new QueueElement;
    newElem->key = key;
    newElem->value = value;
    newElem->next = next;
    return newElem;
}

PriorityQueue *createPriorityQueue()
{
    PriorityQueue *newQueue = new PriorityQueue;
    newQueue->minimal = nullptr;
    newQueue->size = 0;
    return newQueue;
}

bool isEmpty(PriorityQueue *q)
{
    return q->size == 0;
}

void deletePriorityQueue(PriorityQueue *&q)
{
    if (q == nullptr)
        return;

    if (!isEmpty(q))
    {
        QueueElement *temp = q->minimal;

        while (temp != nullptr)
        {
            QueueElement *toDelete = temp;
            temp = temp->next;
            delete toDelete->value;
            delete toDelete;
        }
    }

    delete q;
    q = nullptr;
}

void insert(MapElement *value, PriorityQueue *q)
{
    int key = value->passedLength + value->toGoLength;

    QueueElement *newElem = createElement(key, value, q->minimal);

    if (isEmpty(q))
        q->minimal = newElem;
    else if (key <= q->minimal->key)
        q->minimal = newElem;
    else
    {
        QueueElement *temp = q->minimal;
        newElem->next = nullptr;

        if (temp->next == nullptr)
            temp->next = newElem;
        else
        {
            while (temp->next->next != nullptr && key > temp->next->key)
                temp = temp->next;

            if (key <= temp->next->key)
            {
                newElem->next = temp->next;
                temp->next = newElem;
            }
            else
                temp->next->next = newElem;
        }
    }

    q->size++;
}

MapElement *extractMin(PriorityQueue *q)
{
    if (isEmpty(q))
        return nullptr;

    MapElement *toReturn = q->minimal->value;

    QueueElement *toDelete = q->minimal;
    q->minimal = q->minimal->next;
    delete toDelete;

    q->size--;
    return toReturn;
}
