#include "WaterScene.h"
#include "GameElements/MeteorNode.h"
#include "GameElements/WaterNode.h"

#include <iostream>

using namespace cocos2d;

static const int TAG_WATER = 0x05;
static const int TAG_METEOR = 0x06;

void WaterScene::onMouseDown(Vec2 pt) {
    auto m = MeteorNode::create();
    m->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    m->setPosition(pt);
    m->setTag(TAG_METEOR);
    _meteors.emplace(m, MeteorInfo());
    addChild(m, 2);
}

bool WaterScene::init() {
    if (!BasicScene::initWithPhysics())
        return false;
    getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    _node = WaterNode::create();
    _node->setWaterPhysicsNodesTag(TAG_WATER);
    addChild(_node, 1);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(WaterScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    dropItem();
    return true;
}

/* HANDLERS */

bool WaterScene::onContactBegin(PhysicsContact& contact) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    auto isTagPair = [&](int tagA, int tagB) {
        if(!nodeA || !nodeB) return false;
        if (nodeA->getTag() == tagB && nodeB->getTag() == tagA) return true;
        if (nodeA->getTag() == tagA && nodeB->getTag() == tagB) return true;
        return false;
    };
    
    if(isTagPair(TAG_WATER, TAG_WATER)) return false;
    if(isTagPair(TAG_METEOR, TAG_METEOR)) return false;
    if(isTagPair(TAG_WATER, TAG_METEOR)) {
        MeteorNode* mn = dynamic_cast<MeteorNode*>(nodeA->getTag() == TAG_METEOR ? nodeA : nodeB);
        processMeteorCollision(mn);
        return false;
    }
    return true;
}

/* UPDATES */

/* TOOLS */

void WaterScene::processMeteorCollision(MeteorNode* meteor) {
    if(_meteors.find(meteor) == _meteors.end()) {
        return;
    }
    _meteors.erase(meteor);
    _node->touch(meteor);
}

void WaterScene::dropItem() {
    auto n = Node::create();
    n->setContentSize(Size(200, 10));
    n->setPhysicsBody(PhysicsBody::createBox(n->getContentSize()));
    addChild(n, 2);
    n->setPosition(getContentSize()/2);
}

