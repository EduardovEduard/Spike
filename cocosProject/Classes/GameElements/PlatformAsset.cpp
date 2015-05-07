#include "PlatformAsset.h"
#include "Utils.h"

using namespace cocos2d;


PlatformAsset* PlatformAsset::create(const Size& size) {
    auto *pRet = new PlatformAsset(); 
    if (pRet && pRet->init(size)) {
        pRet->autorelease(); 
        return pRet; 
    } else { 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    } 
}

bool PlatformAsset::init(const Size& s) {
    if(!Node::init()) 
	return false;
    setContentSize(s);
    initSprite();
    initPhysics();
    return true;
}

void PlatformAsset::initSprite() {
    auto s = Sprite::create("platform.png");
    Utils::setNodeHeight(s, getContentSize().height);
    s->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    s->setPosition(Vec2::ZERO);
    s->setScaleX(getContentSize().width / s->getContentSize().width);
    s->setScaleY(getContentSize().height / s->getContentSize().height);
    addChild(s);
}

void PlatformAsset::initPhysics() {
    auto pb = PhysicsBody::createBox(
	getContentSize()
    );
    setPhysicsBody(pb);
}


