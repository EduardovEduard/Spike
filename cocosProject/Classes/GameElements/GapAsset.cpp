#include "GapAsset.h"
#include "GUI/GUI.h"
#include <cocos2d.h>

using namespace cocos2d;
using namespace Models;
using namespace std;

bool GapAsset::init() {
    if(!Node::init())
        return false;
    _sprite = Sprite::create("gap_gray.png");
    _sprite->setScale(0.5, 0.03);
    _sprite->setPosition({0, -20});
    _sprite->setColor(Color3B::GRAY);
    addChild(_sprite, 1);
    return true;
}

void GapAsset::unlock(Article a, bool success) {
    auto label = GUI::createLabelR(articleToStr(a), 20);
    label->setColor(Color3B::BLACK);
    label->setPosition({0, -8});
    addChild(label, 2);
    if(success){
        _sprite->setColor(Color3B::GREEN);
    } else {
        _sprite->setColor(Color3B::RED);
    }
}











