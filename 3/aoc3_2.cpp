#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;


int main () {
    string myText;
    ifstream MyReadFile("input");
    string delimiter = " ";
    string enemy_play;
    string my_play;
    streampos oldpos;
    bool start = true;
    int total_score = 0;
    int lines = 0;
    char sacks [3][100];
    int lens[3];
    while (getline (MyReadFile, myText)) {
        if(lines < 3){
            if(lines == 0 && !start){
                MyReadFile.seekg(oldpos);
                getline (MyReadFile, myText);
            }
            if(lines == 2){
                oldpos = MyReadFile.tellg();
            }
            start = false;
            int len = myText.length();
            string str1 = myText.substr(0,len);
            char char_array1[len + 1];
            strcpy(char_array1, str1.c_str());
            strcpy(sacks[lines],char_array1);
            lens[lines] = len;
            lines +=1;
        }
        else{
            
            char result;
            bool found = false;
            //3 loops y me la pela 
            for(int i = 0; i < lens[0] && !found; i++){
                for(int j = 0; j < lens[1] && !found; j++){
                    if(sacks[0][i] == sacks[1][j]){
                        for(int k = 0; k < lens[2] && !found; k++){
                            if(sacks[0][i] == sacks[2][k]){
                                result = sacks[2][k];
                                found = true;
                            }
                        }
                    }
                }
            }
            if(islower(result)){
                total_score += result - 96;
            }
            else{
                total_score += result - 38;
            }
            lines = 0;
        }
        
    }
    MyReadFile.close(); 
    cout << total_score << endl;
}