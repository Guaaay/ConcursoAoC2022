#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <stack>
using namespace std;

string visualize_stacks(vector <stack<char>> stacks){
    string result = "";
    int i = 1;
    for(vector<stack<char>>::iterator it = stacks.begin() ; it != stacks.end(); ++it){
        stack<char>stacki=*it;
        result = result + "stack " + to_string(i) +  ": ";
        while(!stacki.empty()) {
            result = result +  stacki.top() + " ";
            stacki.pop();
        }       
        result = result + "\n";
        i++;
    }
    return result;
}

int main()
{
    string myText;
    ifstream MyReadFile("input");
    //initialize vector of stacks
    vector <stack<char>> stacks;
    for(int i = 0; i<9;i++){
        stack<char> stack;
        stacks.push_back(stack);
    }
    //Get initial crates information
    string rows[8];
    int i = 7;
    while (getline(MyReadFile, myText) && i >=0)
    {
        rows[i] = myText;
        i -= 1;
    }
    
    //Parse strings and push into stacks:
    for(int i = 0; i < 9; i++ ){
        string str = rows[i];
        int count = 0;
        for(int j = 1;j < str.length() && count < 9; j+=4){
            char crate = str[j];
            if(crate != ' '){
                stacks.at(count).push(crate);
            }
            count += 1;
        }
        
    }

    //continue parsing instructions

    i = 0;
    while (getline(MyReadFile, myText))
    {
        if(i == 0){
            i=i+1;
            continue;
        }
        int n_move = stoi(myText.substr(5, myText.find(" from")-5));
        int from = stoi(myText.substr(myText.find("from")+5, 1))-1;
        int to = stoi(myText.substr(myText.find("to")+3, 1))-1;
        //Perform operation
        vector<char> grab;
        for(int i = 0; i<n_move; i++){
            //Remove element from the stack
            char crate = stacks.at(from).top();
            stacks.at(from).pop();
            //Push element into "to" stack
            grab.push_back(crate);
        }

        for(std::vector<char>::reverse_iterator it = grab.rbegin() ; it != grab.rend(); ++it){
            stacks.at(to).push(*it);
        }

    }
    //Visualize stacks
    cout << visualize_stacks(stacks) << endl;
    MyReadFile.close();
}