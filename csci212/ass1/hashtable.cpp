#include <string>
#include <vector>
#include "linkedlist.h"
#include "hashtable.h"
using namespace std;

hashtable::hashtable(int size)
{
    tableSize = size;
    for (int i = 0; i < tableSize; i++)
    {
        linkedlist emptyList;
        users.push_back("");
        processList.push_back(emptyList);
    }

}


void hashtable::setUser(string aUser)
{
    int sumAscii = 0;
    int modRemainder;
    for (int i = 0; i < aUser.size(); i++)
    {
        sumAscii += (int)aUser[i];
    }

    modRemainder = sumAscii % tableSize;
    if (users[modRemainder] == "")
    {
        users[modRemainder] = aUser;
    }
    else
    {
        for (int i = 1; i <= tableSize; i++)
        {
            int secondModRemainder = (modRemainder + i) % tableSize;
            if (users[secondModRemainder] == "")
            {
                users[secondModRemainder] = aUser;
                break;
            }
        }
    }
}

int hashtable::getSize()
{
    return tableSize;
}

vector <string> hashtable::getUserList()
{
    return users;
}

linkedlist hashtable::getProcessList(string aUser)
{
    int pos = findUser(aUser);
    if (pos != -1)
    {
        return processList[pos];
    }
}

void hashtable::setProcessList(int pos, string aUid, string aPid, string aPpid, string aStime, string aTty, string aTime, string aCmd)
{
    processList[pos].appendNode(aUid, aPid, aPpid, aStime, aTty, aTime, aCmd);
}




int hashtable::findUser(string aUser)
{
    int sumAscii = 0;
    int modRemainder;
    for (int i = 0; i < aUser.size(); i++)
    {
        sumAscii += (int)aUser[i];
    }

    modRemainder = sumAscii % tableSize;
    if (users[modRemainder] == aUser)
    {
        return modRemainder;
    }
    else
    {
        for (int i = 1; i <= tableSize; i++)
        {
            int secondModRemainder = (modRemainder + i) % tableSize;
            if (users[secondModRemainder] == aUser)
            {
                return secondModRemainder;
            }
        }
    }
    return -1;
}