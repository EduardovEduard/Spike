#include "ScoreManager.h"
#include "DataManager.h"

ScoreManager* ScoreManager::getInstance() {
    static ScoreManager instance;
    return &instance;
}

bool ScoreManager::init() { return true; }

int ScoreManager::getBestScore() {
    return DataManager::getInstance()->get("bestScore", 0);
}

bool ScoreManager::sendMyScore(int v) {
    if(getBestScore() >= v) return false;
    DataManager::getInstance()->put("bestScore", v);
    return true;
}
