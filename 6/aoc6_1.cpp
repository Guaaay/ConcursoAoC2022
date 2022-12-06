#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <queue>
using namespace std;


int main()
{
    string myText;
    char byte = 0;
    char last = 0;
    int diff = 0;
    int result = 0;
    int num_distinct = 4;
    ifstream MyReadFile("input");
    queue<char> q;

    while (MyReadFile.get(byte))
    {
        if(q.size()<num_distinct){
            q.push(byte);
        }
        else if(q.size() == num_distinct){
            q.pop();
            q.push(byte);
        }
        unordered_set<char> s;
        queue<char> q_copy = q;
        while(!q_copy.empty()){
            s.insert(q_copy.front());
            q_copy.pop();
        }
        if(s.size() == num_distinct){
            result = MyReadFile.tellg();
            break;
        }
    }
    cout << result << endl;
    MyReadFile.close();
}