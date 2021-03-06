#include "StartPlatformAsset.h"
#include "Utils.h"

using namespace cocos2d;

StartPlatformAsset* StartPlatformAsset::create(const Size& size) {
    StartPlatformAsset *pRet = new StartPlatformAsset(); 
    if (pRet && pRet->init(size)) { 
        pRet->autorelease(); 
        return pRet; 
    } else { 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    } 
}

bool StartPlatformAsset::init(const Size& size) {
    if(!Node::init()) 
	return false;
    setContentSize(size);
    setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    initView();
    initPhysics();
    return true;
}

void StartPlatformAsset::initView() {
    auto s = Sprite::create("startPlatform.png");
    s->setAnchorPoint(Vec2(0.97, 1-0.685));
    s->setPosition(getContentSize());
    Utils::setNodeWidth(s, getContentSize().width * (1/0.97));
    addChild(s);
}

void StartPlatformAsset::initPhysics() {
    auto pb = PhysicsBody::createBox(getContentSize());
    pb->setDynamic(false);
    setPhysicsBody(pb);
}



