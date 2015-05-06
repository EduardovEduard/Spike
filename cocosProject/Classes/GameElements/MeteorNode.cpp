#include "MeteorNode.h"

using namespace cocos2d;

bool MeteorNode::init() {
    if(!Node::init()) 
	return false;
//    auto node = DrawNode::create();
    // node->drawSolidCircle(Vec2::ZERO, 30, 0, 4, 1, 1, Color4F::RED);
    auto physicsBody = PhysicsBody::createCircle(10);
    
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    setPhysicsBody(physicsBody);
    return true;
}