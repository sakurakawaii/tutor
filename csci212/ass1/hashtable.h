#include <string>
#include <vector>
#include "linkedlist.h"
using namespace std;

#ifndef hashtable_H
#define hashtable_H

class hashtable
{
    private:
        int tableSize;
        vector <string> users;
        vector <linkedlist> processList;
    public:
        hashtable(int size);

        void setUser(string aUser);

        int getSize();
        vector <string> getUserList();
        linkedlist getProcessList(string aUser);

        void setProcessList(int pos, string aUid, string aPid, string aPpid, string aStime, string aTty, string aTime, string aCmd);

        int findUser(string aUser);
};

#endif