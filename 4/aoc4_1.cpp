#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

int main()
{
    string myText;
    ifstream MyReadFile("input");
    string delimiter1 = ",";
    string delimiter2 = "-";
    string range1;
    string range2;
    int range1_1;
    int range1_2;
    int range2_1;
    int range2_2;
    int total_score = 0;
    while (getline(MyReadFile, myText))
    {
        range1 = myText.substr(0, myText.find(delimiter1));
        range2 = myText.substr(myText.find(delimiter1) + 1, myText.length());
        range1_1 = stoi(range1.substr(0, range1.find(delimiter2)));
        range1_2 = stoi(range1.substr(range1.find(delimiter2) + 1, range1.length()));
        range2_1 = stoi(range2.substr(0, range2.find(delimiter2)));
        range2_2 = stoi(range2.substr(range2.find(delimiter2) + 1, range2.length()));
        //second range is contained in the first or first range is contained in the second
        if ((abs(range1_1) <= abs(range2_1) && abs(range1_2) >=range2_2) || (abs(range1_1) >= abs(range2_1) && abs(range1_2) <=range2_2)){    
            total_score +=1;
        }
    }
    MyReadFile.close(); 
    cout << total_score << endl;
}