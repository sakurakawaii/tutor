#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "linkedlist.h"
using namespace std;

int convertTimeToSec(string formattedTime);
void updatePumpStatus (linkedlist &pump, linkedlist &payment);
int minimal (int a, int b);
int getFuelTypeIndex(char fuelType);

int main()
{


    ifstream fin;
    char fname[50];
    
    cout<< "Please enter the file name." << endl;
    cin >> fname;
    cout << "Simulation start" << endl;
    
    fin.open(fname);
    if(!fin.is_open())
    {
        cerr << "Can't open file" << endl;
        return -1;
    }
    
    linkedlist allCars;
    linkedlist pump1;//92
    linkedlist pump2;//92
    linkedlist pump3;//92,95,98
    linkedlist pump4;//92,95,98
    linkedlist pump5;//diesel
    linkedlist pump6;//LPG
    linkedlist payment;

    string formattedArrTime = "";
    char fuelType = ' ';
    int fillTime = 0;
    int payTime = 0;
    int time = 0;

    //For total time simulated report
    int firstArrTime = 0;
    int lastDepTime = 0;
    int totalSimulateTime = 0;
    //For each different type of fuel report
    float avgQueueLength[5] = {0, 0, 0, 0, 0};//92,95,98,diesel,LPG
    float avgTimeInQueue[5] = {0, 0, 0, 0, 0};
    float avgTimeInService[5] = {0, 0, 0, 0, 0};
    int numberOfCarsServed[5] = {0, 0, 0, 0, 0};
    int numberOfCarsLeft[5] = {0, 0, 0, 0, 0};
    //For each pump report
    int totalIdleTime[6] = {0, 0, 0, 0, 0, 0};//pump1, pump2, pump3, pump4, pump5, pump6

    //store all cars
    while(fin>>formattedArrTime && fin>>fuelType && fin>>fillTime && fin>>payTime)
    {
        int arrTime;
        arrTime = convertTimeToSec(formattedArrTime);       
        allCars.appendNode(arrTime, fuelType, fillTime, payTime, 'A', 0);
    }
    //Debug: For output allCars
    //for (int i = 0; i < allCars.getLength(); i++)
    //{
    //   cout<<allCars.getArrTime(i)<<" "<<allCars.getFuelType(i)<<" "<<allCars.getFillTime(i)<<" "<<allCars.getPayTime(i)<<endl;
    //}



    //Simulation starts
    firstArrTime = allCars.getArrTime(0);
    int t = firstArrTime;
    while(!allCars.isEmpty() || !pump1.isEmpty() || !pump2.isEmpty() || !pump3.isEmpty() || !pump4.isEmpty() || !pump5.isEmpty() || !pump6.isEmpty() || !payment.isEmpty())
    {

        //Payment Queue update
        if (payment.getLength() > 0)
        {
            //check first customer in payment queue is waiting to pay or not
            if (payment.getStatus(0) == 'Q')
            {
                payment.setStatus(0, 'P');//change status to paying
                payment.setPayTime(0, (payment.getPayTime(0) - 1));//decrease paytime by 1
            }
            else if (payment.getStatus(0) == 'P')
            {
                payment.setPayTime(0, (payment.getPayTime(0) - 1));//decrease payment by 1
            }
            //check first customer is done payment or not
            if (payment.getPayTime(0) == 0)
            {
                //remove the car when it finishes the payment
                int tempPumpNo = payment.getPumpNo(0);
                switch (tempPumpNo)
                {
                    case 1:
                        pump1.deleteNode(0);
                        numberOfCarsServed[0]++;
                        break;
                    case 2:
                        pump2.deleteNode(0);
                        numberOfCarsServed[0]++;
                        break;
                    case 3:
                        numberOfCarsServed[getFuelTypeIndex(pump3.getFuelType(0))]++;
                        pump3.deleteNode(0);
                        break;
                    case 4:
                        numberOfCarsServed[getFuelTypeIndex(pump4.getFuelType(0))]++;
                        pump4.deleteNode(0);
                        break;
                    case 5:
                        pump5.deleteNode(0);
                        numberOfCarsServed[3]++;
                        break;
                    case 6:
                        pump6.deleteNode(0);
                        numberOfCarsServed[4]++;
                        break;
                    default:
                        break;
                }
                payment.deleteNode(0);
            }
        }


        //Pump Queue update
        updatePumpStatus (pump1, payment);
        updatePumpStatus (pump2, payment);
        updatePumpStatus (pump3, payment);
        updatePumpStatus (pump4, payment);
        updatePumpStatus (pump5, payment);
        updatePumpStatus (pump6, payment);

        //New car come in, set status
        if(!allCars.isEmpty())
        {
            if(allCars.getArrTime(0) == t)
            {
                if (allCars.getFuelType(0) == '2')
                {
                    int shortestQueue = minimal(minimal((minimal(pump3.getLength(), pump4.getLength())), pump1.getLength()), pump2.getLength());
                    if (shortestQueue == 4)
                    {
                        numberOfCarsLeft[0]++;
                    }
                    else
                    {
                        if (pump1.getLength() == shortestQueue)
                        {
                            pump1.appendNode(allCars.getArrTime(0), allCars.getFuelType(0), allCars.getFillTime(0), allCars.getPayTime(0), 'W', 1);
                        }
                        else if (pump2.getLength() == shortestQueue)
                        {
                            pump2.appendNode(allCars.getArrTime(0), allCars.getFuelType(0), allCars.getFillTime(0), allCars.getPayTime(0), 'W', 2);
                        }
                        else if (pump3.getLength() == shortestQueue)
                        {
                            pump3.appendNode(allCars.getArrTime(0), allCars.getFuelType(0), allCars.getFillTime(0), allCars.getPayTime(0), 'W', 3);
                        }
                        else if (pump4.getLength() == shortestQueue)
                        {
                            pump4.appendNode(allCars.getArrTime(0), allCars.getFuelType(0), allCars.getFillTime(0), allCars.getPayTime(0), 'W', 4);
                        }
                    }
                }
                else if (allCars.getFuelType(0) == '5')
                {
                    int shortestQueue = minimal(pump3.getLength(), pump4.getLength());
                    if (shortestQueue == 4)
                    {
                        numberOfCarsLeft[1]++;
                    }
                    else
                    {
                        if (pump3.getLength() == shortestQueue)
                        {
                            pump3.appendNode(allCars.getArrTime(0), allCars.getFuelType(0), allCars.getFillTime(0), allCars.getPayTime(0), 'W', 3);
                        }
                        else if (pump4.getLength() == shortestQueue)
                        {
                            pump4.appendNode(allCars.getArrTime(0), allCars.getFuelType(0), allCars.getFillTime(0), allCars.getPayTime(0), 'W', 4);
                        }
                    }
                }
                else if (allCars.getFuelType(0) == '8')
                {
                    int shortestQueue = minimal(pump3.getLength(), pump4.getLength());
                    if (shortestQueue == 4)
                    {
                        numberOfCarsLeft[2]++;
                    }
                    else
                    {
                        if (pump3.getLength() == shortestQueue)
                        {
                            pump3.appendNode(allCars.getArrTime(0), allCars.getFuelType(0), allCars.getFillTime(0), allCars.getPayTime(0), 'W', 3);
                        }
                        else if (pump4.getLength() == shortestQueue)
                        {
                            pump4.appendNode(allCars.getArrTime(0), allCars.getFuelType(0), allCars.getFillTime(0), allCars.getPayTime(0), 'W', 4);
                        }
                    }
                }
                else if (allCars.getFuelType(0) == 'd')
                {
                    if (pump5.getLength() == 4)//leave
                    {
                        numberOfCarsLeft[3]++;
                    }
                    else
                    {
                        pump5.appendNode(allCars.getArrTime(0), allCars.getFuelType(0), allCars.getFillTime(0), allCars.getPayTime(0), 'W', 5);
                    }
                }
                else if (allCars.getFuelType(0) == 'l')
                {
                    if (pump6.getLength() == 4)//leave
                    {
                        numberOfCarsLeft[4]++;
                    }
                    else
                    {
                        pump6.appendNode(allCars.getArrTime(0), allCars.getFuelType(0), allCars.getFillTime(0), allCars.getPayTime(0), 'W', 6);
                    }
                }
                allCars.deleteNode(0);
            }
        }

        //Update Report
        //Pump Empty
        if (pump1.isEmpty())
        {
            totalIdleTime[0]++;
        }
        else
        {
            if (pump1.getStatus(0) == 'Q' || pump1.getStatus(0) == 'W')
            {
                totalIdleTime[0]++;
            }
        }

        if (pump2.isEmpty())
        {
            totalIdleTime[1]++;
        }
        else
        {
            if (pump2.getStatus(0) == 'Q' || pump2.getStatus(0) == 'W')
            {
                totalIdleTime[1]++;
            }
        }
        if (pump3.isEmpty())
        {
            totalIdleTime[2]++;
        }
        else
        {
            if (pump3.getStatus(0) == 'Q' || pump3.getStatus(0) == 'W')
            {
                totalIdleTime[2]++;
            }      
        }
        if (pump4.isEmpty())
        {
            totalIdleTime[3]++;
        }
        else
        {
            if (pump4.getStatus(0) == 'Q' || pump4.getStatus(0) == 'W')
            {
                totalIdleTime[3]++;
            }      
        }
        if (pump5.isEmpty())
        {
            totalIdleTime[4]++;
        }
        else
        {
            if (pump5.getStatus(0) == 'Q' || pump5.getStatus(0) == 'W')
            {
                totalIdleTime[4]++;
            }      
        }
        if (pump6.isEmpty())
        {
            totalIdleTime[5]++;
        }
        else
        {
            if (pump6.getStatus(0) == 'Q' || pump6.getStatus(0) == 'W')
            {
                totalIdleTime[5]++;
            }      
        }

        float queueLengthThisSec[5] = {0, 0, 0, 0, 0};//92,95,98,diesel,LPG
        float timeInQueueThisSec[5] = {0, 0, 0, 0, 0};
        float timeInServiceThisSec[5] = {0, 0, 0, 0, 0};
        for (int i = 0; i < pump1.getLength(); i++)
        {
            if (pump1.getStatus(i) == 'W')
            {
                queueLengthThisSec[0]++;
                timeInQueueThisSec[0]++;
                timeInServiceThisSec[0]++;
            }
            else if (pump1.getStatus(i) == 'F')
            {
                timeInServiceThisSec[0]++;
            }
        }
        for (int i = 0; i < pump2.getLength(); i++)
        {
            if (pump2.getStatus(i) == 'W')
            {
                queueLengthThisSec[0]++;
                timeInQueueThisSec[0]++;
                timeInServiceThisSec[0]++;
            }
            else if (pump2.getStatus(i) == 'F')
            {
                timeInServiceThisSec[0]++;
            }
        }
        for (int i = 0; i < pump3.getLength(); i++)
        {
            if (pump3.getStatus(i) == 'W')
            {
                queueLengthThisSec[getFuelTypeIndex(pump3.getFuelType(i))]++;
                timeInQueueThisSec[getFuelTypeIndex(pump3.getFuelType(i))]++;
                timeInServiceThisSec[getFuelTypeIndex(pump3.getFuelType(i))]++;
            }
            else if (pump3.getStatus(i) == 'F')
            {
                timeInServiceThisSec[getFuelTypeIndex(pump3.getFuelType(i))]++;
            }
            //numberOfCarsServed[getFuelTypeIndex(pump3.getFuelType(0))]++;
        }
        for (int i = 0; i < pump4.getLength(); i++)
        {
            if (pump4.getStatus(i) == 'W')
            {
                queueLengthThisSec[getFuelTypeIndex(pump4.getFuelType(i))]++;
                timeInQueueThisSec[getFuelTypeIndex(pump4.getFuelType(i))]++;
                timeInServiceThisSec[getFuelTypeIndex(pump4.getFuelType(i))]++;
            }
            else if (pump4.getStatus(i) == 'F')
            {
                timeInServiceThisSec[getFuelTypeIndex(pump4.getFuelType(i))]++;
            }
        }
        for (int i = 0; i < pump5.getLength(); i++)
        {
            if (pump5.getStatus(i) == 'W')
            {
                queueLengthThisSec[3]++;
                timeInQueueThisSec[3]++;
                timeInServiceThisSec[3]++;
            }
            else if (pump5.getStatus(i) == 'F')
            {
                timeInServiceThisSec[3]++;
            }
        }
        for (int i = 0; i < pump6.getLength(); i++)
        {
            if (pump6.getStatus(i) == 'W')
            {
                queueLengthThisSec[4]++;
                timeInQueueThisSec[4]++;
                timeInServiceThisSec[4]++;
            }
            else if (pump6.getStatus(i) == 'F')
            {
                timeInServiceThisSec[4]++;
            }
        }
        for (int i = 0; i < payment.getLength(); i++)
        {
            if (payment.getStatus(i) == 'Q')
            {
                queueLengthThisSec[getFuelTypeIndex(payment.getFuelType(i))]++;
                timeInQueueThisSec[getFuelTypeIndex(payment.getFuelType(i))]++;
                timeInServiceThisSec[getFuelTypeIndex(payment.getFuelType(i))]++;
            }
            else if (payment.getStatus(i) == 'P')
            {
                timeInServiceThisSec[getFuelTypeIndex(payment.getFuelType(i))]++;
            } 
        }
        for (int i = 0; i < 5; i++)
        {
            avgQueueLength[i] += queueLengthThisSec[i];
            avgTimeInQueue[i] += timeInQueueThisSec[i];
            avgTimeInService[i] += timeInServiceThisSec[i];
        }


        //Debug: Output pumps process
        /*for (int i = 0; i < pump1.getLength(); i++)
        {
            cout<<"pump1 time "<<t<<": "<<" Qslot: "<<i<<" "<<pump1.getArrTime(i)<<" "<<pump1.getFuelType(i)<<" "<<pump1.getFillTime(i)<<" "<<pump1.getPayTime(i)<<" "<<pump1.getStatus(i)<<" "<<pump1.getPumpNo(i)<<endl;
        }
        for (int i = 0; i < pump2.getLength(); i++)
        {
            cout<<"pump2 time "<<t<<": "<<" Qslot: "<<i<<" "<<pump2.getArrTime(i)<<" "<<pump2.getFuelType(i)<<" "<<pump2.getFillTime(i)<<" "<<pump2.getPayTime(i)<<" "<<pump2.getStatus(i)<<" "<<pump2.getPumpNo(i)<<endl;
        }
        for (int i = 0; i < pump3.getLength(); i++)
        {
            cout<<"pump3 time "<<t<<": "<<" Qslot: "<<i<<" "<<pump3.getArrTime(i)<<" "<<pump3.getFuelType(i)<<" "<<pump3.getFillTime(i)<<" "<<pump3.getPayTime(i)<<" "<<pump3.getStatus(i)<<" "<<pump3.getPumpNo(i)<<endl;
        }
        for (int i = 0; i < pump4.getLength(); i++)
        {
            cout<<"pump4 time "<<t<<": "<<" Qslot: "<<i<<" "<<pump4.getArrTime(i)<<" "<<pump4.getFuelType(i)<<" "<<pump4.getFillTime(i)<<" "<<pump4.getPayTime(i)<<" "<<pump4.getStatus(i)<<" "<<pump4.getPumpNo(i)<<endl;
        }
        for (int i = 0; i < pump5.getLength(); i++)
        {
            cout<<"pump5 time "<<t<<": "<<" Qslot: "<<i<<" "<<pump5.getArrTime(i)<<" "<<pump5.getFuelType(i)<<" "<<pump5.getFillTime(i)<<" "<<pump5.getPayTime(i)<<" "<<pump5.getStatus(i)<<" "<<pump5.getPumpNo(i)<<endl;
        }
        for (int i = 0; i < pump6.getLength(); i++)
        {
            cout<<"pump6 time "<<t<<": "<<" Qslot: "<<i<<" "<<pump6.getArrTime(i)<<" "<<pump6.getFuelType(i)<<" "<<pump6.getFillTime(i)<<" "<<pump6.getPayTime(i)<<" "<<pump6.getStatus(i)<<" "<<pump6.getPumpNo(i)<<endl;
        }
        //Debug: Output payment queue process
        for (int i = 0; i < payment.getLength(); i++)
        {
            cout<<"payment "<<t<<": "<<payment.getArrTime(i)<<" "<<payment.getFuelType(i)<<" "<<payment.getFillTime(i)<<" "<<payment.getPayTime(i)<<" "<<payment.getStatus(i)<<" "<<payment.getPumpNo(i)<<endl;
        }
        cout<<"=============================================================="<<endl;*/

        t++;
    }
    lastDepTime = t;
    totalSimulateTime = lastDepTime - firstArrTime;
    //Debug:
    //cout<<firstArrTime<<" "<<lastDepTime<<" "<<totalSimulateTime<<endl;
    for (int i = 0; i < 5; i++)
    {
        avgQueueLength[i] =  avgQueueLength[i] / totalSimulateTime;
        avgTimeInQueue[i] = avgTimeInQueue[i] / numberOfCarsServed[i];
        avgTimeInService[i] = avgTimeInService[i] / numberOfCarsServed[i];
    }
    int totalSimulateTimeHour = totalSimulateTime / 3600;
    totalSimulateTime = totalSimulateTime - totalSimulateTimeHour * 3600;
    int totalSimulateTimeMinute = totalSimulateTime / 60;
    int totalSimulateTimeSecond = totalSimulateTime % 60;

    cout<<"Total time simulated: "<<totalSimulateTimeHour<<" hour"<<((totalSimulateTimeHour == 1) ? " " : "s ")<<totalSimulateTimeMinute<<" minute"<<((totalSimulateTimeMinute == 1) ? " " : "s ")
        <<totalSimulateTimeSecond<<" second"<<((totalSimulateTimeSecond == 1) ? "" : "s")<<endl<<endl;

    cout<<"For 92 octane:"<<endl<<"Average queue length: "<<avgQueueLength[0]<<" car"<<((avgQueueLength[0] <= 1 && avgQueueLength[0] > 0) ? "" : "s")<<endl
        <<"Average time in queue: "<<avgTimeInQueue[0]<<" seconds"<<endl
        <<"Average time in system: "<<avgTimeInService[0]<<" seconds"<<endl
        <<"The number of cars served: "<<numberOfCarsServed[0]<<" car"<<((numberOfCarsServed[0] == 1) ? "" : "s")<<endl
        <<"The number of cars that left before  being served: "<<numberOfCarsLeft[0]<<" car"<<((numberOfCarsLeft[0] == 1) ? "" : "s")<<endl<<endl;

    cout<<"For 95 octane:"<<endl<<"Average queue length: "<<avgQueueLength[1]<<" car"<<((avgQueueLength[1] <= 1 && avgQueueLength[1] > 0) ? "" : "s")<<endl
        <<"Average time in queue: "<<avgTimeInQueue[1]<<" seconds"<<endl
        <<"Average time in system: "<<avgTimeInService[1]<<" seconds"<<endl
        <<"The number of cars served: "<<numberOfCarsServed[1]<<" car"<<((numberOfCarsServed[1] == 1) ? "" : "s")<<endl
        <<"The number of cars that left before  being served: "<<numberOfCarsLeft[1]<<" car"<<((numberOfCarsLeft[1] == 1) ? "" : "s")<<endl<<endl;

    cout<<"For 98 octane:"<<endl<<"Average queue length: "<<avgQueueLength[2]<<" car"<<((avgQueueLength[2] <= 1 && avgQueueLength[2] > 0) ? "" : "s")<<endl
        <<"Average time in queue: "<<avgTimeInQueue[2]<<" seconds"<<endl
        <<"Average time in system: "<<avgTimeInService[2]<<" seconds"<<endl
        <<"The number of cars served: "<<numberOfCarsServed[2]<<" car"<<((numberOfCarsServed[2] == 1) ? "" : "s")<<endl
        <<"The number of cars that left before  being served: "<<numberOfCarsLeft[2]<<" car"<<((numberOfCarsLeft[2] == 1) ? "" : "s")<<endl<<endl;

    cout<<"For diesel:"<<endl<<"Average queue length: "<<avgQueueLength[3]<<" car"<<((avgQueueLength[3] <= 1 && avgQueueLength[3] > 0) ? "" : "s")<<endl
        <<"Average time in queue: "<<avgTimeInQueue[3]<<" seconds"<<endl
        <<"Average time in system: "<<avgTimeInService[3]<<" seconds"<<endl
        <<"The number of cars served: "<<numberOfCarsServed[3]<<" car"<<((numberOfCarsServed[3] == 1) ? "" : "s")<<endl
        <<"The number of cars that left before  being served: "<<numberOfCarsLeft[3]<<" car"<<((numberOfCarsLeft[3] == 1) ? "" : "s")<<endl<<endl;

    cout<<"For LPG:"<<endl<<"Average queue length: "<<avgQueueLength[4]<<" car"<<((avgQueueLength[4] <= 1 && avgQueueLength[4] > 0) ? "" : "s")<<endl
        <<"Average time in queue: "<<avgTimeInQueue[4]<<" seconds"<<endl
        <<"Average time in system: "<<avgTimeInService[4]<<" seconds"<<endl
        <<"The number of cars served: "<<numberOfCarsServed[4]<<" car"<<((numberOfCarsServed[4] == 1) ? "" : "s")<<endl
        <<"The number of cars that left before  being served: "<<numberOfCarsLeft[4]<<" car"<<((numberOfCarsLeft[4] == 1) ? "" : "s")<<endl<<endl;

    cout<<"Pump 1 total idle time: "<<totalIdleTime[0]<<" seconds"<<endl;
    cout<<"Pump 2 total idle time: "<<totalIdleTime[1]<<" seconds"<<endl;
    cout<<"Pump 3 total idle time: "<<totalIdleTime[2]<<" seconds"<<endl;
    cout<<"Pump 4 total idle time: "<<totalIdleTime[3]<<" seconds"<<endl;
    cout<<"Pump 5 total idle time: "<<totalIdleTime[4]<<" seconds"<<endl;
    cout<<"Pump 6 total idle time: "<<totalIdleTime[5]<<" seconds"<<endl;

    //Debug:
    //cout<<pump1.getLength()<<" "<<pump2.getLength()<<" "<<pump3.getLength()<<" "<<pump4.getLength()<<" "<<pump5.getLength()<<" "<<pump6.getLength()<<" "<<payment.getLength()<<" "<<allCars.getLength()<<endl;
    return 0;
}

