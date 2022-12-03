#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
    string myText;
    ifstream MyReadFile("input1.txt");
    int acc = 0;
    int max[3] = {0,0,0};
    int curr;
    while (getline (MyReadFile, myText)) {
        if(myText==""){
            for(int i = 0; i<3;i++)
            {
                if(acc > max[i]){
                    max[i] = acc;
                    break;
                }
            }
            acc = 0;
        }
        else{
            curr = stoi(myText);
            acc += curr;
        }
    }
    int result = 0;
    for(int i = 0; i < 3; i++){
        result += max[i];
    }
    cout << result << endl;
    MyReadFile.close(); 
}