#include"function.h"
// supporting functions
int charToIndex(char a) {
    return a - 32;
}
vector<char> splitWord(string word) {
    vector<char> result;
    stringstream ss(word);
    char a;
    while (ss >> a) result.push_back(a);
    return result;
}
// Hung
vector<Word> getWordsFromFile(int choice) {
    vector<Word> dict;

    switch (choice) {
    case 0: { // emojis
        ifstream fin; fin.open("dataSets/emotional.txt", ios::in);
        char check;
        string firstTaken, secondTaken;
        Word temp;
        while (!fin.eof()) {
            getline(fin, firstTaken, ':');
            fin.get(check);
            if (check != ' ') {
                if (check == ':') {
                    getline(fin, secondTaken, '\n');
                    temp.key = firstTaken + check;
                    temp.def = secondTaken;
                }
                else {
                    getline(fin, secondTaken, ':');
                    temp.key = firstTaken + ':' + check + secondTaken;
                    getline(fin, secondTaken, '\n');
                    temp.def = secondTaken;
                }
            }
            else { // ...:(space)...
                getline(fin, secondTaken, '\n');
                temp.key = firstTaken;
                temp.def = check + secondTaken;
            }
            temp.def.erase(temp.def.begin());
            dict.push_back(temp);
        }
        fin.close();
    }
          break;
    case 1: { // slang
        ifstream fin; fin.open("dataSets/slang.txt", ios::in);
        Word temp;
        char check;
        string firstTaken, secondTaken, s;
        while (!fin.eof()) {
            getline(fin, firstTaken, ':');
            fin.get(check);
            if (check != ' ') {
                if (check == ':') {
                    getline(fin, secondTaken, '\n');
                    temp.key = firstTaken + check; temp.def = secondTaken;
                }
                else {
                    getline(fin, secondTaken, ':');
                    temp.key = firstTaken + ':' + check + secondTaken;
                    getline(fin, secondTaken, '\n');
                    temp.def = secondTaken;
                }
            }
            else { // ...:(space)...
                getline(fin, secondTaken, '\n');
                temp.key = firstTaken;
                temp.def = check + secondTaken;
            }
            temp.def.erase(temp.def.begin());
            dict.push_back(temp);
        }
        fin.close();
    }
          break;
    case 2: { // Eng to Eng
        ifstream fin; fin.open("dataSets/eng-eng.txt", ios::in);
        Word temp;
        while (!fin.eof()) {
            getline(fin, temp.key, ':');
            fin.ignore(1);
            getline(fin, temp.def, '\n');
            dict.push_back(temp);
        }
        fin.close();
    }
          break;
    case 3: { // Eng to Viet
        ifstream fin; fin.open("dataSets/eng-viet.txt", ios::in);
        Word temp;
        while (!fin.eof()) {
            getline(fin, temp.key, ':');
            fin.ignore(1);
            getline(fin, temp.def, '\n');
            dict.push_back(temp);
        }
        fin.close();
    }
          break;
    case 4: { // Viet to Eng
        ifstream fin; fin.open("dataSets/viet-eng.txt", ios::in);
        Word temp;
        while (!fin.eof()) {
            getline(fin, temp.key, ':');
            fin.ignore(1);
            getline(fin, temp.def, '\n');
            dict.push_back(temp);
        }
        fin.close();
    }
          break;
    }
    return dict;
}
void deleteTree(Node*& tree) {
    if (!tree) return;
    for (int i = 0; i < 95; ++i) {
        deleteTree(tree->child[i]);
    }
    delete tree;
}
// main functions
// V.Hieu
void inputWordToTree(Node*& root, Word word)
{
    if (!root) root = new Node();
    Node* pCrawl = root;

    for (int i = 0; i < word.key.length(); i++) {
        int index = charToIndex(word.key[i]);
        if (!pCrawl->child[index])
            pCrawl->child[index] = new Node();

        if (i == 0) {
            char first = word.def[0];
            for (int j = 0; j < word.def.length(); j++) {
                if (word.def[j] != ' ') {
                    first = word.def[j];
                    break;
                }
            }
            vector<string> Def;
            int x = charToIndex(first);
            if (!pCrawl->child[x]) pCrawl->child[x] = new Node();
            pCrawl->child[x]->defList.push_back({ word.def,word.key });
        }
        pCrawl = pCrawl->child[index];
    }

    // mark last node as leaf
    pCrawl->isLastChar = true;
    pCrawl->def.push_back(word.def);
}
// V.Hieu
void Dictionary::getAllWordsToTree(Node*& tree, int choice) {
    vector<Word> dic = getWordsFromFile(choice);
    for (int i = 0; i < dic.size(); i++) {
        inputWordToTree(tree, dic[i]);
    }
}
// V.Hieu
bool Dictionary::searchByDef(string def, Node*& tree, string& ans, int& positionInDefList) {
    int index = charToIndex(def[0]);
    Node* cur = tree->child[index];
    if (cur) {
        for (int i = 0; i < cur->defList.size(); ++i) {
            if (strstr(cur->defList[i].first.c_str(), def.c_str())) {
                ans = cur->defList[i].second;
                positionInDefList = i;
                return true;
            }
        }
    }
    return false;
}
// V.Hieu
bool Dictionary::addNewWord(Word newWord,Dictionary& dict,int choice) {
    Node* lastChar = searchByKey(dict.tree[choice], newWord.key);
    if (lastChar) {
        for (int i = 0; i < lastChar->def.size(); i++) {
            if (strstr(lastChar->def[i].c_str(), newWord.def.c_str())) return false; // already exists in the tree
        }
    }
    inputWordToTree(dict.tree[choice], newWord);
}
// Hung
Node* Dictionary::searchByKey(Node* tree, string key) {
    if (!tree) return NULL;
    Node* pCrawl = tree;
    for (int i = 0; i < key.length(); ++i) {
        int index = charToIndex(key[i]);
        if (!pCrawl->child[index]) return NULL;
        pCrawl = pCrawl->child[index];
    }
    if (pCrawl->isLastChar) {
        return pCrawl;
    }
    else return NULL;
}
// Hung
void Dictionary::editDef(Dictionary& dict, int choice, string key) {
    int pos, select;
    string oldDef, newDef;
    // search key
    Node* last = dict.searchByKey(dict.tree[choice], key);
    if (last) {
        for (int i = 0; i < last->def.size(); ++i) {
            cout << i + 1 << ". " << last->def[i] << endl;
        }
        cout << "Which one do you want to edit?(Enter a number)" << endl;
        do {
            cin >> select;
            if (select < 1 || select > last->def.size()) {
                cout << "invalid choice ! input again" << endl;
            }
        } while (select < 1 || select > last->def.size());
        oldDef = last->def[select - 1];
        cout << "Change " << select << " to: ";
        cin.ignore();
        getline(cin, newDef,'\n');
        // delete the old def in def(lastNode)
        last->def.erase(last->def.begin() + select - 1);
        // delete the old def in defList(Node has a list of defs start by that Node's character)
        dict.searchByDef(oldDef, dict.tree[choice], key, pos);
        int index = charToIndex(oldDef[0]);
        dict.tree[choice]->child[index]->defList.erase(dict.tree[choice]->child[index]->defList.begin() + pos);
        // add newWord into tree
        Word w; w.key = key; w.def = newDef;
        inputWordToTree(dict.tree[choice], w);
        cout << "Editing successed!" << endl;
        return;
    }
    else {
        cout << "Key can't be found" << endl;
        return;
    }
}