int convertTimeToSec(string formattedTime)
{
    string hoursStr;
    string minutesStr;
    string secondsStr;
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int timeInSec = 0;
        
    int pos = formattedTime.find(":");
    hoursStr = formattedTime.substr(0, pos);
    formattedTime = formattedTime.substr(pos + 1);
    formattedTime.find(":");
    minutesStr = formattedTime.substr(0, pos);
    secondsStr = formattedTime.substr(pos + 1);
    hours += atoi(hoursStr.c_str());
    minutes += atoi(minutesStr.c_str());
    seconds += atoi(secondsStr.c_str());

    timeInSec = hours*60*60 + minutes*60 + seconds;

    return timeInSec;
}

void updatePumpStatus (linkedlist &pump, linkedlist &payment)
{
    if (pump.getLength() > 0)
    {
        if (pump.getStatus(0) == 'W')
        {
            pump.setStatus(0, 'F');
            pump.setFillTime(0, (pump.getFillTime(0) - 1));
        }
        else if (pump.getStatus(0) == 'F')
        {
            pump.setFillTime(0, (pump.getFillTime(0)-1));
        }
        if (pump.getFillTime(0) == 0 && pump.getStatus(0) == 'F')
        {
            pump.setStatus(0, 'Q');
            payment.appendNode(pump.getArrTime(0), pump.getFuelType(0), pump.getFillTime(0), pump.getPayTime(0), pump.getStatus(0), pump.getPumpNo(0));
        }
    }
}

int minimal (int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

int getFuelTypeIndex(char fuelType)
{
    if (fuelType == '2')
    {
        return 0;
    }
    else if (fuelType == '5')
    {
        return 1;
    }
    else if (fuelType == '8')
    {
        return 2;
    }
    else if (fuelType == 'd')
    {
        return 3;
    }
    else if (fuelType == 'l')
    {
        return 4;
    }
}