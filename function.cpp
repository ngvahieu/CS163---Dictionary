#include"function.h"
// supporting functions
int charToIndex(char a){
    return a - 33;
}
vector<char> splitWord(string word) {
    vector<char> result;
    stringstream ss(word);
    char a;
    while (ss >> a) result.push_back(a);
    return result;
}
// main functions

vector<Word> getWordsFromFile(int choice) {
    vector<Word> dict;
   _setmode(fileno(stdin), _O_U16TEXT);
   _setmode(fileno(stdout), _O_U16TEXT);
   locale loc(locale(), new codecvt_utf8<wchar_t>);
    
    switch (choice) {
        case 1: { // emojis
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
                dict.push_back(temp);
            }
            fin.close();
            int i = 0;
            wfstream wfin; wfin.open("/dataSets/emotional.txt", ios::in);
            wchar_t check1;
            wstring firstTake, secondTake;
            while(!wfin.eof()) {
                getline(wfin, firstTake, L':');
                wfin.get(check1);
                if(check1 != ' ') {
                    if(check1 == ':') {
                        getline(wfin, secondTake, L'\n');
                        dict[i].secondKey = firstTake + check1;
                    }
                    else {
                        getline(wfin, secondTake, L':');
                        dict[i].secondKey = firstTake + L':' + check1 + secondTake;                        getline(wfin, secondTake, L'\n');
                    }
                }
                else { // ...:(space)...
                    getline(wfin, secondTake, L'\n');
                    dict[i].secondKey = firstTake;
                }
                ++i;
            }
            wfin.close();
        }
            break;
        case 2: { // slang
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
                dict.push_back(temp);
            }
            fin.close();
            int i = 0;
            wfstream wfin; wfin.open("/dataSets/slang.txt", ios::in);
            wchar_t check1;
            wstring firstTake, secondTake;
            while(!wfin.eof()) {
                getline(wfin, firstTake, L':');
                wfin.get(check1);
                if(check1 != ' ') {
                    if(check1 == ':') {
                        getline(wfin, secondTake, L'\n');
                        dict[i].secondKey = firstTake + check1;
                    }
                    else {
                        getline(wfin, secondTake, L':');
                        dict[i].secondKey = firstTake + L':' + check1 + secondTake;                        getline(wfin, secondTake, L'\n');
                    }
                }
                else { // ...:(space)...
                    getline(wfin, secondTake, L'\n');
                    dict[i].secondKey = firstTake;
                }
                ++i;
            }
            wfin.close();
        }
            break;
        case 3: { // Eng to Eng
            ifstream fin; fin.open("/dataSets/eng-eng.txt", ios::in);
            Word temp;
            string s;
            while(!fin.eof()) {
                getline(fin, temp.key, ':');
                getline(fin, temp.def, '\n');
                dict.push_back(temp);
            }
            fin.close();
            int i = 0;
            wfstream wfin; wfin.open("/dataSets/eng-eng.txt", ios::in);
            wstring w;
            while(!wfin.eof()) {
                getline(wfin, dict[i].secondKey, L':');
                getline(wfin, w, L'\n');
                ++i;
            }
            wfin.close();
        }
            break;
        case 4: { // Eng to Viet
            ifstream fin; fin.open("/dataSets/eng-viet.txt", ios::in);
            Word temp;
            string s;
            while(!fin.eof()) {
                getline(fin, temp.key, ':');
                getline(fin, temp.def, '\n');
                dict.push_back(temp);
            }
            fin.close();
            int i = 0;
            wfstream wfin; wfin.open("/dataSets/eng-viet.txt", ios::in);
            wstring w;
            while(!wfin.eof()) {
                getline(wfin, dict[i].secondKey, L':');
                getline(wfin, w, L'\n');
                ++i;
            }
            wfin.close();
        }
            break;
        case 5: { // Viet to Eng
            ifstream fin; fin.open("/dataSets/viet-eng.txt", ios::in);
            wfstream wfin; wfin.open("/dataSets/viet-eng.txt", ios::in);
            Word temp;
            string sp; wstring wp;
            while(!fin.eof()) {
                getline(fin, temp.key, '(');
                getline(fin, sp, ':');
                getline(wfin, wp, L'(');
                getline(wfin, temp.secondKey, L')');
                getline(fin, temp.def, '\n');
                getline(wfin, wp, L'\n');
                dict.push_back(temp);
            }
            fin.close();
            wfin.close();
        }
            break;
    }

    return dict;
}

