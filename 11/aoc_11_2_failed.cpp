#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

vector<string> split(string x, char delim = ' ')
{
    x += delim; //includes a delimiter at the end so last word is also read
    vector<string> splitted;
    string temp = "";
    for (int i = 0; i < x.length(); i++)
    {
        if (x[i] == delim)
        {
            splitted.push_back(temp); //store words in "splitted" vector
            temp = "";
            i++;
        }
        temp += x[i];
    }
    return splitted;
}

struct item{
    int original;
    vector<int> factors;
};

class Monkey{
private:
    vector <item> items;
    //False is sum, true is multiplication
    bool mul;
    //The value by which to modify item's worry level
    int opModifier;
    //The value to use for checking the monkey to throw to
    int divide_check;
    bool modIsold = false;

public:
    pair<int,int> monk_alts;
    int id;
    int inspections = 0;
    Monkey(int num = 0, bool SoM = false, int opMod = 0, int divider = 0, pair<int,int> monks = {0,0}){
        id = num;
        mul = SoM;
        opModifier = opMod;
        divide_check = divider;
        monk_alts = monks;
    }

    //Setters
    void setID(int num){
        id = num;
    }
    void setOP(bool SoM){
        mul = SoM;
    }
    void setOpMod(int opMod){
        if(opMod == -1){
            modIsold = true;
        }
        opModifier = opMod;
    }
    void setDivider(int divider){
        divide_check = divider;
    }
    int getItems(){
        return items.size();
    }
    //Returns the id of the monkey to which it will throw the item
    //and the worry value of the item
    pair<int,item> inspectItem(){
        inspections += 1;
        item itemtoinspect;
        itemtoinspect.original = items.front().original;
        itemtoinspect.factors = items.front().factors;
        items.erase(items.begin());
        if(modIsold){
            opModifier = itemtoinspect.original;
        }
        if(mul){
            itemtoinspect.factors.push_back(opModifier);
        }
        else{
            itemtoinspect.original = itemtoinspect.original + opModifier;
            for(int factor : itemtoinspect.factors){
                if(itemtoinspect.original%factor!=0){
                    itemtoinspect.factors.erase(itemtoinspect.factors.begin());
                }
            }
        }
        //Calculate monkey to throw to:
        int monk;
        //check if "divide check" is in the factors list

        if(itemtoinspect.original%divide_check==0
            || find(itemtoinspect.factors.begin(), itemtoinspect.factors.end(), divide_check) != itemtoinspect.factors.end()){
            monk = monk_alts.first;
        }
        else{
            monk = monk_alts.second;
        }
        
        return {monk,itemtoinspect};
    }

    void addItem(item item){
        items.push_back(item);
    }
};


int main()
{
    string myText;
    ifstream MyReadFile("input_test");
    //Make monkeys
    int numMonkeys = 4;
    int num_rounds = 10000;
    Monkey * monkeys[numMonkeys];
    int i = 0;
    while (getline(MyReadFile, myText))
    {
        vector<string> parsed = split(myText);
        if(parsed.size() > 1){
            if(parsed.at(0) == "Monkey"){
                Monkey * monk = new Monkey();
                monk->setID(stoi(parsed.at(1)));
                monkeys[stoi(parsed.at(1))] = monk;
                i = stoi(parsed.at(1));
            }
            else if(parsed.at(1) == " Starting"){
                std::vector<string>::iterator it = parsed.begin();
                ++it;
                ++it;
                ++it;
                while (it != parsed.end())
                {
                    int itemVal = stoi(*it);
                    item itemtoAdd;
                    itemtoAdd.original = itemVal;
                    monkeys[i]->addItem(itemtoAdd);
                    ++it;
                }
            }
            else if(parsed.at(1) == " Operation:"){
                if(parsed.at(6) == "old"){
                    monkeys[i]->setOpMod(-1);
                }
                else{
                    monkeys[i]->setOpMod(stoi(parsed.at(6)));
                }
                if(parsed.at(5)=="*"){
                    monkeys[i]->setOP(true);
                }
                else{
                    monkeys[i]->setOP(false);
                }
                
            }
            else if(parsed.at(1) == " Test:"){
                monkeys[i]->setDivider(stoi(parsed.at(4)));
            }
            else if(parsed.at(3) == "true:"){
                monkeys[i]->monk_alts.first = stoi(parsed.at(7));
            }
            else if(parsed.at(3) == "false:"){
                monkeys[i]->monk_alts.second = stoi(parsed.at(7));
            }
        }
    }
    //Rounds
    
    for(int round = 0; round < num_rounds; round++){
        for(int monkey = 0; monkey < numMonkeys; monkey++){
            int numItems = monkeys[monkey]->getItems();
            for(int k = 0;k<numItems;k++){
                pair<int,item> to_throw = monkeys[monkey]->inspectItem();
                monkeys[to_throw.first]->addItem(to_throw.second);
            }
        }
    }
    vector<int>inspections;

    for(int i = 0; i < numMonkeys; i++){
        inspections.push_back(monkeys[i]->inspections);
    }
    long int max1;
    vector<int>::iterator max = max_element(inspections.begin(),inspections.end());
    inspections.erase(max);
    max1 = *max;
    long int max2 = *max_element(inspections.begin(),inspections.end());
    long long int monkey_business = max1*max2;
    cout << "Monkey Business: " << monkey_business << endl;
}