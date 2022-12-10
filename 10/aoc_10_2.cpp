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

void reset_row(string row[40]){
    for(int i = 0; i < 40; i++){
        row[i] = ".";
    }
}

string printRow(string row[40]){
    string result = "";
    for(int i = 0; i < 40; i++){
        result += row[i];
    }
    return result;
}

int main () {
    string myText;
    ifstream MyReadFile("input");
    int X = 1;

    string screen[6][40];
    reset_row(screen[0]);
    bool adding = false;
    vector<string> splitted;
    int row = 0;
    int pixel = 0;
    for(int cycle = 1; cycle<=220; cycle++){
        //Draw next pixel in screen
        if(pixel == X-1 || pixel == X || pixel == X+1){
            screen[row][pixel] = "#";
        }
        pixel +=1;
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
        if((cycle)%40==0){
            row += 1;
            reset_row(screen[row]);
            pixel = 0;
        }

    }
    for(int i= 0; i<6; i++){
        cout << printRow(screen[i]) << endl;
    }
    
}