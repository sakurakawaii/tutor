#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include "linkedlist.h"
#include "hashtable.h"
using namespace std;

int totalCPUTime (linkedlist userInfo);
string longestPathInfo (linkedlist userInfo);

int main()
{
    string temp;
    int count = 1;
    string cut;
    int lineCount = 1;
    int hashSize = 120;
    hashtable allProcess(hashSize);
    while(getline(cin, temp))
    {
        if (temp.find("<defunct>") == -1)
        {
            while(temp[0] == ' ')
            {
                temp = temp.substr(1);
            }
            string array[7];
            bool isAddedToHashTable = false;
            int pos = temp.find(" ");
            bool cmdChecker = false;
            while (count <= 8)
            {
                if (pos != -1)
                {
                    cut = temp.substr(0, pos);
                    temp = temp.substr(pos + 1);
                }
                if (count < 4)
                {
                    array[count-1] = cut;
                }
                else if (count > 4 && count < 8)
                {
                    array[count-2] = cut;
                }
                else if (count == 8)
                {
                    if (pos == -1)
                    {
                        if (temp[0] != '[' && temp[temp.size()-1] != ']')
                        {
                            array[count-2] = temp;
                            cmdChecker = true;
                        }
                    }
                    else
                    {
                        if (cut[0] != '[' && cut[cut.size()-1] != ']')
                        {
                            array[count-2] = cut;
                            cmdChecker = true;
                        }
                    }
                    if (cmdChecker && lineCount != 1)
                    {
                        int pos = allProcess.findUser(array[0]);
                        if (pos != -1)
                        {
                            allProcess.setProcessList(pos, array[0], array[1], array[2], array[3], array[4], array[5], array[6]);
                        }
                        else
                        {
                            allProcess.setUser(array[0]);
                            pos = allProcess.findUser(array[0]);
                            allProcess.setProcessList(pos, array[0], array[1], array[2], array[3], array[4], array[5], array[6]);
                        }
                    }
                }
                count++;
                while(temp[0] == ' ')
                {
                    temp = temp.substr(1);
                }
                pos = temp.find(" ");
            }
            count = 1;
            lineCount++;
        }
    }

    vector <string> userList = allProcess.getUserList();
    int totalProcesses = 0;
    int mostProcesses = 0;
    string mostProcessesUser = "";
    int leastProcesses = 0;
    string leastProcessesUser = "";
    int mostSlashCount = 0;
    string longestPathAndPid = "";
    string longestPathUser = "";
    int totalCPUTimeWithAllProcesses = 0;
    for (int i = 0; i < userList.size(); i++)
    {
        if (userList[i] != "")
        {
            linkedlist userInfo = allProcess.getProcessList(userList[i]);
            cout<<"User "<<userInfo.getUid(0)<<endl;
            cout<<"=====";
            for (int j = 0; j < userInfo.getUid(0).size(); j++)
            {
                cout<<"=";
            }
            cout<<endl<<endl;
            cout<<"User "<<userInfo.getUid(0)<<" has a total of "<<userInfo.getLength()<<" process"
                <<((userInfo.getLength() != 1) ? "es" : "")<<endl;
            totalProcesses += userInfo.getLength();
            if (userInfo.getLength() >= mostProcesses)
            {
                mostProcesses = userInfo.getLength();
                mostProcessesUser = userInfo.getUid(0);
            }
            if (userInfo.getLength() <= leastProcesses || leastProcesses == 0)
            {
                leastProcesses = userInfo.getLength();
                leastProcessesUser = userInfo.getUid(0);
            }

            int totalCPUTimeOfThisUser = totalCPUTime(userInfo);
            cout<<"User "<<userInfo.getUid(0)<<" has consumed a total of "<<totalCPUTimeOfThisUser / 60
                <<" minute"<<(((totalCPUTimeOfThisUser / 60) != 1) ? "s" : "")<<" and "<<totalCPUTimeOfThisUser % 60
                <<" second"<<(((totalCPUTimeOfThisUser % 60) != 1) ? "s" : "")<<" of CPU time."<<endl;
            totalCPUTimeWithAllProcesses += totalCPUTimeOfThisUser;

            cout<<"The process id with the longest path name is pid ";
            string longestPathInformation = longestPathInfo(userInfo);
            int longestPathInformationSpacePos = longestPathInformation.find(" ");
            int longestPathInformationSlashCount = atoi((longestPathInformation.substr(0, longestPathInformationSpacePos)).c_str());
            longestPathInformation = longestPathInformation.substr(longestPathInformationSpacePos+1);
            if(longestPathInformationSlashCount >= mostSlashCount)
            {
                mostSlashCount = longestPathInformationSlashCount;
                longestPathAndPid = longestPathInformation;
                longestPathUser = userInfo.getUid(0);
            }
            cout<<longestPathInformation<<"."<<endl<<endl;
        }        
    }

    cout<<"Statistical Summary"<<endl;
    cout<<"=================="<<endl;
    cout<<"There are a total of "<<totalProcesses<<" process"
        <<((totalProcesses != 1) ? "es" : "")<<" in the process table."<<endl;
    cout<<"User "<<mostProcessesUser<<" has the most processes in the table (count = "<<mostProcesses<<")"<<endl;
    cout<<"User "<<leastProcessesUser<<" has the least processes in the table (count = "<<leastProcesses<<")"<<endl<<endl;

    cout<<"The process with the longest path name is pid ";
    int spacePosOfLongestPath = longestPathAndPid.find(" ");
    cout<<longestPathAndPid.substr(0, spacePosOfLongestPath)<<" with the path name "<<longestPathAndPid.substr(spacePosOfLongestPath + 1)
        <<" belonging to the "<<longestPathUser<<" user."<<endl<<endl;

    totalCPUTimeWithAllProcesses = totalCPUTimeWithAllProcesses / totalProcesses;
    int totalCPUTimeWithAllProcessesMinute = totalCPUTimeWithAllProcesses / 60;
    int totalCPUTimeWithAllProcessesSecond = totalCPUTimeWithAllProcesses % 60;
    cout<<"The average CPU time used by all processes is "<<totalCPUTimeWithAllProcessesMinute<<" minute"
        <<((totalCPUTimeWithAllProcessesMinute != 1) ? "s" : "")<<" and "
        <<totalCPUTimeWithAllProcessesSecond<<" second"<<((totalCPUTimeWithAllProcessesSecond != 1) ? "s" : "")<<"."<<endl;
    
    return 0;
}


