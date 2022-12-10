#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

// splits a std::string into vector<string> at a delimiter
vector<string> split(string x, char delim = ' ')
{
    x += delim; //includes a delimiter at the end so last word is also read
    vector<string> splitted;
    string temp = "";
    for (int i = 0; i < x.length(); i++)
    {
        if (x[i] == delim)
        {
            splitted.push_back(temp); //store words in "splitted" vector
            temp = "";
            i++;
        }
        temp += x[i];
    }
    return splitted;
}


int main () {
    string myText;
    ifstream MyReadFile("input");
    int X = 1;
    int signalStrength = 0;

    
    bool adding = false;
    vector<string> splitted;
    for(int cycle = 1; cycle<=220; cycle++){
        
        if(cycle == 20 || (cycle+20)%40==0){
            signalStrength += cycle*X;
        }
        if(!adding){
            if(getline(MyReadFile,myText)){
                splitted = split(myText);
                if(splitted.at(0) == "addx"){
                    adding = true;
                }
            }
        }
        
        else{
            X += stoi(splitted.at(1));
            adding = false;
        }
        

    }
    
    cout << "Sum of interesting positions: " << signalStrength << endl;
}