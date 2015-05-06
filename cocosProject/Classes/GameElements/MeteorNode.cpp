#include "MeteorNode.h"

#include <random>

using namespace cocos2d;

bool MeteorNode::init() {
    if(!Node::init()) 
        return false;

    static std::random_device randomDevice;
    static std::mt19937 mt{randomDevice()};
    std::uniform_real_distribution<double> dist(100, 300);

    auto sprite = Sprite::create("meteor.png");
    addChild(sprite);

    auto physicsBody = PhysicsBody::createCircle(10);
    physicsBody->setVelocity(Vec2(dist(mt), 0));

    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setPhysicsBody(physicsBody);
    return true;
}
