#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include <Windows.h>
#include <codecvt>
#include <locale>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
using namespace std;
struct Node {
    Node* child[94]; // from 33->126 in ASCII
    bool isLastChar;
	bool add;    
    bool remove;
    vector<pair<wstring,vector<string>>> def; 
    // wstring used for saving Vietnamese words in case some Vietnamese words coincide after eliminating signs.
    // vector<string> saves definitions.
    // just push if a node is a last character of a specific word.
    vector<pair<vector<string>,wstring>> defList; 
    // only save to first character Node for searching definition.
};
struct word{
    string key;
    string def;
};
class Dictionary{
public: 
    Node* tree1; // tree1 stores emojis data set.
    Node* tree2; // tree2 stores slang words data set
	Node* tree3; // tree3 stores English to English data set.
	Node* tree4; // tree4 stores English to Vietnamese data set.
	Node* tree5; // tree5 stores VietNamese to English data set.

    void getAllWords(Node*& tree); // get all words in a specific file.
    string searchForKeyword(string keyword,Node*& tree);
    string searchForDef(string def,Node*& tree);
    void viewHistoryWords();
    void addNewWord(string word,string def,Node*& tree);
    void editWord(string word,Node*& tree);
    void removeWord(string word,Node*& tree);
    void resetDictionary(Node*& tree);
    void removeFavWord(string word);
    void addFavWord(string word);
    void viewRanWord(Node*& tree);
    void guessDef(Node*& tree);
    void guessWord(Node*& tree);
};
int charToIndex(char a); // change a character to equivalent index in TrieNode.
vector<char> splitWord(string word); // split a word into characters.
void saveTreeToFile(Node*& tree); // save Trie tree to text file.
