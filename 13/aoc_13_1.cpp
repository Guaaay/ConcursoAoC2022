#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

struct element{
    //-1 if element is list
    int val = -1;
    //can be integers or more lists
    vector<element> elements;
};

//0 = elements are equal, -1 = left is smaller, 1, right is smaller
int compareElems(element elem1, element elem2){
    //both are numbers:
    if(elem1.val !=-1 && elem2.val !=-1){
        return (elem1.val < elem2.val)? -1: (elem2.val < elem1.val)? 1 : 0;
    }
    //both are lists
    else if(elem1.val == -1 && elem2.val == -1){
        //find biggest list
        if(elem1.elements.size() > elem2.elements.size()){
            for(int i = 0; i < elem2.elements.size(); i++){
                int res = compareElems(elem1.elements[i], elem2.elements[i]);
                //Left list is smaller
                if(res == -1){
                    return -1;
                }
                //Right list is smaller
                else if(res == 1){
                    return 1;
                }
                //keep going if there are still elements
            }
            //If for loop ends, it means we reached the end of list 2, so we are not in the right order
            return 1;
        }
        else if(elem1.elements.size() < elem2.elements.size()){
            for(int i = 0; i < elem1.elements.size(); i++){
                int res = compareElems(elem1.elements[i], elem2.elements[i]);
                //Left list is smaller
                if(res == -1){
                    return -1;
                }
                //Right list is smaller
                else if(res == 1){
                    return 1;
                }
                //keep going if there are still elements
            }
            //If for loop ends, it means we reached the end of list 1, so we are not in the right order
            return -1;
        }
        //Both lists are equal
        else{
            for(int i = 0; i < elem1.elements.size(); i++){
                int res = compareElems(elem1.elements[i], elem2.elements[i]);
                //Left list is smaller
                if(res == -1){
                    return -1;
                }
                //Right list is smaller
                else if(res == 1){
                    return 1;
                }
                //keep going if there are still elements
            }
            //If for loop ends, it means we reached the end of list 1, so lìsts are equal
            return 0;
        }
    }
    //One is a list and the other is a number
    else if(elem1.val==-1 && elem2.val !=-1){
        //Make elem2 a list that contains its value:
        element newElem;
        element value;
        value.val = elem2.val;
        newElem.elements.push_back(value);
        return compareElems(elem1,newElem);
    }
    else{
        //Make elem1 a list that contains its value:
        element newElem;
        element value;
        value.val = elem1.val;
        newElem.elements.push_back(value);
        return compareElems(newElem,elem2);
    }
}

int main(){
    string myText;
    ifstream MyReadFile("inputpt1");
    vector<element> all;
    while (getline(MyReadFile, myText))
    {
        if(myText == ""){
            continue;
        }
        stack<element> linestacc;
        element firstLine;
        linestacc.push(firstLine);
        for(int i = 0; i < myText.length(); i++){
            string c = myText.substr(i,1);
            if(i!=0){
                element elems;
                if(c == "["){
                    //linestacc.top().elements.push_back(elems);
                    linestacc.push(elems);
                }
                else if(c == ","){
                    continue;
                }
                else if(c == "]"){
                    if(linestacc.size()==1){
                        all.push_back(linestacc.top());
                        linestacc.pop();
                    }
                    else{
                        element current = linestacc.top();
                        linestacc.pop();
                        linestacc.top().elements.push_back(current);
                    }
                    
                }
                else {
                    if(i < myText.length() && myText.substr(i+1,1) != "," && myText.substr(i+1,1) != "]"){
                        elems.val = stoi(myText.substr(i,2));
                    }
                    else{
                        elems.val=(stoi(c));
                    }
                    
                    linestacc.top().elements.push_back(elems);
                }
            }
        }
        
    }
    
    int num_order = 0;
    int j = 1;
    for(int i = 1; i < all.size(); i+=2){
        element list1 = all[i-1];
        element list2 = all[i];
        int result = compareElems(list1,list2);
        if(result == -1){
            num_order += j;
        }
        j+=1;
    }
    cout << num_order << endl;
}