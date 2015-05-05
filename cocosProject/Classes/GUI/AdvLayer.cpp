#include "AdvLayer.h"
#include "GUI.h"

using namespace std;
using namespace cocos2d;

bool AdvLayer::init() {
    if(!LayerColor::initWithColor(Color4B(255,255,255,250))) 
        return false;
    auto size = Director::getInstance()->getVisibleSize();
    
    auto title = GUI::createLabelR("Good job!", 42);
    title->setColor(Color3B::BLACK);
    title->setPosition(size.width/2, size.height*0.85);
    addChild(title);
    
    auto title2 = GUI::createLabelR("Now it's time to take your prize! \n Fill your contacts to get \n a free English skype lesson!", 26, TextHAlignment::CENTER);
    title2->setColor(Color3B::BLACK);
    title2->setPosition(size.width/2, size.height*0.65);
    addChild(title2);
    
    const Size BUTTON_SIZE(size.width / 3, size.height / 6.6);
    
    // form
    auto s = Sprite::create("gap_gray.png");
    s->setScale(3.3, 0.6);
    s->setPosition(size.width * 0.65, size.height*0.45);
    addChild(s);
    auto lbl = GUI::createLabelR("Skype name:", 20);
    lbl->setColor(Color3B::BLACK);
    lbl->setPosition(size.width * 0.32, size.height*0.45);
    addChild(lbl);
    // end form
    
    // button send
    auto bSend = GUI::TextButton::create(
        BUTTON_SIZE, "submit", 
        [this]() {
        }, 
        Color3B::BLACK, Color3B::BLACK, Color3B::BLACK, Color3B::WHITE
    );
    bSend->setPosition(Vec2(size.width/2, size.height*0.20));
    addChild(bSend);
    // end button send
    
    // close button
    auto bClose = GUI::TextButton::create(
        Size(size.width / 10, size.height / 10), " X ", 
        [this]() {
            this->runAction(Sequence::create(DelayTime::create(0.3), CallFunc::create([this](){ this->removeFromParent(); }), NULL));
        }, 
        Color3B::BLACK, Color3B::BLACK, Color3B::BLACK, Color3B::WHITE, 23
    );
    bClose->setPosition(Vec2(size.width * 0.9, size.height*0.9));
    addChild(bClose);
    // end close button
    
    return true;
}









