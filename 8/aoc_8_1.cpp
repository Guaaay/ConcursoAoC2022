#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int main () {
    string myText;
    ifstream MyReadFile("input");
    int total_score = 0;
    //Make matrix
    using Vij = vector<int>;
    vector<Vij> Mat;
    while (getline (MyReadFile, myText)) {
        vector<int> line;
        //string lineptr = &myText;
        for(int i = 0; i < myText.length(); i++){
            line.push_back(myText[i]-48);
        }
        Mat.push_back(line);
    }

    //Check for every tree (possible to optimize but f it)
    int num_cols = Mat.at(0).size();
    int num_rows = Mat.size();
    //Row traversal
    int visible_trees = 0;
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            //Check for edges
            if(i == 0 || j == 0 || i == num_rows-1 || j == num_cols-1){
                visible_trees += 1;
            }
            else{
                //Check trees to the left
                bool broke=false;
                for(int n = j-1; n >= 0; n--){
                    int elem = Mat.at(i).at(j);
                    int comp = Mat.at(i).at(n);
                    if(comp >= elem){
                        //Not visible to the left
                        broke = true;
                        break;}
                }
                if(broke){//Check trees to the right
                    broke = false;
                    for(int n = j+1; n < num_cols; n++){
                        if(Mat.at(i).at(n) >= Mat.at(i).at(j)){
                            //Not visible to the right
                            broke = true;
                            break;}
                    }
                }
                if(broke){
                    broke = false;
                    //Check trees up
                    for(int n = i-1; n >=0; n--){
                        if(Mat.at(n).at(j) >= Mat.at(i).at(j)){
                            //Not visible up
                            broke = true;
                            break;}
                    }
                }
                if(broke){
                    //Check trees down
                    broke = false;
                    for(int n = i+1; n < num_rows; n++){
                        if(Mat.at(n).at(j) >= Mat.at(i).at(j)){
                            //Not visible down
                            broke = true;
                            break;}
                    }
                }
                //If any of the loops didn't break, tree is visible
                if(!broke){
                    visible_trees += 1;
                }
            }
        }
    }
    cout << "Number of visible trees is: " << visible_trees << endl;
}