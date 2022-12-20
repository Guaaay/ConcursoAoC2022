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

struct point{
    int x;
    int y;
};



struct beacon{
    point location;
};
struct sensor{
    point location;
    beacon closest_beacon;
    int manhattan_dist_to_beacon;
};

int main(){
    string myText;
    ifstream MyReadFile("input");
    
    vector<sensor> grid;
    while (getline(MyReadFile, myText))
    {
        
        //Get sensor's x and y coordinates from input
        vector<string> parsed = split(myText, ' ');
        sensor newSensor;
        newSensor.location.x = stoi(parsed[2].substr(2, parsed[2].length()-3));
        newSensor.location.y = stoi(parsed[3].substr(2, parsed[3].length()-3));
        newSensor.closest_beacon.location.x = stoi(parsed[8].substr(2, parsed[8].length()-3));
        newSensor.closest_beacon.location.y = stoi(parsed[9].substr(2, parsed[9].length()-2));
        //Calculate manhattan distance from sensor to beacon:
        int m_dist = abs(newSensor.location.x-newSensor.closest_beacon.location.x)+
                     abs(newSensor.location.y-newSensor.closest_beacon.location.y);
        newSensor.manhattan_dist_to_beacon = m_dist;
        //Add sensors and beacons to grid
        grid.push_back(newSensor);
    }
    //Calculate places where a beacon can't be to grid:
    //We just look along the line, and calculate the manhattan distance to every sensor:
    int numImpossible = 0;
    int y = 2000000;
    for(int i = -2000000; i < 5000000; i++){
        for(sensor s : grid){
            //If our current manhattan distance to the sensor is lower than the distance from the sensor to the beacon, there can't be a beacon here
            //Check if we are on a beacon: 
            if(s.closest_beacon.location.x == i && s.closest_beacon.location.y == y){
                break;
            }
            int curr_m_dist = abs(s.location.x-i)+
                     abs(s.location.y-y);
            if(curr_m_dist <= s.manhattan_dist_to_beacon){
                numImpossible +=1;
                break;
            }
            
        }
    }
    cout << numImpossible << endl;
    MyReadFile.close();
    return 0;
}