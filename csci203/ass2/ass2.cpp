#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;

int numOfPeople = 0;

struct Pump
{
	int arrTime; //in seconds
	char fuelType;
	int fillTime;
	int payTime;		
};

const int MAX = 500;
Pump fuelPump;

int main()
{
	//Initialise struct array of pump
	for(int i = 0; i < MAX; i++)
	{
		fuelPump[i].arrTime = 0;
		fuelPump[i].fuelType = " ";
		fuelPump[i].fillTime = 0;
		fuelPump[i].payTime = 0;
	}
	
	ifstream fin;
	char fname[50];
	
	cout << "Please enter the file name." << endl;
	cin >> fname;
	cout << "Simulation start" << endl;
	
	fin.open(fname);
	if(!fin.is_open())
	{
		cerr << "Can't open file" << endl;
		return 1;
	}
	
	string time;
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	int colonCount = 0;
	int arriveTime = 0;
	
	fin >> time;
	//convert into seconds
	for(int i = 0; i < time.size(); i++)
	{
		if(time[i] == ':')
		{
			colonCount++;
		}
	}
	if(colonCount ==2)
	{
		string formattedTime;
		string hoursStr;
		string minutesStr;
		string secondsStr;
		
		int pos = formattedTime.find(":");
		hours = formattedTime.substr(0, pos);
		formattedTime = formattedTime.substr(pos + 1);
		formattedTime.find(":");
		minutesStr = formattedTime.substr(0, pos);
		secondsStr = formattedTime.substr(pos + 1);
		hours += atoi(hoursStr.c_str());
		minutes += atoi(minutesStr.c_str());
		seconds += atoi(secondsStr.c_str());
	}

	arriveTime = hours*60*60 + minutes*60 + seconds; //how to store to struct
	fuelPump.arrTime = arriveTime;//?
	fin >> fuelPump.fuelType;
	fin >> fuelPump.fillTime;
	fin >> fuelPump.payTime;
	
	system("pause");
	return 0;
}
/*
kk, i think u can divide this assignment into these steps

靜かな夜に says: (9:11:25 PM)
so it mainly have two parts

靜かな夜に says: (9:11:54 PM)
one is pump queue, one is payment queue

靜かな夜に says: (9:12:49 PM)
u can focus on pump queue first

靜かな夜に says: (9:13:07 PM)
try to read in input and store them in array first

靜かな夜に says: (9:13:49 PM)
then change 00:02:37,etc into seconds

靜かな夜に says: (9:14:03 PM)
thats easier for future to calculate time
what type would the time be?

靜かな夜に says: (9:23:08 PM)
firstly u should read it in as string

靜かな夜に says: (9:23:14 PM)
then find ":"

靜かな夜に says: (9:23:44 PM)
i have the code in ur last 212 assignment

Marina says: (9:24:21 PM)
oki. so what bout in the struct part?

靜かな夜に says: (9:24:26 PM)
in the main.cpp

Marina says: (9:24:31 PM)
like struct for the pup

Marina says: (9:24:34 PM)
*pump

靜かな夜に says: (9:24:59 PM)
u can do that, but u still need to convert time into seconds to calculate

靜かな夜に says: (9:25:09 PM)
coz if u have hour, min, sec

Marina says: (9:25:30 PM)
so the struct would be int for seconds

靜かな夜に says: (9:25:32 PM)
its hard to to calculate since u need to take care the situation like 1 min 80secs

靜かな夜に says: (9:25:42 PM)
yeah, u can do something like that

靜かな夜に says: (9:25:48 PM)
struct pump

靜かな夜に says: (9:26:44 PM)
in main.cpp, totalCPUTime function

靜かな夜に says: (9:26:57 PM)
u have the example code for how to do that

靜かな夜に says: (9:27:07 PM)
u need that colonCount == 2 part

靜かな夜に says: (9:27:45 PM)
but instead of day, hour, min, u should have hour, min, sec

靜かな夜に says: (9:27:55 PM)
and use diff formula to convert them to sec

Marina says: (10:12:39 PM)
hmm im getting confused. coz my struct has the int arrTime. but then when i read it in its not going to be int

Marina says: (10:13:06 PM)
how do i like read it in, which im to convert it to secs

靜かな夜に says: (10:13:22 PM)
u should read it in as a string

靜かな夜に says: (10:13:33 PM)
so u will have something like 00:02:37 right?

靜かな夜に says: (10:13:44 PM)
then u cut them into 00 02 37

靜かな夜に says: (10:13:53 PM)
then convert 00 02 37 into int

靜かな夜に says: (10:14:16 PM)
then use 0*60*60 + 2*60 + 37

靜かな夜に says: (10:14:29 PM)
to make it as sec



*/
