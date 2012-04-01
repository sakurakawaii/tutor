#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <ctime>
using namespace std;

void FIFO(vector <string> references, int frameSize);
void LRU (vector <string> references, int frameSize);
void LFU (vector <string> references, int frameSize);
void RANDOM (vector <string> references, int frameSize);

int main()
{
    vector <string> references;
    int frameSize;
    string frameSizeInput;
    string referencesInput;
    //Input page references, store in vector
    cout<<"Enter Page Reference String:";
    getline(cin, referencesInput);
    //check the page reference input is empty or not
    if (referencesInput == "")
    {
        cout<<"Error: No reference string"<<endl;
        return -1;
    }
    //clear leading spaces
    while (referencesInput[0] == ' ')
    {
        referencesInput = referencesInput.substr(1);
    }
    //clear spaces at the end
    while (referencesInput[referencesInput.size()-1] == ' ')
    {
        referencesInput = referencesInput.substr(0, referencesInput.size()-1);
    }
    int pos = referencesInput.find(" ");
    string cut;
    while (pos != -1)
    {
        cut = referencesInput.substr(0, pos);
        //check if page reference string is from 'A-Z' only (for first to last-1 page reference string)
        if (cut.size() > 1 || cut[0] < 'A' || cut[0] > 'Z')
        {
            cout<<"Error: The page reference string can be an arbitrary sequence of Upper Case characters (A-Z)"<<endl;
            return -1;
        }
        references.push_back(cut);
        referencesInput = referencesInput.substr(pos+1);
        //clear leading spaces
        while (referencesInput[0] == ' ')
        {
            referencesInput = referencesInput.substr(1);
        }
        pos = referencesInput.find(" ");
    }
    //check if page reference string is from 'A-Z' only (for the last page reference string)
    if (referencesInput.size() > 1 || referencesInput[0] < 'A' || referencesInput[0] > 'Z')
    {
        cout<<"Error: The page reference string can be an arbitrary sequence of Upper Case characters (A-Z)"<<endl;
        return -1;
    }
    references.push_back(referencesInput);
       
    //Input frame size
    cout<<"Enter Page Frame Size:";
    getline(cin, frameSizeInput);
    frameSize = atoi(frameSizeInput.c_str());
    //check if frameSize is an positive int or not
    if (frameSize <= 0)
    {
        cout<<"Error: Invalid frame size"<<endl;
        return -1;
    }
    
    FIFO(references, frameSize);
    LRU(references, frameSize);
    LFU(references, frameSize);
    RANDOM(references, frameSize);
    
    return 0;
}



void FIFO(vector <string> references, int frameSize)
{
    vector <string> frame;
    int firstIn = 0; //Incicate which page should be swapped
    int pageFaultCount = 0;
    
    //Prepare frame
    for (int i = 0; i < frameSize; i++)
    {
        frame.push_back("");
    }
    
    cout<<endl<<"FIFO Performance"<<endl<<endl;
    //Check each reference string with frame
    for (int i = 0; i < references.size(); i++)
    {
        bool findInFrame = false;
        for (int j = 0; j < frame.size(); j++)
        {
            //Check if we have a hit
            if (references[i] == frame[j])
            {
                findInFrame = true;
                break;
            }
            //Check if still have empty slots in frame, swap in and raise a page fault
            else if (frame[j] == "")
            {
                findInFrame = true;
                frame[j] = references[i];
                cout<<"Page Fault at time = "<<i<<" swapped in candidate "<<references[i]<<endl;
                pageFaultCount++;
                break;
            }
        }
        //Can't find page in frame, we have a page fault
        if (!findInFrame)
        {
            cout<<"Page Fault at time = "<<i<<" swapped in candidate "<<references[i]<<" replacing place in frame "<<frame[firstIn]<<endl;
            frame[firstIn] = references[i];
            firstIn++;
            firstIn = firstIn % frameSize;
            pageFaultCount++;
        }
    }
    cout<<"Total Page Faults: "<<pageFaultCount<<endl<<endl;
}

