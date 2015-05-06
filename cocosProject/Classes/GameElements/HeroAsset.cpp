#include "HeroAsset.h"
#include "Utils.h"

using namespace cocos2d;


HeroAsset* HeroAsset::create(const Size& size) {
    auto *pRet = new HeroAsset(); 
    if (pRet && pRet->init(size)) { 
        pRet->autorelease(); 
        return pRet; 
    } else { 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    } 
}

bool HeroAsset::init(const Size& s) {
    if(!Node::init()) 
	return false;
    setContentSize(s);
    //initSprite();
    initPhysics();
    return true;
}

void HeroAsset::initSprite() {
    auto s = Sprite::create("circle.png");
    s->setColor(Color3B::BLACK);
    s->setScale(0.3);
    addChild(s);
}

void HeroAsset::initPhysics() {
    auto pb = PhysicsBody::createBox(
	getContentSize(), PhysicsMaterial(.1f, .5f, .0f)
    );
    setPhysicsBody(pb);
}

void HeroAsset::setSpeedX(double sx) {
    auto pb = getPhysicsBody();
    pb->setVelocity(
	Vec2(sx, pb->getVelocity().y)
    );
}

void HeroAsset::addSpeedY(double sy) {
    auto pb = getPhysicsBody();
    pb->setVelocity(
	pb->getVelocity() + Vec2(0, sy)
    );
}


