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
    int total_score = 0;
    while (getline (MyReadFile, myText)) {
        int len = myText.length();
        string str1 = myText.substr(0,len/2);
        string str2 = myText.substr(len/2,len);
        char char_array1[len/2 + 1];
        char char_array2[len/2 + 1];
        strcpy(char_array1, str1.c_str());
        strcpy(char_array2, str2.c_str());
        char result;
        bool found = false;
        for(int i = 0; i < len/2 && !found; i++){
            for(int j = 0; j < len/2 && !found; j++){
                if(char_array1[i] == char_array2[j]){
                    result = char_array1[i];
                    found = true;
                }
            }
        }
        if(islower(result)){
            total_score += result - 96;
        }
        else{
            total_score += result - 38;
        }
    }
    cout << total_score << endl;
}