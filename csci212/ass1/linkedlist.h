#include <string>
using namespace std;

#ifndef linkedlist_H
#define linkedlist_H

struct node
{
    string uid;
    string pid;
    string ppid;
    string stime;
    string tty;
    string time;
    string cmd;
    node * next;
};

class linkedlist
{
    private:
        node * head;
        int listLength;
    public:
        linkedlist();

        string getUid(int pos);
        string getPid(int pos);
        string getPpid(int pos);
        string getStime(int pos);
        string getTty(int pos);
        string getTime(int pos);
        string getCmd(int pos);

        void setUid(int pos, string aUid);
        void setPid(int pos, string aPid);
        void setPpid(int pos, string aPpid);
        void setStime(int pos, string aStime);
        void setTty(int pos, string aTty);
        void setTime(int pos, string aTime);
        void setCmd(int pos, string aCmd);

        bool isEmpty();
        int getLength();
        void appendNode(string aUid, string aPid, string aPpid, string aStime, string aTty, string aTime, string aCmd);
        node * getNode(int pos);
        void clearList();
};

#endif