#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

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


//Prints the cave to the output



int main(){
    char cave[200][200];
    //Initialize cave array with all '.'
    for(size_t i = 0; i < 200; i++)
    {
        for (size_t j = 0; j < 200; j++)
        {
            cave[i][j] = '.';
        }
    }
    
    
    string myText;
    ifstream MyReadFile("input");
    while (getline(MyReadFile, myText))
    {
        vector<string> coords = split(myText);
        for(int i = 0; i<coords.size()-1; i++){
            vector<string> firstCoord = split(coords[i],',');
            vector<string> secondCoord = split(coords[i+1],',');
            int x1 = stoi(firstCoord[0])-400;
            int y1 = stoi(firstCoord[1]);
            int x2 = stoi(secondCoord[0])-400;
            int y2 = stoi(secondCoord[1]);
            //Rock line goes right
            if(y1 == y2 && x1 < x2){
                for(int j = x1; j <= x2; j++){
                    cave[y1][j] = '#';
                }
            }
            //Rock line goes left
            if(y1 == y2 && x2 < x1){
                for(int j = x1; j >= x2; j--){
                    cave[y1][j] = '#';
                }
            }
            //Rock line goes up
            if(x1 == x2 && y1 < y2){
                for(int j = y1; j <= y2; j++){
                    cave[j][x1] = '#';
                }
            }
            //Rock line goes down
            if(x1 == x2 && y2 < y1){
                for(int j = y1; j >= y2; j--){
                    cave[j][x1] = '#';
                }
            }
            
        }
    }
    // for(int i = 199; i >= 0; i--)
    // {
    //     for (int j = 0; j < 200; j++)
    //     {
    //         cout << cave[i][j];
    //     }
    //     cout << endl;
    // }
    //calculate sand falling down from point 100,200
    int sandOriginX = 500-400;
    int sandOriginY = 0;
    int totalSand = 0;
    bool limitHit = false;
    while(!limitHit){
        int sandX = sandOriginX;
        int sandY = sandOriginY;
        bool stopped = false;
        while(!stopped){
            //Check to see if we hit vertical limit;
            if(sandY == 190){
                limitHit = true;
                break;
            }
            //Try to go down
            if(cave[sandY+1][sandX] == '.'){
                sandX = sandX;
                sandY = sandY+1;
            }
            //Try to go left
            else if(cave[sandY+1][sandX-1] == '.'){
                sandX = sandX-1;
                sandY = sandY+1;
            }
            //Try to go right
            else if(cave[sandY+1][sandX+1] == '.'){
                sandX = sandX+1;
                sandY = sandY+1;
            }
            //Stay there
            else{
                totalSand += 1;
                stopped = true;
                cave[sandY][sandX] = 'o';
            }
        }
    }
    
    for(int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 200; j++)
        {
            cout << cave[i][j];
        }
        cout << endl;
    }
    cout<<totalSand<<"\n";
}