int totalCPUTime (linkedlist userInfo)
{
    int days = 0;
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int colonCount = 0;
    string timeFormat = userInfo.getTime(0);
    for (int i = 0; i < timeFormat.size(); i++)
    {
        if (timeFormat[i] == ':')
        {
            colonCount++;
        }
    }
    if (colonCount == 1)
    {
        for (int i = 0; i < userInfo.getLength(); i++)
        {
            string formattedTime = userInfo.getTime(i);
            string minutesStr;
            string secondsStr;
            int pos = formattedTime.find(":");
            minutesStr = formattedTime.substr(0, pos);
            secondsStr = formattedTime.substr(pos+1);
            minutes += atoi(minutesStr.c_str());
            seconds += atoi(secondsStr.c_str());
        }
    }
    else if (colonCount == 2)
    {
        for (int i = 0; i < userInfo.getLength(); i++)
        {
            string formattedTime = userInfo.getTime(i);
            string daysStr;
            string hoursStr;
            string minutesStr;
            int pos = formattedTime.find(":");
            daysStr = formattedTime.substr(0, pos);
            formattedTime = formattedTime.substr(pos+1);
            formattedTime.find(":");
            hoursStr = formattedTime.substr(0, pos);
            minutesStr = formattedTime.substr(pos+1);
            days += atoi(daysStr.c_str());
            hours += atoi(hoursStr.c_str());
            minutes += atoi(minutesStr.c_str());
        }        
    }
    return (seconds + 60*minutes + 60*60*hours + 60*60*24*days);
}


string longestPathInfo (linkedlist userInfo)
{
    int mostSlashCounts = 0;
    string longestPathAndPid = "";
    for (int i = 0; i < userInfo.getLength(); i++)
    {
        string currentCmd = userInfo.getCmd(i);
        int slashCount = 0;
        for (int j = 0; j < currentCmd.size(); j++)
        {
            if (currentCmd[j] == '/')
            {
                slashCount++;
            }
        }
        if (slashCount >= mostSlashCounts)
        {
            mostSlashCounts = slashCount;
            stringstream ss;
            ss << mostSlashCounts;
            longestPathAndPid = ss.str() + " " + userInfo.getPid(i) + " " + currentCmd;
        }
    }
    return longestPathAndPid;
}