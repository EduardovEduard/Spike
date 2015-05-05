#include "ResultsLayer.h"
#include "GUI.h"
#include "AdvLayer.h"

using namespace std;
using namespace cocos2d;

bool ResultsLayer::init() {
    if(!LayerColor::initWithColor(Color4B(255,255,255,200))) 
        return false;
    
    auto title = GUI::createLabelR("WIN", 42);
    title->setColor(Color3B::BLACK);
    auto size = Director::getInstance()->getVisibleSize();
    title->setPosition(size.width/2, size.height*0.72);
    addChild(title);
    initButtons();
    return true;
}

void ResultsLayer::initButtons() {
    auto size = Director::getInstance()->getVisibleSize();
    const Size BUTTON_SIZE(size.width / 3, size.height / 6.6);
    auto bRestart = GUI::TextButton::create(
        BUTTON_SIZE, "restart", 
        [this]() {
            if(_onRestart) _onRestart();
        }, 
        Color3B::BLACK, Color3B::BLACK, Color3B::BLACK, Color3B::WHITE
    );
    bRestart->setPosition(Vec2(size.width/2, size.height*0.5));
    addChild(bRestart);
    
    auto bReview = GUI::TextButton::create(
        BUTTON_SIZE, "next", 
        [this]() {
            if(_onNext) _onNext();
        }, 
        Color3B::BLACK, Color3B::BLACK, Color3B::BLACK, Color3B::WHITE
    );
    bReview->setPosition(Vec2(size.width/2, size.height*0.25));
    addChild(bReview);
    
    auto bBonus = GUI::TextButton::create(
        Size(size.width / 5, size.height / 10), "bonus", 
        [this]() {
            auto al = AdvLayer::create();
            this->addChild(al, 50);
        }, 
        Color3B::BLACK, Color3B::BLACK, Color3B::BLACK, Color3B::WHITE, 23
    );
    bBonus->setPosition(Vec2(size.width * 0.8, size.height*0.9));
    addChild(bBonus);
    
}








