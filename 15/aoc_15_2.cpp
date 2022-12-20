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
    bool found = false;
    int beaconX = 0;
    int beaconY = 0;
    //int size = 20;
    int size = 4000000;
    for(int y = 0; y <= size && !found; y++){
        if(y%1 == 0){
            //cout << (float)y/size*100 << "%" << "\n";
            cout << y << "/4000000" << "\n";
        }
        for(int x = 0; x <= size && !found; x++){
            for(sensor s : grid){
                //If our current manhattan distance to the sensor is lower than the distance from the sensor to the beacon, there can't be a beacon here
                //Check if we are on a beacon: 
                if(s.closest_beacon.location.x == x && s.closest_beacon.location.y == y){
                    found = false;
                    break;
                }
                int curr_m_dist = abs(s.location.x-x)+
                        abs(s.location.y-y);
                if(curr_m_dist < s.manhattan_dist_to_beacon){
                    if(x <= s.location.x){
                        x+=(abs(s.location.x-x)*2);
                    }
                    else{
                        x+=(s.manhattan_dist_to_beacon-(abs(s.location.y-y)))-abs(s.location.x-x);

                    }
                    found = false;
                    break;
                }
                else{
                    found = true;
                }
            }
            if(found){
                beaconX = x;
                beaconY = y;
            }
        }
    }
    long long int tuning = ((long long int)beaconX * 4000000 ) + beaconY;
    cout << tuning << endl;
    MyReadFile.close();
    return 0;
}