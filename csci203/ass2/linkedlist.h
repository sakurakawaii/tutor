#include <string>
using namespace std;

#ifndef linkedlist_H
#define linkedlist_H

struct node //car
{
    int arrTime; //in seconds
    char fuelType;
    int fillTime;
    int payTime;
    char status;//P--paying, F--filling, W--waiting to fill, Q--leave to pay, A--just arrived, initial status
    int pumpNo;  
    node * next;
};

class linkedlist
{
    private:
        node * head;
        int listLength;
        int totalFillWaitingTime;
        int totalPayWaitingTime;
        int idleTime;
    public:
        linkedlist();

        int getArrTime(int pos);
        char getFuelType(int pos);
        int getFillTime(int pos);
        int getPayTime(int pos);
        char getStatus(int pos);
        int getPumpNo(int pos);

        void setArrTime(int pos, int anArrTime);
        void setFuelType(int pos, char aFuelType);
        void setFillTime(int pos, int aFillTime);
        void setPayTime(int pos, int aPayTime);
        void setStatus(int pos, char aStatus);
        void setPumpNo(int pos, int aPumpNo);

        bool isEmpty();
        int getLength();
        bool isPaying();
        int getTotalFillWaitingTime();
        int getTotalPayWaitingTime();
        int getIdleTime();
        void setTotalFillWaitingTime();
        void setTotalPayWaitingTime();
        void appendNode(int anArrTime, char aFuelType, int aFillTime, int aPayTime, int aStatus, int aPumpNo);
        void deleteNode(int pos);
        node * getNode(int pos);
        void clearList();
};

#endif