#include "GameOverLayer.h"
#include "GUI.h"

using namespace std;
using namespace cocos2d;

bool GameOverLayer::init() {
    if(!LayerColor::initWithColor(Color4B(0,0,0,200))) 
        return false;
    auto title = GUI::createLabelR("GAME OVER", 42);
    title->setColor(Color3B::WHITE);
    auto size = Director::getInstance()->getVisibleSize();
    title->setPosition(size.width/2, size.height*0.72);
    addChild(title);
    initButtons();
    return true;
}

void GameOverLayer::initButtons() {
    auto size = Director::getInstance()->getVisibleSize();
    const Size BUTTON_SIZE(size.width / 3, size.height / 6.6);
    auto bRestart = GUI::TextButton::create(
        BUTTON_SIZE, "restart", 
        [this]() {
            if(_onRestart) _onRestart();
        }, 
        Color3B::WHITE, Color3B::WHITE, Color3B::WHITE, Color3B::BLACK
    );
    bRestart->setPosition(Vec2(size.width/2, size.height*0.5));
    addChild(bRestart);
    
    auto bReview = GUI::TextButton::create(
        BUTTON_SIZE, "review", 
        [this]() {
            if(_onReview) _onReview();
        }, 
        Color3B::WHITE, Color3B::WHITE, Color3B::WHITE, Color3B::BLACK
    );
    bReview->setPosition(Vec2(size.width/2, size.height*0.25));
    addChild(bReview);
}
