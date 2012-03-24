#include <iostream>
#include <string>
using namespace std;

int main()
{
    string temp;
    string array[6];
    int count = 1;
    string cut;
    int caseNo = 1;
    while(getline(cin, temp))
    {
        if (temp.find("<defunct>") == -1)
        {
            string array[7];
            int pos = temp.find(" ");
            while (count <= 8)
            {
                if (pos != -1)
                {
                    cut = temp.substr(0, pos);
                    temp = temp.substr(pos + 1);
                }
                if (count < 4)
                {
                    //cout<<cut<<" ";
                    array[count-1] = cut;
                }
                else if (count > 4 && count < 8)
                {
                    //cout<<cut<<" ";
                    array[count-2] = cut;
                }
                else if (count == 8)
                {
                    if (pos == -1)
                    {
                        if (temp[0] != '[' && temp[temp.size()-1] != ']')
                        {
                            array[count-2] = temp;
                            //cout<<temp<<endl;
                            for (int i = 0; i < 7; i++)
                            {
                                cout<<array[i]<<" ";
                            }
                            cout<<endl;
                        }
                    }
                    else
                    {
                        if (cut[0] != '[' && cut[cut.size()-1] != ']')
                        {
                            array[count-2] = cut;
                            //cout<<cut<<endl;
                            for (int i = 0; i < 7; i++)
                            {
                                cout<<array[i]<<" ";
                            }
                            cout<<endl;
                        }
                    }
                    break;
                }
                count++;
                while(temp[0] == ' ')
                {
                    temp = temp.substr(1);
                }
                pos = temp.find(" ");
            }
            count = 1;
            caseNo++;
        }
    }
    return 0;
}
