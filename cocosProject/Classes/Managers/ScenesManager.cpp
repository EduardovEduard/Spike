#include "Managers/ScenesManager.h"
#include "Managers/SoundsManager.h"

#include "Scenes/GameScene.h"
#include "Scenes/SpringScene.h"

#include <cocos2d.h>


using namespace cocos2d;


void ScenesManager::runWithGame() {
    _currentScene = GameScene::create();
    auto director = Director::getInstance();
    director->runWithScene(_currentScene);
}

void ScenesManager::runWithSpring() {
    _currentScene = SpringScene::create();
    auto director = Director::getInstance();
    director->runWithScene(_currentScene);
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

