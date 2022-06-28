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

void StringToWString(std::wstring &ws, const std::string &s) {
    std::wstring wsTmp(s.begin(), s.end());
    ws = wsTmp;
}
vector<Word> getWordsFromFile(int choice) {
    vector<Word> dict;
//    _setmode(fileno(stdin), _O_U16TEXT);
//    _setmode(fileno(stdout), _O_U16TEXT);
//    locale loc(locale(), new codecvt_utf8<wchar_t>);
    
    switch (choice) {
        case 1: { // emojis
            ifstream fin; fin.open("/dataSets/emotional.txt", ios::in);
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
                        s = firstTaken + check; temp.key = s; temp.def = secondTaken;
                        StringToWString(w, s); temp.secondKey = w;
                    }
                    else {
                        getline(fin, secondTaken, ':');
                        s = firstTaken + ':' + check + secondTaken; temp.key = s;
                        StringToWString(w, s); temp.secondKey = w;
                        getline(fin, secondTaken, '\n');
                        temp.def = secondTaken;
                    }
                }
                else { // ...:(space)...
                    getline(fin, secondTaken, '\n');
                    s = firstTaken;temp.key = s;
                    StringToWString(w, s); temp.secondKey = w;
                    temp.def = check + secondTaken;
                }
                dict.push_back(temp);
            }
            fin.close();
        }
            break;
        case 2: { // slang
            ifstream fin; fin.open("/dataSets/emotional.txt", ios::in);
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
                        s = firstTaken + check; temp.key = s; temp.def = secondTaken;
                        StringToWString(w, s); temp.secondKey = w;
                    }
                    else {
                        getline(fin, secondTaken, ':');
                        s = firstTaken + ':' + check + secondTaken; temp.key = s;
                        StringToWString(w, s); temp.secondKey = w;
                        getline(fin, secondTaken, '\n');
                        temp.def = secondTaken;
                    }
                }
                else { // ...:(space)...
                    getline(fin, secondTaken, '\n');
                    s = firstTaken; temp.key = s;
                    StringToWString(w, s); temp.secondKey = w;
                    temp.def = check + secondTaken;
                }
                dict.push_back(temp);
            }
            fin.close();
        }
            break;
        case 3: { // Eng to Eng
            ifstream fin; fin.open("/dataSets/eng-eng.txt", ios::in);
            Word temp;
            string s; wstring w;
            while(!fin.eof()) {
                getline(fin, temp.key, ':');
                s = temp.key; StringToWString(w, s); temp.secondKey = w;
                getline(fin, temp.def, '\n');
                dict.push_back(temp);
            }
            fin.close();
        }
            break;
        case 4: { // Eng to Viet
            ifstream fin; fin.open("/dataSets/eng-viet.txt", ios::in);
            Word temp;
            string s; wstring w;
            while(!fin.eof()) {
                getline(fin, temp.key, ':');
                s = temp.key; StringToWString(w, s); temp.secondKey = w;
                getline(fin, temp.def, '\n');
                dict.push_back(temp);
            }
            fin.close();
        }
            break;
        case 5: { // Viet to Eng
            ifstream fin; fin.open("dataSets/viet-eng.txt", ios::in);
            wfstream wfin; wfin.open("dataSets/viet-eng.txt", ios::in);
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
