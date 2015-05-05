#include "Managers/ScenesManager.h"
#include "Managers/SoundsManager.h"
#include "Managers/LevelsManager.h"

#include "Scenes/MainScene.h"

#include <cocos2d.h>


using namespace cocos2d;


void ScenesManager::runWithMain() {
    _currentScene = nullptr;
    auto lvl = new Models::Level(LevelsManager::getInstance()->getFirstLevel());
    _currentScene = MainScene::create(lvl);
    auto director = Director::getInstance();
    director->runWithScene(_currentScene);
}

void ScenesManager::gotoMain(int num) {
    if(num > 3) return;
    _currentScene = nullptr;
    auto lvl = new Models::Level(LevelsManager::getInstance()->getLevel(num));
    _currentScene = MainScene::create(lvl);
    auto director = Director::getInstance();
    director->replaceScene(_currentScene);
}

ScenesManager::ScenesManager() {
}

void ScenesManager::onAppPause() {
    _currentScene->onAppPause();
}

void ScenesManager::onAppResume() {
    _currentScene->onAppResume();
}

void ScenesManager::hideByTag(const int tag) {
    if(!_currentScene) return;
    auto asset = _currentScene->getChildByTag(tag);
    if(!asset) return;
    asset->removeFromParent();
}

