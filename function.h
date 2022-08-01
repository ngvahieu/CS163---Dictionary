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
    Node* child[95]; // from 32->126 in ASCII
    bool isLastChar;
    vector<string> def;
    // vector<string> saves definitions.
    // just push if a node is a last character of a specific word.

    vector<pair<string, string>> defList;
    // only save to first character Node for searching definition.
    Node() {
        isLastChar = false;
        for (int i = 0; i < 95; i++) child[i] = nullptr;
        def.resize(0); defList.resize(0);
    }
};
struct Word {
    string key;
    string def;
};
class Dictionary {
public:
    vector<Node*> tree;
    // tree[0] stores emotional data set.
    // tree[1] stores slang words data set
    // tree[2] stores English to English data set.
    // tree[3] stores English to Vietnamese data set.
    // tree[4] stores VietNamese to English data set.
    Dictionary() {
        tree.resize(5);
        for (auto x : tree) x = nullptr;
    }

    void getAllWordsToTree(Node*& tree, int choice); // get all words in a specific file.
    Node* searchByKey(Node* tree, string key);
    bool searchByDef(string def, Node*& tree, string& ans, int& positionInDefList);
    bool addNewWord(Word newWord, Dictionary& dict, int choice);
    void historyOfSearch(vector<pair<string,vector<string>>> &his, string key, Node* pLastChar);// put in the menu of search key(after the searchByKey function)
    void viewHistoryWords(vector<pair<string,vector<string>>> his);
    bool addNewWord(Word newWord, Node*& tree);
    void editDef(Dictionary& dict, int choice, string key);
    void removeWord(Dictionary& dict, int choice, string key);
    void resetDictionary(Node*& tree, int choice);
    void removeFavWord(string word, int choice);
    void addFavWord(string word, int choice);

    /*void viewRanWord(Node*& tree, int choice);*/
    void viewRanWord(Node*& tree);

    void guessDef(Node*& tree, int choice);
    void guessWord(Node*& tree, int choice);
};
int ranNum(int min, int max); //return a random number in a range
int charToIndex(char a); // change a character to equivalent index in TrieNode.
vector<char> splitWord(string word); // split a word into characters.
vector<Word> getWordsFromFile(int choice);
void inputWordToTree(Node*& root, Word word); // put a word to tree
void saveTreeToFile(Node*& tree, int choice); // save Trie tree to text file.
void deleteTree(Node*& tree); // delete a Trie tree 
