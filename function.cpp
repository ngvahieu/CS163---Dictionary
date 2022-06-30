#include"function.h"
// supporting functions
int charToIndex(char a) {
    return a - 32;
}
void deleteTree(Node*& tree) {
    if (!tree) return;
    for (int i = 0; i < 94; ++i) {
        deleteTree(tree->child[i]);
    }
    delete tree;
}
vector<char> splitWord(string word) {
    vector<char> result;
    stringstream ss(word);
    char a;
    while (ss >> a) result.push_back(a);
    return result;
}

vector<Word> getWordsFromFile(int choice) {
    vector<Word> dict;
    _setmode(fileno(stdin), _O_U16TEXT);
    _setmode(fileno(stdout), _O_U16TEXT);
    locale loc(locale(), new codecvt_utf8<wchar_t>);
    
    switch (choice) {
        case 0: { // emojis
            ifstream fin; fin.open("/dataSets/emotional.txt", ios::in);
            char check;
            string firstTaken, secondTaken;
            Word temp;
            while(!fin.eof()) {
                getline(fin, firstTaken, ':');
                fin.get(check);
                if(check != ' ') {
                    if(check == ':') {
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
            ifstream fin; fin.open("/dataSets/slang.txt", ios::in);
            Word temp;
            char check;
            string firstTaken, secondTaken, s;
            wstring w;
            while(!fin.eof()) {
                getline(fin, firstTaken, ':');
                fin.get(check);
                if(check != ' ') {
                    if(check == ':') {
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
            ifstream fin; fin.open("/dataSets/eng-eng.txt", ios::in);
            Word temp;
            string s;
            while(!fin.eof()) {
                getline(fin, temp.key, ':');
                fin.ignore(1);
                getline(fin, temp.def, '\n');
                dict.push_back(temp);
            }
            fin.close();
        }
            break;
        case 3: { // Eng to Viet
            ifstream fin; fin.open("/dataSets/eng-viet.txt", ios::in);
            Word temp;
            string s;
            while(!fin.eof()) {
                getline(fin, temp.key, ':');
                fin.ignore(1);
                getline(fin, temp.def, '\n');
                dict.push_back(temp);
            }
            fin.close();
        }
            break;
        case 4: { // Viet to Eng
            ifstream fin; fin.open("/dataSets/viet-eng.txt", ios::in);
            Word temp;
            while(!fin.eof()) {
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

// main functions
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
            Def.push_back(word.def);
            int x = charToIndex(first);
            if (!pCrawl->child[x]) pCrawl->child[x] = new Node();
            pCrawl->child[x]->defList.push_back({ Def,word.key });
        }
        pCrawl = pCrawl->child[index];
    }
    // mark last node as leaf
    pCrawl->isLastChar = true;
    vector<string> Def;
    Def.push_back(word.def);
    pCrawl->def.push_back(Def);
}
void Dictionary :: getAllWordsToTree(Node*& tree, int choice) {
    vector<Word> dic = getWordsFromFile(choice);
    for (int i = 0; i < dic.size(); i++) {
        inputWordToTree(tree, dic[i]);
    }
}

Node* Dictionary :: searchByKey(Node* tree, string key) {
    if(!tree) return NULL;
    Node* pCrawl = tree;
    for(int i = 0; i < key.length(); ++i) {
        int index = charToIndex(key[i]);
        if(!pCrawl->child[index]) return NULL;
        pCrawl = pCrawl->child[index];
    }
    if(pCrawl->isLastChar) {
        return pCrawl;
    }
    else return NULL;
}
void Dictionary :: editKey(Dictionary dict, int choice, string key, string newKey) {
    Node* lastChar = dict.searchByKey(dict.tree[choice], key);
    if(!lastChar) return;
    lastChar->isLastChar = false;
    for(int i = 0; i < lastChar->def.size(); ++i) {
        for(int j = 0; j < lastChar->def[i].size(); ++j) {
            Word w; w.key = newKey; w.def = last->def[i][j];
            inputWordToTree(dict.tree[choice], w);
        }
    }
}

