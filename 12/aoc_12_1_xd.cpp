#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;



struct node{
    char value;
    bool visited = false;
    int dist = INT_MAX;
    node * pred = nullptr;
    vector<node*> neighbors;
    bool isStart = false;
    bool isEnd = false;

    void addNeighbor(node * toAdd){
        neighbors.push_back(toAdd);
    }
    void visit(){
        visited = true;
    }
};

struct graph{
    vector<vector<node>> nodes;

    // void addNode(node add, bool newLine, int i ){
    //     if(newLine){
    //         vector<node> newL;
    //         nodes.push_back(newL);
    //     }
    //     nodes[i].push_back(add);
    // }
};


bool canClimb(node * current, node * next){
    return (next!=nullptr) && (next->value - current->value <= 1);
}

int main () {   
    string myText;
    ifstream MyReadFile("input");
    //Parse input into matrix
    
    //used to count rows and columns
    int i = 0;
    int j = 0;
    //Build graph
    graph heightmap;
    while (getline (MyReadFile, myText)) {
        
        j = 0;
        vector<char> line;
        char char_array[myText.length()+1];
        strcpy(char_array, myText.c_str());
        for(char c : char_array){
            node curr;
            curr.value = c;
            if(c == 'S'){
                curr.isStart = true;
            }
            if(c == 'E'){
                curr.isEnd = true;
            }
            if(j == 0){
                vector<node> newL;
                heightmap.nodes.push_back(newL);
            }
            heightmap.nodes[i].push_back(curr);
            j+=1;
           
        }
        i+=1;
    }
    


    node * start ;
    node * end;
    for(int i = 0; i < heightmap.nodes.size(); i++){
        for(int j = 0; j< heightmap.nodes[i].size(); j++){
            //Check for available neighbors
            
            node * curr = &(heightmap.nodes[i][j]);
            node * nUp = (i == 0)? nullptr : &(heightmap.nodes[i-1][j]);
            node * nDown = (i == heightmap.nodes.size())? nullptr : &(heightmap.nodes[i+1][j]);
            node * nLeft = (j == 0)? nullptr : &(heightmap.nodes[i][j-1]);
            node * nRight = (j == heightmap.nodes[0].size()-1)? nullptr : &(heightmap.nodes[i][j+1]);
            if(curr->isEnd){
                end = curr;
            }
             if(curr->isStart){
                start = curr;
            }
            //Check if available to climb
            if(canClimb(curr, nUp)){
                curr->addNeighbor(nUp);
            }
            if(canClimb(curr, nDown)){
                curr->addNeighbor(nDown);
            }
            if(canClimb(curr, nLeft)){
                curr->addNeighbor(nLeft);
            }
            if(canClimb(curr, nRight)){
                curr->addNeighbor(nRight);
            }
        }
    }

    //Pathfinding algorithm:
    queue<node*> BFS;
    start->visit();
    start->dist=0;
    BFS.push(start);
    bool found = false;
    while(!BFS.empty()){
        node * curr = BFS.front();
        cout << curr->value << " ";
        BFS.pop();
        for(node * neighbor : curr->neighbors){
            if(!(neighbor->visited)){
                neighbor->visit();
                neighbor->dist=curr->dist+ 1;
                neighbor->pred=curr;
                BFS.push(neighbor);
                if(neighbor->isEnd){
                    found = true;
                    break;
                }
            }
        }
    found = false;
    break;
    }
    if(!found){
        cout << "no se ha encontrado camino" << endl;
    }
    else{
        vector<int> path;
        node * crawl = end;
        cout << "HOLA: " << crawl->pred->value << endl;
        // while (crawl->pred != nullptr){

        // }
    }
    
}