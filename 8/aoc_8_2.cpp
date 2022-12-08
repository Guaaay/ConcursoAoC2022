#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int main () {
    string myText;
    ifstream MyReadFile("input");
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
    int max_score = 0;
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            //Check trees to the left
            bool broke=false;
            int left = 0;
            for(int n = j-1; n >= 0; n--){
                left +=1;
                if(Mat.at(i).at(n) >= Mat.at(i).at(j)){
                    break;}
            }
            //Check trees right
            int right=0;
            for(int n = j+1; n < num_cols; n++){
                right += 1;
                if(Mat.at(i).at(n) >= Mat.at(i).at(j)){
                    break;}
            }
            //Check trees up
            int up = 0;
            for(int n = i-1; n >=0; n--){
                up += 1;
                if(Mat.at(n).at(j) >= Mat.at(i).at(j)){
                    break;}
            }
            //Check trees down
            int down = 0;
            for(int n = i+1; n < num_rows; n++){
                down += 1;
                if(Mat.at(n).at(j) >= Mat.at(i).at(j)){
                    break;}
            }
            int current_score = left * right * up * down;
            if (current_score > max_score){
                max_score = current_score;
            }
        }
    }
    cout << "Biggest scenic score is: " << max_score << endl;
}