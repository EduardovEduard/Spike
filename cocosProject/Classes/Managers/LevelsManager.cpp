#include "LevelsManager.h"
#include <sstream>
#include "Utils.h"
#include <iostream>

using namespace Models;
using namespace std;

LevelsManager* LevelsManager::getInstance() {
    static LevelsManager instance;
    return &instance;
}

Level LevelsManager::getFirstLevel() {
    return getLevel(1);
}

Level LevelsManager::getLevel(int i) {
    Level res;
    res.num = i;
    stringstream filePath;
    filePath << "levels/level" << i << ".txt";
    stringstream strm(Utils::getFileData(filePath.str()));
    string line;
    // read answers
    while(true) {
        getline(strm, line);
        if(line == string("---")) break;
        Answer answ;
        stringstream sss(line);
        string str;
        sss >> str; // read article
        answ.article = articleFromStr(str.substr(0, str.size()-1));
        answ.description = line.substr(str.find(":") + 2);
        res.answers.push_back(answ);
        //cout << "add item:" << articleToStr(answ.article) << " :: " << answ.description << endl;
    }
    
    int lineNum = 0;
    int gapNum = 0;
    while(true) {
        if(!strm.good()) break;
        getline(strm, line);
        LevelRow row;
        stringstream sss(line);
        string str;
        cout << "------" << endl;
        cout << line << endl;
        int colNum = 0;
        while(sss >> str) {
            row.tokens.push_back(str);
            if(str == "???") {
                res.answers.at(gapNum).line = lineNum;
                res.answers.at(gapNum).col = colNum;
                gapNum++;
            }
            colNum++;
            //cout << "<>" << str << endl;
        }
        res.rows.push_back(row);
        lineNum++;
    
    }
    
    return res;
}









