#include "SpringScene.h"

#include <iostream>


using namespace cocos2d;


bool SpringScene::init() {
    if(!BasicScene::initWithPhysics())
        return false;
    getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    initNodes();
    return true;
}

void SpringScene::initNodes() {
    auto n1 = Node::create();
    n1->setPhysicsBody(PhysicsBody::createBox(Size(100, 100)));
    n1 ->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(n1);
    auto size = getContentSize();
    n1->setPosition(Vec2(size.width/2, size.height/2));
}


/* STATE */

/* HANDLERS */

/* UPDATES */










