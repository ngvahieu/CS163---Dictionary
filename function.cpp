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
    vector<Word> getWordsFromFile(int choice) {
    vector<Word> dict;
//    _setmode(fileno(stdin), _O_U16TEXT);
//    _setmode(fileno(stdout), _O_U16TEXT);
//    locale loc(locale(), new codecvt_utf8<wchar_t>);
    
    switch (choice) {
        case 1: { // emojis
            ifstream fin; fin.open("/Users/apple/Documents/Tài Liệu đại học/Năm 1/HK3/Data Structure/project/projectHung/projectHung/dataSets/emotional.txt", ios::in);
            Word temp;
            char check;
            string sp, firstTaken, secondTaken;
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
                    temp.key = firstTaken; temp.def = check + secondTaken;
                }
                dict.push_back(temp);
            }
            fin.close();
        }
            break;
        case 2: { // slang
            ifstream fin; fin.open("/Users/apple/Documents/Tài Liệu đại học/Năm 1/HK3/Data Structure/project/projectHung/projectHung/dataSets/slang.txt", ios::in);
            Word temp;
            char check;
            string sp, firstTaken, secondTaken;
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
                    temp.key = firstTaken; temp.def = check + secondTaken;
                }
                dict.push_back(temp);
            }
            fin.close();
        }
            break;
        case 3: { // Eng to Eng
            ifstream fin; fin.open("/Users/apple/Documents/Tài Liệu đại học/Năm 1/HK3/Data Structure/project/projectHung/projectHung/dataSets/eng-eng.txt", ios::in);
            Word temp;
            string sp;
            while(!fin.eof()) {
                getline(fin, temp.key, ':');
                getline(fin, temp.def, '\n');
                dict.push_back(temp);
            }
            fin.close();
        }
            break;
        case 4: { // Eng to Viet
            ifstream fin; fin.open("/Users/apple/Documents/Tài Liệu đại học/Năm 1/HK3/Data Structure/project/projectHung/projectHung/dataSets/eng-viet.txt", ios::in);
            Word temp;
            string sp;;
            while(!fin.eof()) {
                getline(fin, temp.key, ':');
                getline(fin, temp.def, '\n');
                dict.push_back(temp);
            }
            fin.close();
        }
            break;
        case 5: { // Viet to Eng
            ifstream fin; fin.open("/Users/apple/Documents/Tài Liệu đại học/Năm 1/HK3/Data Structure/project/projectHung/projectHung/dataSets/viet-eng.txt", ios::in);
            wfstream wfin; wfin.open("/Users/apple/Documents/Tài Liệu đại học/Năm 1/HK3/Data Structure/project/projectHung/projectHung/dataSets/viet-eng.txt", ios::in);
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
}