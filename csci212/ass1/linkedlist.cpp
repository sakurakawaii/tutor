#include <iostream>
#include <string>
#include "linkedlist.h"
using namespace std;

linkedlist::linkedlist()
{
    head = NULL;
    listLength = 0;
}

string linkedlist::getUid(int pos)
{
    node * target = getNode(pos);
    return target->uid;
}
string linkedlist::getPid(int pos)
{
    node * target = getNode(pos);
    return target->pid;
}
string linkedlist::linkedlist::getPpid(int pos)
{
    node * target = getNode(pos);
    return target->ppid;
}
string linkedlist::getStime(int pos)
{
    node * target = getNode(pos);
    return target->stime;
}
string linkedlist::getTty(int pos)
{
    node * target = getNode(pos);
    return target->tty;
}
string linkedlist::getTime(int pos)
{
    node * target = getNode(pos);
    return target->time;
}
string linkedlist::getCmd(int pos)
{
    node * target = getNode(pos);
    return target->cmd;
}

void linkedlist::setUid(int pos, string aUid)
{
    node * target = getNode(pos);
    target->uid = aUid;
}
void linkedlist::setPid(int pos, string aPid)
{
    node * target = getNode(pos);
    target->pid = aPid;
}
void linkedlist::setPpid(int pos, string aPpid)
{
    node * target = getNode(pos);
    target->ppid = aPpid;
}
void linkedlist::setStime(int pos, string aStime)
{
    node * target = getNode(pos);
    target->stime = aStime;
}
void linkedlist::linkedlist::setTty(int pos, string aTty)
{
    node * target = getNode(pos);
    target->tty = aTty;
}
void linkedlist::setTime(int pos, string aTime)
{
    node * target = getNode(pos);
    target->time = aTime;
}
void linkedlist::setCmd(int pos, string aCmd)
{
    node * target = getNode(pos);
    target->cmd = aCmd;
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
void linkedlist::appendNode(string aUid, string aPid, string aPpid, string aStime, string aTty, string aTime, string aCmd)
{
    node * newNode = new node;
    newNode->uid = aUid;
    newNode->pid = aPid;
    newNode->ppid = aPpid;
    newNode->stime = aStime;
    newNode->tty = aTty;
    newNode->time = aTime;
    newNode->cmd = aCmd;
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
            head == NULL;
        }
        listLength = 0;
    }
}