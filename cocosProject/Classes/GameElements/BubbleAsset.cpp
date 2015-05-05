#include "BubbleAsset.h"
#include "GUI/GUI.h"
#include <cocos2d.h>

using namespace cocos2d;
using namespace std;

bool BubbleAsset::init() {
    if(!Scale9Sprite::initWithFile("btn_active.png"))
        return false;
    setColor(Color3B::BLACK);
    return true;
}

void BubbleAsset::setText(const string& str) {
    if(_label) {
        _label->removeFromParent();
    }
    _label = GUI::createLabelR(str, 14);
    _label->setColor(Color3B::WHITE);
    Size sz(
        _label->getContentSize().width + 10,
        _label->getContentSize().height + 10
    );
    setContentSize(sz);
    _label->setPosition(getContentSize()/2);
    addChild(_label);
}











