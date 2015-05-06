#include "GameScene.h"
#include "GameElements/MeteorNode.h"
#include "GameElements/WaterNode.h"
#include "GameElements/StartPlatformAsset.h"
#include "GameElements/FinishPlatformAsset.h"

#include <iostream>

using namespace cocos2d;

static const int TAG_WATER = 0x05;
static const int TAG_METEOR = 0x06;


/* INTIS */

bool GameScene::init() {
    if (!BasicScene::initWithPhysics())
        return false;
  
    initPhysics();
    initStartPlatform();
    initFinishPlatform();
    initPlatforms();
    initWater();
    return true;
}

void GameScene::initPhysics() {
    getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameScene::initPlatforms() {
    dropItem(100, 200);
}

void GameScene::initStartPlatform() {
    Vec2 sz(_size.width * 0.1, _size.height / 1.9);
    auto sp = StartPlatformAsset::create(Size(sz));
    sp->setPosition(sz/2);
    addChild(sp, 1);
}

void GameScene::initFinishPlatform() {
    Vec2 sz(_size.width * 0.1, _size.height / 1.9);
    auto sp = FinishPlatformAsset::create(Size(sz));
    sp->setPosition(Vec2(_size.width, _size.height / 1.9) - sz/2);
    addChild(sp, 1);
}

void GameScene::initWater() {
    _waterNode = WaterNode::create(Size(
	_size.width * 0.8, _size.height / 2
    ));
    _waterNode->setWaterPhysicsNodesTag(TAG_WATER);
    _waterNode->setPosition(Vec2(_size.width * 0.1, 0));
    addChild(_waterNode, 1);
}


/* HANDLERS */

void GameScene::onMouseDown(Vec2 pt) {
    dropMeteor(pt);
}

bool GameScene::onContactBegin(PhysicsContact& contact) {
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

void GameScene::processMeteorCollision(MeteorNode* meteor) {
    if(_meteors.find(meteor) == _meteors.end()) {
        return;
    }
    _meteors.erase(meteor);
    _waterNode->touch(meteor);
}

void GameScene::dropItem(double xOffset, double length) {
    auto n = Node::create();
    n->setContentSize(Size(length, 10));
    n->setPhysicsBody(PhysicsBody::createBox(n->getContentSize()));
    addChild(n, 2);
    n->setPosition(getContentSize()/2);
}

void GameScene::dropMeteor(Vec2 pt) {
    auto m = MeteorNode::create();
    m->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    m->setPosition(pt);
    m->setTag(TAG_METEOR);
    _meteors.emplace(m, MeteorInfo());
    addChild(m, 2);
}