void LRU (vector <string> references, int frameSize)
{
    vector <string> frame;
    bool full = false;
    int pageFaultCount = 0;
    
    //Prepare frame
    for (int i = 0; i < frameSize; i++)
    {
        frame.push_back("");
    }
    
    cout<<"LRU Performance"<<endl<<endl;
    //Check each reference string with frame
    for (int i = 0; i < references.size(); i++)
    {
        bool findInFrame = false;
        for (int j = 0; j < frame.size(); j++)
        {
            //If we have a hit
            if (references[i] == frame[j])
            {
                findInFrame = true; 
                //move this page to last of vector(recent used in last)
                frame.push_back(frame[j]);
                frame.erase(frame.begin()+j);
                //check frame is full of pages or not
                //if there is any empty page in frame, move them to last for further use
                if (!full)
                {
                    int emptyPageCount = 0;
                    for (int k = 0; k < frame.size(); k++)
                    {
                        if (frame[k] == "")
                        {
                            emptyPageCount++;
                            frame.erase(frame.begin()+k);
                            frame.push_back("");
                        }
                        if(emptyPageCount == 0)
                        {
                            full = true;
                        }
                    }
                }
                break;
            }
            //We meet an empty page, swap in and raise a page fault
            else if(frame[j] == "")
            {
                findInFrame = true;
                frame[j] = references[i];
                cout<<"Page Fault at time = "<<i<<" swapped in candidate "<<references[i]<<endl;
                pageFaultCount++;
                break;
            }
        }
        //if we haven't find reference string in frame, raise a page fault and move the first element of the frame (oldest in first, recent in last)
        //push the new page at last of the frame
        if (!findInFrame)
        {
            cout<<"Page Fault at time = "<<i<<" swapped in candidate "<<references[i]<<" replacing place in frame "<<frame[0]<<endl;
            frame.erase(frame.begin());
            frame.push_back(references[i]);
            pageFaultCount++;
        }
    }
    cout<<"Total Page Faults: "<<pageFaultCount<<endl<<endl;
}

void LFU (vector <string> references, int frameSize)
{
    map <string, int> frequentTracker; //<reference, frequency>
    set <string> frame;
    set <string>::iterator frameI;
    bool full = false;
    int pageFaultCount = 0;
    
    cout<<"LRU Performance"<<endl<<endl;
    //Check each reference string with frame
    for (int i = 0; i < references.size(); i++)
    {
        //Check reference string's frequency, if in tracker, frequency+1, otherwise, insert and make it frequency = 1
        if (frequentTracker.find(references[i]) != frequentTracker.end())
        {
            (frequentTracker.find(references[i])->second)++;
        }
        else
        {
            frequentTracker.insert(make_pair(references[i], 1));
        }
        //If reference string is not in frame
        if (frame.find(references[i]) == frame.end())
        {
            //if we have empty page, swap in reference string into frame
            if (frame.size() < frameSize)
            {
                frame.insert(references[i]);
                cout<<"Page Fault at time = "<<i<<" swapped in candidate "<<references[i]<<endl;
            }
            //if no more empty page
            else
            {
                //Look up frequet tracker for each page in frame and find the least frequently used and swap with the reference string
                int LFUCount = -1;
                pair <string, int> LFUPair;
                for (frameI = frame.begin(); frameI != frame.end(); frameI++)
                {
                    if (frequentTracker.find(*frameI) != frequentTracker.end())
                    {
                        if ((frequentTracker.find(*frameI)->second) < LFUCount || LFUCount == -1 )
                        {
                            LFUPair = *frequentTracker.find(*frameI);
                            LFUCount = LFUPair.second;
                        }
                    }
                }
                cout<<"Page Fault at time = "<<i<<" swapped in candidate "<<references[i]<<" replacing place in frame "<<LFUPair.first<<endl;
                frame.erase(LFUPair.first);
                frame.insert(references[i]);
            }
            pageFaultCount++;
        }
    }
    cout<<"Total Page Faults: "<<pageFaultCount<<endl<<endl;
}

void RANDOM (vector <string> references, int frameSize)
{
    vector <string> frame;
    int pageFaultCount = 0;
    
    //Prepare frame
    for (int i = 0; i < frameSize; i++)
    {
        frame.push_back("");
    }
    
    cout<<endl<<"RANDOM Performance"<<endl<<endl;
    //Check each reference string with frame
    for (int i = 0; i < references.size(); i++)
    {
        bool findInFrame = false;
        for (int j = 0; j < frame.size(); j++)
        {
            //Check if we have a hit
            if (references[i] == frame[j])
            {
                findInFrame = true;
                break;
            }
            //Check if still have empty slots in frame, swap in and raise a page fault
            else if (frame[j] == "")
            {
                findInFrame = true;
                frame[j] = references[i];
                cout<<"Page Fault at time = "<<i<<" swapped in candidate "<<references[i]<<endl;
                pageFaultCount++;
                break;
            }
        }
        //Can't find page in frame, we have a page fault
        if (!findInFrame)
        {
            //generate a random position in frame for swapping
            srand(time(0));//set seed based on time, so the program will always generate different random number with rand() function
            int pos = rand() % frameSize;//Use mod to make position always sit in frame size
            cout<<"Page Fault at time = "<<i<<" swapped in candidate "<<references[i]<<" replacing place in frame "<<frame[pos]<<endl;
            frame[pos] = references[i];
            pageFaultCount++;
        }
    }
    cout<<"Total Page Faults: "<<pageFaultCount<<endl<<endl;
}
