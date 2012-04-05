#include <iostream>
#include <string>
#include "linkedlist.h"
using namespace std;

linkedlist::linkedlist()
{
    head = NULL;
    listLength = 0;
    totalFillWaitingTime = 0;
    totalPayWaitingTime = 0;
    idleTime = 0;
}


int linkedlist::getArrTime(int pos)
{
    node * target = getNode(pos);
    return target->arrTime;
}
char linkedlist::getFuelType(int pos)
{
    node * target = getNode(pos);
    return target->fuelType;
}
int linkedlist::linkedlist::getFillTime(int pos)
{
    node * target = getNode(pos);
    return target->fillTime;
}
int linkedlist::getPayTime(int pos)
{
    node * target = getNode(pos);
    return target->payTime;
}

char linkedlist::getStatus(int pos)
{
    node * target = getNode(pos);
    return target->status;
}
int linkedlist::getPumpNo(int pos)
{
    node * target = getNode(pos);
    return target->pumpNo;    
}

void linkedlist::setArrTime(int pos, int anArrTime)
{
    node * target = getNode(pos);
    target->arrTime = anArrTime;
}
void linkedlist::setFuelType(int pos, char aFuelType)
{
    node * target = getNode(pos);
    target->fuelType = aFuelType;
}
void linkedlist::setFillTime(int pos, int aFillTime)
{
    node * target = getNode(pos);
    target->fillTime = aFillTime;
}
void linkedlist::setPayTime(int pos, int aPayTime)
{
    node * target = getNode(pos);
    target->payTime = aPayTime;
}
void linkedlist::setStatus(int pos, char aStatus)
{
    node * target = getNode(pos);
    target->status = aStatus;
}
void linkedlist::setPumpNo(int pos, int aPumpNo)
{
    node * target = getNode(pos);
    target->pumpNo = aPumpNo;  
}

bool linkedlist::isEmpty()
{
    if (listLength == 0)
    {
        return true;
    }
    return false;
}

int linkedlist::getLength()
{
    return listLength;
}

bool linkedlist::isPaying()
{
    if (listLength == 0)
    {
        return false;
    }
    else
    {
        if (head->status == 'P' || head->status == 'Q')
        {
            return true;
        }
    }
    return false;
}

int linkedlist::getTotalFillWaitingTime()
{
    return totalFillWaitingTime;
}

int linkedlist::getTotalPayWaitingTime()
{
    return totalPayWaitingTime;
}

int linkedlist::getIdleTime()
{
    return idleTime;
}

void linkedlist::setTotalFillWaitingTime()
{

}

void linkedlist::setTotalPayWaitingTime()
{

}



void linkedlist::appendNode(int anArrTime, char aFuelType, int aFillTime, int aPayTime, int aStatus, int aPumpNo)
{
    node * newNode = new node;
    newNode->arrTime = anArrTime;
    newNode->fuelType = aFuelType;
    newNode->fillTime = aFillTime;
    newNode->payTime = aPayTime;
    newNode->status = aStatus;
    newNode->pumpNo = aPumpNo;
    newNode->next = NULL;
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        node * lastNode = getNode(listLength - 1);
        lastNode->next = newNode;
    }
    listLength++;
}

void linkedlist::deleteNode(int pos)
{
    if (listLength == 1)
    {
        head = NULL;
        listLength = 0;
    }
    else if (listLength > 1)
    {
        node * deleteTarget = (getNode(pos));
        if (pos == 0)
        {
            head = head->next;
        }
        else if (pos == listLength - 1)
        {
            (getNode(pos-1))->next = NULL;
        }
        else
        {
            (getNode(pos-1))->next = deleteTarget->next;
        }
        delete deleteTarget;
        listLength--;
    }
}


node * linkedlist::getNode(int pos)
{
    node * target = head;
    int cursor = 0;
    while (cursor != pos)
    {
        target = target->next;
        cursor++;
    }
    return target;
}

void linkedlist::clearList()
{
    if(!isEmpty())
    {
        node * deleteTarget = NULL;
        if (head != NULL)
        {
            while (head->next != NULL)
            {
                deleteTarget = head->next;
                head->next = deleteTarget->next;
                delete deleteTarget;
            }
            head = NULL;
        }
        listLength = 0;
    }
}