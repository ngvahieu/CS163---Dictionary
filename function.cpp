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
bool Dictionary::addNewWord(Word newWord, Dictionary& dict, int choice) {
    Node* lastChar = searchByKey(dict.tree[choice], newWord.key);
    if (lastChar) {
        for (int i = 0; i < lastChar->def.size(); i++) {
            if (strstr(lastChar->def[i].c_str(), newWord.def.c_str())) return false; // already exists in the tree
        }
    }
    inputWordToTree(dict.tree[choice], newWord);
    return true;
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
        getline(cin, newDef, '\n');
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
// Hung
void Dictionary::historyOfSearch(vector<pair<string, vector<string>>>& his, string key, Node* pLastChar) {
    his.push_back({ key, pLastChar->def });
}
// Hung
void Dictionary::viewHistoryWords(vector<pair<string, vector<string>>> his) {
    cout << "HISTORY OF SEARCH WORDS" << endl;
    for (int i = 0; i < his.size(); ++i) {
        cout << i + 1 << ". " << his[i].first << ":" << endl;
        for (int j = 0; j < his[i].second.size(); ++j)
            cout << " " << i + 1 << "." << j + 1 << " " << his[i].second[j] << endl;
    }
    cout << endl;
}
void Dictionary::removeWord(Dictionary& dict, int choice, string key) {
    Node* pLastChar = dict.searchByKey(dict.tree[choice], key);
    if (pLastChar) {
        int select = 0, pos;
        string oldDef;
        for (int i = 0; i < pLastChar->def.size(); ++i) {
            cout << i + 1 << ": " << pLastChar->def[i] << endl;
        }
        cout << "Choose the one you want to remove: "; cin >> select;
        oldDef = pLastChar->def[select - 1];
        // delete in def
        pLastChar->def.erase(pLastChar->def.begin() + select - 1);
        // delete in defList
        dict.searchByDef(oldDef, dict.tree[choice], key, pos);
        dict.tree[choice]->child[oldDef[0]]->defList.erase(dict.tree[choice]->defList.begin() + pos);
        if (pLastChar->def.size() == 0) {
            pLastChar->isLastChar = false;
        }
    }
    else
        cout << "Not found the word!" << endl;
}

//Khoa
int ranNum(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void Dictionary::viewRanWord(Node*& tree)
{
    if (!tree) return;
    int indexChar = ranNum(0, 94);
    while (!tree->child[indexChar] || tree->child[indexChar]->defList.size() == 0)
        indexChar = ranNum(0, 94);
    int indexDef = ranNum(0, tree->child[indexChar]->defList.size() - 1);
    cout << "Random word: " << tree->child[indexChar]->defList[indexDef].second << "\n";
    cout << "Definition -> " << tree->child[indexChar]->defList[indexDef].first << "\n";
}

//Khoa
vector<string> readFavfile(int choice)
{
    vector<string> favList;
    string filename;

    switch (choice)
    {
    case 0:  // emojis
        filename = "favEmotional.txt";
        break;
    case 1: // slang
        filename = "favSlang.txt";
        break;
    case 2: // Eng to Eng
        filename = "favEng-Eng.txt";
        break;
    case 3: // Eng to Viet
        filename = "favEng-Viet.txt";
        break;
    case 4: // Viet to Eng
        filename = "favViet-Eng.txt";
        break;
    default:
        break;
    }

    ifstream fin;
    string str;
    fin.open("favList/" + filename, ios::in);
    if (fin)
    {
        while (getline(fin, str, '\n'))
            favList.push_back(str);
        fin.close();
    }

    return favList;
}

void Dictionary::addFavWord(string word, int choice)
{
    vector<string> favList = readFavfile(choice);
    string filename;

    switch (choice)
    {
    case 0:  // emojis
        filename = "favEmotional.txt";
        break;
    case 1: // slang
        filename = "favSlang.txt";
        break;
    case 2: // Eng to Eng
        filename = "favEng-Eng.txt";
        break;
    case 3: // Eng to Viet
        filename = "favEng-Viet.txt";
        break;
    case 4: // Viet to Eng
        filename = "favViet-Eng.txt";
        break;
    default:
        break;
    }

    ofstream fout;
    if (favList.size() < 5)
    {
        fout.open("favList/" + filename, ios::app);
        if (fout)
        {
            if (favList.size() != 0) fout << '\n';
            fout << word;
            fout.close();
        }
    }
    else
    {
        cout << "Favourite list can only store 5 words maximum! Please remove other words first.\n";
        viewFavList(choice);
        string str;
        cout << "Type word you want to remove: ";
        getline(cin, str, '\n');
        removeFavWord(str, choice);
        addFavWord(word, choice);
    }
}

void viewFavList(int choice)
{
    vector<string> favList = readFavfile(choice);
    cout << "Your favourite list: " << '\n';
    for (int i = 0; i < favList.size(); i++)
        cout << i + 1 << ". " << favList[i] << '\n';
}

//Khoa
vector<string> readHisfile(int choice)
{
    vector<string> hisList;
    string filename;

    switch (choice)
    {
    case 0:  // emojis
        filename = "hisEmotional.txt";
        break;
    case 1: // slang
        filename = "hisSlang.txt";
        break;
    case 2: // Eng to Eng
        filename = "hisEng-Eng.txt";
        break;
    case 3: // Eng to Viet
        filename = "hisEng-Viet.txt";
        break;
    case 4: // Viet to Eng
        filename = "hisViet-Eng.txt";
        break;
    default:
        break;
    }

    ifstream fin;
    string str;
    fin.open("historyList/" + filename, ios::in);
    if (fin)
    {
        while (getline(fin, str, '\n'))
            hisList.push_back(str);
        fin.close();
    }

    return hisList;
}

void addHisWord(string word, int choice)
{
    vector<string> hisList = readHisfile(choice);
    string filename;

    switch (choice)
    {
    case 0:  // emojis
        filename = "hisEmotional.txt";
        break;
    case 1: // slang
        filename = "hisSlang.txt";
        break;
    case 2: // Eng to Eng
        filename = "hisEng-Eng.txt";
        break;
    case 3: // Eng to Viet
        filename = "hisEng-Viet.txt";
        break;
    case 4: // Viet to Eng
        filename = "hisViet-Eng.txt";
        break;
    default:
        break;
    }

    ofstream fout;
    if (hisList.size() < 5)
    {
        fout.open("hisList/" + filename, ios::app);
        if (fout)
        {
            if (hisList.size() != 0) fout << '\n';
            fout << word;
            fout.close();
        }
    }
    else
    {
        fout.open("hisList/" + filename);
        if (fout)
        {
            for (int i = 1; i < hisList.size(); i++)
                fout << hisList[i] << '\n';
            fout << word;
            fout.close();
        }
    }
}

void viewHisList(int choice)
{
    vector<string> hisList = readHisfile(choice);
    cout << "Your search history: " << '\n';
    for (int i = hisList.size() - 1; i >= 0; i--)
        cout << hisList[i] << '\n';
}

//Q.Hieu 
vector<Word> getWordsFromfavFile(int choice) {
    vector<Word> dict;

    switch (choice) {
    case 0: { // emojis
        ifstream fin; fin.open("favEmotional.txt", ios::in);
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
        ifstream fin; fin.open("favSlang.txt", ios::in);
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
        ifstream fin; fin.open("favEng-Eng.txt", ios::in);
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
        ifstream fin; fin.open("favEng-Viet.txt", ios::in);
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
        ifstream fin; fin.open("favViet-Eng.txt", ios::in);
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
void Dictionary::removeFavWord(string word, int choice) {
    ifstream fin;
    ofstream fout;
    switch (choice) {
    case 0: //emotional 
    {
        vector<Word> vt = getWordsFromfavFile(0);
        fout.open("favEmotional.txt", ios::trunc);
        if (!fout.is_open()) cout << "Can not open the file ";
        int select = 0;
        for (int i = 0; i < vt.size(); i++) {
            fout << i + 1 << ": " << vt[i].def << endl;
            cout << i + 1 << ": " << vt[i].def << endl;
        }
        cout << "Choose the one you want to remove: "; cin >> select;
        vt.erase(vt.begin() + select - 1);
        /*vt->def.erase(vt->def.begin() + select - 1);*/
        fout.close();
    }
    case 1: // slang
    {
        vector<Word> vt = getWordsFromfavFile(1);
        fout.open("favSlang.txt", ios::trunc);
        if (!fout.is_open()) cout << "Can not open the file ";
        int select = 0;
        for (int i = 0; i < vt.size(); i++) {
            fout << i + 1 << ": " << vt[i].def << endl;
            cout << i + 1 << ": " << vt[i].def << endl;
        }
        cout << "Choose the one you want to remove: "; cin >> select;
        vt.erase(vt.begin() + select - 1);
        /*vt->def.erase(vt->def.begin() + select - 1);*/
        fout.close();
    }
    case 2: { // eng to eng 
        vector<Word> vt = getWordsFromfavFile(2);
        fout.open("favEng-Eng.txt", ios::trunc);
        if (!fout.is_open()) cout << "Can not open the file ";
        int select = 0;
        for (int i = 0; i < vt.size(); i++) {
            fout << i + 1 << ": " << vt[i].def << endl;
            cout << i + 1 << ": " << vt[i].def << endl;
        }
        cout << "Choose the one you want to remove: "; cin >> select;
        vt.erase(vt.begin() + select - 1);
        /*vt->def.erase(vt->def.begin() + select - 1);*/
        fout.close();
    }
    case 3: {// eng to viet 
        vector<Word> vt = getWordsFromfavFile(3);
        fout.open("favEng-Viet.txt", ios::trunc);
        if (!fout.is_open()) cout << "Can not open the file ";
        int select = 0;
        for (int i = 0; i < vt.size(); i++) {
            fout << i + 1 << ": " << vt[i].def << endl;
            cout << i + 1 << ": " << vt[i].def << endl;
        }
        cout << "Choose the one you want to remove: "; cin >> select;
        vt.erase(vt.begin() + select - 1);
        /*vt->def.erase(vt->def.begin() + select - 1);*/
        fout.close();
    }
    case 4: {//viet to eng 
        vector<Word> vt = getWordsFromfavFile(4);
        fout.open("favViet-Eng.txt", ios::trunc);
        if (!fout.is_open()) cout << "Can not open the file ";
        int select = 0;
        for (int i = 0; i < vt.size(); i++) {
            fout << i + 1 << ": " << vt[i].def << endl;
            cout << i + 1 << ": " << vt[i].def << endl;
        }
        cout << "Choose the one you want to remove: "; cin >> select;
        vt.erase(vt.begin() + select - 1);
        /*vt->def.erase(vt->def.begin() + select - 1);*/
        fout.close();
    }
    }
}
void Dictionary::guessDef(Node*& tree) {
    if (!tree) return;
    int select;
    int indexChar1 = ranNum(0, 94);
    int indexChar2 = ranNum(0, 94);
    int indexChar3 = ranNum(0, 94);
    int indexChar4 = ranNum(0, 94);
    bool check = false;
    while (!tree->child[indexChar1] || tree->child[indexChar1]->defList.size() == 0
        || !tree->child[indexChar2] || tree->child[indexChar2]->defList.size() == 0
        || !tree->child[indexChar3] || tree->child[indexChar3]->defList.size() == 0
        || !tree->child[indexChar4] || tree->child[indexChar4]->defList.size() == 0
        || indexChar1 == indexChar2 || indexChar1 == indexChar3 || indexChar1 == indexChar4
        || indexChar2 == indexChar3 || indexChar2 == indexChar4 || indexChar3 == indexChar4) {
        indexChar1 = ranNum(0, 94);
        indexChar2 = ranNum(0, 94);
        indexChar3 = ranNum(0, 94);
        indexChar4 = ranNum(0, 94);
    }
    int indexDef1 = ranNum(0, tree->child[indexChar1]->defList.size() - 1);
    int indexDef2 = ranNum(0, tree->child[indexChar2]->defList.size() - 1);
    int indexDef3 = ranNum(0, tree->child[indexChar3]->defList.size() - 1);
    int indexDef4 = ranNum(0, tree->child[indexChar4]->defList.size() - 1);
    int choice1 = ranNum(1, 4);
    int choice2 = ranNum(1, 4);
    int choice3 = ranNum(1, 4);
    int choice4 = ranNum(1, 4);
    while (choice1 == choice2 || choice1 == choice3 || choice1 == choice4 || choice2 == choice3 || choice2 == choice4 || choice3 == choice4) {
        choice1 = ranNum(1, 4);
        choice2 = ranNum(1, 4);
        choice3 = ranNum(1, 4);
        choice4 = ranNum(1, 4);
    }
    cout << "Random word: " << tree->child[indexChar1]->defList[indexDef1].second << "\n";
    cout << "Definitions : " << endl;
    for (int i = 1; i < 5; i++) {
        if (choice1 == i)  cout << i << ". " << tree->child[indexChar1]->defList[indexDef1].first << endl;
        if (choice2 == i)  cout << i << ". " << tree->child[indexChar2]->defList[indexDef2].first << endl;
        if (choice3 == i)  cout << i << ". " << tree->child[indexChar3]->defList[indexDef3].first << endl;
        if (choice4 == i)  cout << i << ". " << tree->child[indexChar4]->defList[indexDef4].first << endl;
    }
    cout << "Which the answer do you choose : ";
    cin >> select;
    if (select == choice1) cout << "Correct!";
    else cout << "Wrong!";
}
void Dictionary::guessWord(Node*& tree) {
    if (!tree) return;
    int select;
    int indexChar1 = ranNum(0, 94);
    int indexChar2 = ranNum(0, 94);
    int indexChar3 = ranNum(0, 94);
    int indexChar4 = ranNum(0, 94);
    bool check = false;
    while (!tree->child[indexChar1] || tree->child[indexChar1]->defList.size() == 0 || !tree->child[indexChar2] || tree->child[indexChar2]->defList.size() == 0 || !tree->child[indexChar3] || tree->child[indexChar3]->defList.size() == 0 || !tree->child[indexChar4] || tree->child[indexChar4]->defList.size() == 0 || indexChar1 == indexChar2 || indexChar1 == indexChar3 || indexChar1 == indexChar4 || indexChar2 == indexChar3 || indexChar2 == indexChar4 || indexChar3 == indexChar4) {
        indexChar1 = ranNum(0, 94);
        indexChar2 = ranNum(0, 94);
        indexChar3 = ranNum(0, 94);
        indexChar4 = ranNum(0, 94);
    }
    int indexDef1 = ranNum(0, tree->child[indexChar1]->defList.size() - 1);
    int indexDef2 = ranNum(0, tree->child[indexChar2]->defList.size() - 1);
    int indexDef3 = ranNum(0, tree->child[indexChar3]->defList.size() - 1);
    int indexDef4 = ranNum(0, tree->child[indexChar4]->defList.size() - 1);
    cout << "Random Definition: " << tree->child[indexChar1]->defList[indexDef1].first << "\n";
    cout << "Word : " << endl;
    cout << "1. " << tree->child[indexChar2]->defList[indexDef2].second << endl;
    cout << "2. " << tree->child[indexChar3]->defList[indexDef3].second << endl;
    cout << "3. " << tree->child[indexChar1]->defList[indexDef1].second << endl;
    cout << "4. " << tree->child[indexChar4]->defList[indexDef4].second << "\n";
    cout << "Which the answer you choose : ";
    cin >> select;
    if (select == 3) cout << "Correct!";
    else cout << "Wrong!";
}
void Dictionary::resetDictionary(Node*& tree, int choice) {
    deleteTree(tree);
    switch (choice) {
    case 0: {
        getAllWordsToTree(tree, 0);
    }
    case 1: {
        getAllWordsToTree(tree, 1);
    }
    case 2: {
        getAllWordsToTree(tree, 2);
    }
    case 3: {
        getAllWordsToTree(tree, 3);
    }
    case 4: {
        getAllWordsToTree(tree, 4);
    }
    }
}
