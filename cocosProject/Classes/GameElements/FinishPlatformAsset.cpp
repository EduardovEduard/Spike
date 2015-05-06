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
    // TODO: special thing fro finish
    auto s = Sprite::create("gap_green.png");
    s->setPosition(Vec2::ZERO);
    addChild(s);
}

void FinishPlatformAsset::initPhysics() {
    auto pb = PhysicsBody::createBox(getContentSize());
    pb->setDynamic(false);
    setPhysicsBody(pb);
}



