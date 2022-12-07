#include "tree.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include<vector>
#include<numeric>

using namespace std;

struct node{
    string name;
    bool isDir;
    int size;
};



void print_tree(const tree<node>& tr, tree<node>::pre_order_iterator it, tree<node>::pre_order_iterator end)
	{
	if(!tr.is_valid(it)) return;
	int rootdepth=tr.depth(it);
	std::cout << "-----" << std::endl;
	while(it!=end) {
		for(int i=0; i<tr.depth(it)-rootdepth; ++i) 
			std::cout << "  ";
		std::cout << (*it).name << " - " << (*it).size << std::endl << std::flush;
		++it;
		}
	std::cout << "-----" << std::endl;
	}


// splits a std::string into vector<string> at a delimiter
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




ifstream MRFile("input");

void construct_tree(tree<node> tr, tree<node>::pre_order_iterator current_node){
    string myText;
    while(getline(MRFile,myText)){
        vector<string> line = split(myText,' ');
        if(line.at(0) == "dir"){
            node nodeinfo;
            nodeinfo.isDir = true;
            nodeinfo.name = line.at(1);
            nodeinfo.size = 0;
            tr.append_child(current_node, nodeinfo);
        }
        else if(line.at(0) == "$"){
            if(line.at(1) == "cd"){
                if(line.at(2) == ".."){
                    return;
                }
                else{
                    construct_tree(tr,find_if(current_node.begin(),current_node.end(),[&currname = line.at(2)](const node& n) -> bool { return currname == n.name;}));
                }
            }
        }
        else{
            node nodeinfo;
            nodeinfo.isDir = false;
            nodeinfo.name = line.at(1);
            nodeinfo.size = stoi(line.at(0));
            tr.append_child(current_node, nodeinfo);
        }
    }
    return;
}

//Part 1
int traverse_size(tree<node> tr, tree<node>::pre_order_iterator current_node, int *total){
    int mySize = 0;
    if(!(*current_node).isDir){
        mySize = (*current_node).size;
    }
    else{
        tree<node>::sibling_iterator sib=tr.begin(current_node);
        while(sib!=tr.end(current_node)) {
            mySize += traverse_size(tr,sib,total);
            ++sib;
        }
        if(mySize <= 100000){
            *total = *total + mySize;
        }
    }
    return mySize;
}

//Part 2
int traverse_delete(tree<node> tr, vector<int> * dirs, tree<node>::pre_order_iterator current_node, int target){
    int mySize = 0;
    if(!(*current_node).isDir){
        mySize = (*current_node).size;
    }
    else{
        tree<node>::sibling_iterator sib=tr.begin(current_node);
        while(sib!=tr.end(current_node)) {
            mySize += traverse_delete(tr,dirs,sib,target);
            ++sib;
        }
        if(mySize >= target){
            (*dirs).push_back(mySize);
        }
    }
    return mySize;
}

int main(){
    tree<node> filesystem; 
    tree<node>::pre_order_iterator root;
    tree<node>::iterator top = filesystem.begin();
    node root_node;
    root_node.isDir = true;
    root_node.name = "root";
    root_node.size = 0;
    root=filesystem.insert(top, root_node);
    //skip cd /
    string xd;
    getline(MRFile,xd);
    construct_tree(filesystem,root);
    //print_tree(filesystem,filesystem.begin(),filesystem.end());
    vector<int> dirs;
    int total = 0;
    int total_size = traverse_size(filesystem, root, &total);
    int curr_unused = 70000000 - total_size;
    int target = 30000000 - curr_unused;
    total_size = traverse_delete(filesystem,&dirs,root, target);

    cout << "Total size: " << total_size << endl;
    cout << "size<= 100000: " << total << endl;
    cout << "Minimum size of dir to free up space: " << *std::min_element(dirs.begin(), dirs.end()) << endl;
}
    
    