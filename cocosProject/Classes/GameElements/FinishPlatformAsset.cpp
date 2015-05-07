#include "FinishPlatformAsset.h"
#include "Utils.h"

using namespace cocos2d;

FinishPlatformAsset* FinishPlatformAsset::create(const Size& size) {
    auto *pRet = new FinishPlatformAsset(); 
    if (pRet && pRet->init(size)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    } 
}

bool FinishPlatformAsset::init(const Size& size) {
    if(!Node::init()) 
	return false;
    setContentSize(size);
    setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    initView();
    initPhysics();
    return true;
}

void FinishPlatformAsset::initView() {
    auto s = Sprite::create("finishPlatform.png");
    s->setPosition(Vec2(0, getContentSize().height));
    s->setAnchorPoint(Vec2(0.017, 1 - 0.1625));
    Utils::setNodeWidth(s, getContentSize().width * 1.017);
    addChild(s);
}

void FinishPlatformAsset::initPhysics() {
    auto pb = PhysicsBody::createBox(getContentSize());
    pb->setDynamic(false);
    setPhysicsBody(pb);
}



