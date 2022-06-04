#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
struct Node {
    Node* child[94]; // from 33->126 in ASCII
    bool isLeaf;
	bool add;    
    bool remove;
    vector<string> def;   // if isLeaf = true => push new definition of word in def.          
};
class Dictionary{

};

