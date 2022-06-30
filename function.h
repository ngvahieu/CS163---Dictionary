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
    bool add;
    bool remove;
    vector<vector<string>> def;
    // vector<string> saves definitions.
    // just push if a node is a last character of a specific word.

    vector<pair<vector<string>, string>> defList;
    // only save to first character Node for searching definition.
    Node() {
        isLastChar = false; add = false; remove = false;
        for (int i = 0; i < 95; i++) child[i] = nullptr;
    }
};
struct Word {
    string key;
    string def;
};
class Dictionary {
public:
     Dictionary() {
        tree.resize(5);
        for (auto x : tree) x = nullptr;
    }
    vector<Node*> tree;
    void getAllWordsToTree(Node*& tree, int choice); // get all words in a specific file.
    Node* searchByKey(Node* tree, string key);
    string searchByDef(string def, Node*& tree, int choice);
    void viewHistoryWords(int choice);
    void addNewWord(string word, string def, Node*& tree, int choice);
    void editKey(Dictionary dict, int choice, string key, string newKey);
    void removeWord(string word, Node*& tree, int choice);
    void resetDictionary(Node*& tree, int choice);
    void removeFavWord(string word, int choice);
    void addFavWord(string word, int choice);
    void viewRanWord(Node*& tree, int choice);
    void guessDef(Node*& tree, int choice);
    void guessWord(Node*& tree, int choice);
};
int charToIndex(char a); // change a character to equivalent index in TrieNode.
vector<char> splitWord(string word); // split a word into characters.
vector<Word> getWordsFromFile(int choice);
void inputWordToTree(Node*& root, Word word); // put a word to tree
void saveTreeToFile(Node*& tree, int choice); // save Trie tree to text file.
void deleteTree(Node*& tree); // delete a Trie tree