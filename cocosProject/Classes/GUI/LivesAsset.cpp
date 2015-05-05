#include "LivesAsset.h"

using namespace std;
using namespace cocos2d;

bool LivesAsset::init() {
    if(!Node::init()) return false;
    initIcons();
    return true;
}

void LivesAsset::initIcons() {
    for(int i = 0; i < 5; i++) {
        auto s = Sprite::create("circle.png");
        s->setColor(Color3B::BLACK);
        s->setScale(0.2);
        s->setPosition(Vec2(18 * i, 0));
        addChild(s);
        _icons.push(s);
    }
}

void LivesAsset::removeLife() {
    if(_icons.empty()) return;
    _icons.front()->removeFromParent();
    _icons.pop();
}