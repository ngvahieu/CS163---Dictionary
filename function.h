#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;
struct Node {
    Node* child[94]; // from 33->126 in ASCII
    bool isLeaf;
	bool add;    
    bool remove;
    vector<string> def;   // if isLeaf = true => push new definition of word in def.          
};
class Dictionary{
public: 
    vector<pair<string,Node*>> tab1; // tab1 stores emojis data sets.
    vector<pair<string,Node*>> tab2; // tab2 stores slang words data sets
	vector<pair<string,Node*>> tab3; // tab3 stores English to English data sets.
	vector<pair<string,Node*>> tab4; // tab4 stores English to Vietnamese data sets
	vector<pair<string,Node*>> tab5; // tab5 stores VietNamese to English data sets

    void getFileName(vector<pair<string,Node*>>& tab); // order: 1->5, get all file names in the same data set.
    void getAllWords(vector<pair<string,Node*>>& tab); // get all words in a specific file.
    string searchForKeyword(string keyword,vector<pair<string,Node*>>& tab);
    string searchForDef(string def,vector<pair<string,Node*>>& tab);
    void viewHistoryWords();
    void addNewWord(string word,string def,vector<pair<string,Node*>>& tab);
    void editWord(string word,vector<pair<string,Node*>>& tab);
    void removeWord(string word,vector<pair<string,Node*>>& tab);
    void resetDictionary(vector<pair<string,Node*>>& tab);
    void removeFavWord(string word);
    void addFavWord(string word);
    void viewRanWord(vector<pair<string,Node*>>& tab);
    void guessDef(vector<pair<string,Node*>>& tab);
    void guessWord(vector<pair<string,Node*>>& tab);
};
int charToIndex(char a); // change a character to equivalent index in TrieNode
vector<char> splitWord(string word); // split a word into characters.
