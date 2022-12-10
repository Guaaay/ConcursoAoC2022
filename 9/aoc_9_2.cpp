#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;




struct coord{
    int i=0;
    int j=0;
    //unordered_set<coord> positions_visited;

    coord(int x=0, int y=0){
        i == x;
        j == y;
    }
    
    void step(string dir){
        if(dir == "U"){
            j+=1;
        }
        else if(dir == "D"){
            j-=1;
        }
        else if(dir == "R"){
            i+=1;
        }
        else {
            i-=1;
        }

    }

    void set(int x, int y){
        i = x;
        j = y;
    }

    bool operator==(const coord other) const {
        return(i == other.i && j == other.j);
    };

    friend ostream& operator<<(ostream& os, const coord coord){
        os << "(" << coord.i << ", " << coord.j << ")";
        return os;
    }
    bool operator<(const coord other) const {
        return((i - other.i) < -1);
    };
    bool operator>(const coord other) const {
        return((i - other.i) > 1);
    };


    bool isAbove(const coord other) const {
        return((j - other.j) > 1);
    };
    bool isBelow(const coord other) const {
        return((j - other.j) < -1);
    };
};

coord follow(coord head, coord tail){
    if(tail < head){
        tail.i += 1;
        if(tail.j-head.j < -1)
            tail.j += 1;
        else if(tail.j-head.j > 1){
            tail.j -=1;
        }
        else{
            tail.j = head.j;}
    }
    else if(tail > head){
        tail.i -= 1;
        if(tail.j-head.j < -1)
            tail.j += 1;
        else if(tail.j-head.j > 1){
            tail.j -=1;
        }
        else{
            tail.j = head.j;}
    }
    else if(tail.isAbove(head)){
        if(tail.i-head.i < -1)
            tail.i += 1;
        else if(tail.i-head.i > 1){
            tail.i -=1;
        }
        else{
            tail.i = head.i;}
            
        tail.j -= 1;
    }
    else if(tail.isBelow(head)){
        if(tail.i-head.i < -1)
            tail.i += 1;
        else if(tail.i-head.i > 1){
            tail.i -=1;
        }
        else{
            tail.i = head.i;}
        tail.j += 1;
    }
    return tail;
}

int main () {
    string myText;
    ifstream MyReadFile("input");
    vector<coord> unique_coords;
    //Lambda func used to compare coordinates
    coord rope[10];
    for(int i = 0; i < 10; i++){
        coord knot;
        rope[i] = knot;
    }

    while(getline(MyReadFile,myText)){
        string dir = myText.substr(0, 1);
        int steps = stoi(myText.substr(2, 2));
        //Calculate each step
        for(int i = 0; i < steps; i++){ 

            rope[0].step(dir);
            for(int i = 1; i < 10; i++){
                rope[i] = follow(rope[i-1],rope[i]);
            }
            bool exists = false;
            for(vector<coord>::iterator it = unique_coords.begin() ; it != unique_coords.end(); ++it){
                if(rope[9]==(*it)){
                    exists = true;
                    break;
                }
            }
            if(!exists){
                unique_coords.push_back(rope[9]);}
        }
    }
    cout << endl;
    cout << "Number of unique tail positions: " << unique_coords.size() << endl;
}