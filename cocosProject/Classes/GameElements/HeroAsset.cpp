#include "HeroAsset.h"
#include "Utils.h"

using namespace cocos2d;

bool HeroAsset::init() {
    if(!Node::init()) 
	return false;
    initSprite();
    return true;
}

void HeroAsset::initSprite() {
    auto s = Sprite::create("circle.png");
    s->setColor(Color3B::BLACK);
    s->setScale(0.3);
    addChild(s);
}


