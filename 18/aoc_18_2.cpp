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

struct cube{
    int x;
    int y;
    int z;

    cube(int x_,int y_,int z_){
        x = x_;
        y = y_;
        z = z_;
    }
};

int main(){
    string myText;
    ifstream MyReadFile("input");
    vector<cube> cubes;
    int sides = 0;
    while (getline(MyReadFile, myText))
    {
        vector<string> parsed = split(myText, ',');
        cube cubo(stoi(parsed[0]),stoi(parsed[1]),stoi(parsed[2]));
        //Add cube's 6 sides
        sides +=6;
        //For every adjacent cube, remove 2 sides from total
        for(cube cubo2 : cubes){
            //Cube is to the sides, top or bottom, or front or back
            if(abs(cubo2.x-cubo.x) == 1 && cubo2.y == cubo.y && cubo2.z == cubo.z){
                sides -= 2;
            }
            else if(abs(cubo2.y-cubo.y) == 1  && cubo2.x == cubo.x && cubo2.z == cubo.z){
                sides -= 2;
            }
            else if(abs(cubo2.z-cubo.z) == 1  && cubo2.y == cubo.y && cubo2.x == cubo.x){
                sides -= 2;
            }
        }
        cubes.push_back(cubo);
    }
    cout << sides << endl;

}