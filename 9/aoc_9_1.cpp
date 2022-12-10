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
        tail.j = head.j;
    }
    else if(tail > head){
        tail.i -= 1;
        tail.j = head.j;
    }
    else if(tail.isAbove(head)){
        tail.i = head.i;
        tail.j -= 1;
    }
    else if(tail.isBelow(head)){
        tail.i = head.i;
        tail.j += 1;
    }
    return tail;
}

bool cmp_coords(coord coord1, coord coord2) { 
    return (coord1.i == coord2.i) && (coord1.j == coord2.j); };

int main () {
    string myText;
    ifstream MyReadFile("input");
    vector<coord> unique_coords;
    //Lambda func used to compare coordinates
    
    

    coord tail;
    coord head;
    tail.set(0,0);
    head.set(0,0);

    while(getline(MyReadFile,myText)){
        string dir = myText.substr(0, 1);
        int steps = stoi(myText.substr(2, 2));
        //Calculate each step
        for(int i = 0; i < steps; i++){
            head.step(dir);
            tail = follow(head, tail);
            bool exists = false;
            for(vector<coord>::iterator it = unique_coords.begin() ; it != unique_coords.end(); ++it){
                if(cmp_coords(tail,(*it))){
                    exists = true;
                    break;
                }
            }
            if(!exists){
                unique_coords.push_back(tail);}
        }
        
    }
    cout << "Head: " << head << "Tail: " << tail << endl;
    cout << "Number of unique tail positions: " << unique_coords.size() << endl;
}