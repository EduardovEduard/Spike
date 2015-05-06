#include "StartPlatformAsset.h"
#include "Utils.h"

using namespace cocos2d;

bool StartPlatformAsset::init() {
    if(!Node::init()) 
	return false;
    setContentSize(Size(200, 100));
    initView();
    initPhysics();
    return true;
}

void StartPlatformAsset::initView() {
    
}

void StartPlatformAsset::initPhysics() {
    auto pb = PhysicsBody::createBox(getContentSize());
    pb->setDynamic(false);
    setPhysicsBody(pb);
}



