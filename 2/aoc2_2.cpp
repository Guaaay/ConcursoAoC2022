#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int r_p_s (string op, string play){
    if(op == "A" && play == "X"){
        return 0+3;
    }
    else if(op == "A" && play == "Y"){
        return 3+1;
    }
    else if(op == "A" && play == "Z"){
        return 6+2;
    }
    else if(op == "B" && play == "X"){
        return 0+1;
    }
    else if(op == "B" && play == "Y"){
        return 3+2;
    }
    else if(op == "B" && play == "Z"){
        return 6+3;
    }
    else if(op == "C" && play == "X"){
        return 0+2;
    }
    else if(op == "C" && play == "Y"){
        return 3+3;
    }
    else {
        return 6+1;
    }
}

int main () {
    string myText;
    ifstream MyReadFile("input");
    string delimiter = " ";
    string enemy_play;
    string my_play;
    int total_score = 0;
    while (getline (MyReadFile, myText)) {
        enemy_play = myText.substr(0, myText.find(delimiter));
        my_play = myText.substr(myText.find(delimiter)+1, myText.length());
        total_score += r_p_s(enemy_play,my_play);
    }
    cout << total_score << endl;
}