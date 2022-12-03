#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
    string myText;
    ifstream MyReadFile("input1.txt");
    int acc = 0;
    int max = 0;
    int curr;
    while (getline (MyReadFile, myText)) {
        // Output the text from the file
        if(myText==""){
            if(acc > max){
                max = acc;
            }
            acc = 0;
        }
        else{
            curr = stoi(myText);
            acc += curr;
        }
    }
    cout << max << endl;
    MyReadFile.close(); 
}