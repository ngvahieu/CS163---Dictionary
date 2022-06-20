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
    Node* tab1; // tab1 stores emojis data sets.
    Node* tab2; // tab2 stores slang words data sets
	Node* tab3; // tab3 stores English to English data sets.
	Node* tab4; // tab4 stores English to Vietnamese data sets
	Node* tab5; // tab5 stores VietNamese to English data sets

    void getAllWords(Node*& tab); // get all words in a specific file.
    string searchForKeyword(string keyword,Node*& tab);
    string searchForDef(string def,Node*& tab);
    void viewHistoryWords();
    void addNewWord(string word,string def,Node*& tab);
    void editWord(string word,Node*& tab);
    void removeWord(string word,Node*& tab);
    void resetDictionary(Node*& tab);
    void removeFavWord(string word);
    void addFavWord(string word);
    void viewRanWord(Node*& tab);
    void guessDef(Node*& tab);
    void guessWord(Node*& tab);
};
int charToIndex(char a); // change a character to equivalent index in TrieNode
vector<char> splitWord(string word); // split a word into characters.
void saveTreeToFile(Node*& tab); // save Trie tree to txt file
