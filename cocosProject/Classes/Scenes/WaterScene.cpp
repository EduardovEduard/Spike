#include "WaterScene.h"
#include "GameElements/MeteorNode.h"
#include "GameElements/WaterNode.h"
#include "GameElements/StartPlatformAsset.h"
#include "GameElements/FinishPlatformAsset.h"
#include "GameElements/PlatformAsset.h"

#include <cassert>
#include <iostream>
#include <utility>

using namespace cocos2d;
using namespace std;

static const int TAG_WATER = 0x05;
static const int TAG_METEOR = 0x06;
static const int TAG_START_PLATFROM = 0x07;
static const int TAG_FINISH_PLATFROM = 0x08;
static const int TAG_PLATFORM = 0x09;
static const int TAG_HERO = 0x0A;

/* INTIS */

bool WaterScene::init() {
    if (!BasicScene::initWithPhysics())
        return false;
    initPhysics();
    initWater();
    initPlatforms();
    return true;
}

void WaterScene::initPhysics() {
    //getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(WaterScene::onContactBegin, this);
    //contactListener->onContactPreSolve = CC_CALLBACK_2(WaterScene::onContactPredSolve, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void WaterScene::initPlatforms() {
    vector<pair<double, double>> plfs;
    plfs.emplace_back(0.1, 0.1);
    plfs.emplace_back(0.25, 0.12);
    plfs.emplace_back(0.44, 0.18);
    plfs.emplace_back(0.62, 0.1);
    plfs.emplace_back(0.8, 0.05);
    double w = _waterNode->getContentSize().width;
    for(auto p: plfs) {
	addPlatform(
	    _waterNode->getPosition().x + w * p.first, w * p.second
	);
    }
}

void WaterScene::initWater() {
    _waterNode = WaterNode::create(Size(
	_size.width * (1 - 0.15 * 1.23 - 0.15), _size.height / 10
    ));
    _waterNode->setWaterPhysicsNodesTag(TAG_WATER);
    _waterNode->setPosition(Vec2(_size.width * 0.15, 0));
    addChild(_waterNode, 1);
    //_waterNode->touch(Vec2(100, 0), 7, 0);
}


/* UPDATES */

void WaterScene::update(float delta) {
    BasicScene::update(delta);
}


/* HANDLERS */

void WaterScene::onMouseDown(Vec2 pt) {
    _waterNode->touch(pt, 10);
}

bool WaterScene::onContactBegin(PhysicsContact& contact) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    auto isTagPair = [&](int tagA, int tagB) {
        if(!nodeA || !nodeB) return false;
        if (nodeA->getTag() == tagB && nodeB->getTag() == tagA) return true;
        if (nodeA->getTag() == tagA && nodeB->getTag() == tagB) return true;
        return false;
    };
    
//    if(isTagPair(TAG_HERO, TAG_START_PLATFROM) || 
//       isTagPair(TAG_HERO, TAG_FINISH_PLATFROM) || 
//       isTagPair(TAG_HERO, TAG_PLATFORM)
//    ) {
//	onHeroTouchFloor();
//    }

    if(isTagPair(TAG_WATER, TAG_WATER)) return false;
    if(isTagPair(TAG_METEOR, TAG_METEOR)) return false;
    if(isTagPair(TAG_WATER, TAG_METEOR)) {
        MeteorNode* mn = dynamic_cast<MeteorNode*>(nodeA->getTag() == TAG_METEOR ? nodeA : nodeB);
        processMeteorCollision(mn);
        return false;
    }
    
    auto getPlatform = [&]() -> Node* {
	if (nodeA->getTag() == TAG_PLATFORM)
	    return nodeA;
	return nodeB;
    };
    
    if (isTagPair(TAG_WATER, TAG_PLATFORM)) {
	auto platform = getPlatform();
	_waterNode->pushUpwards(platform);
	return true;
    }
    
//    if(isTagPair(TAG_WATER, TAG_HERO)) {
//	auto pb = _hero->getPhysicsBody();
//	pb->setVelocity(pb->getVelocity() * 0.2);
//	return false;
//    }
    return true;
}

bool WaterScene::onContactPreSolve(
    PhysicsContact& contact, PhysicsContactPreSolve& solve
) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    auto isTagPair = [&](int tagA, int tagB) {
        if(!nodeA || !nodeB) return false;
        if (nodeA->getTag() == tagB && nodeB->getTag() == tagA) return true;
        if (nodeA->getTag() == tagA && nodeB->getTag() == tagB) return true;
        return false;
    };
    
//    if(isTagPair(TAG_PLATFORM, TAG_HERO)) {
//	//solve.setSurfaceVelocity(Vec2(-100, 0));
//	solve.setFriction(100);
//	return true;
//    }
    
    if(isTagPair(TAG_WATER, TAG_PLATFORM)) {
	solve.setFriction(0.01);
	solve.setRestitution(0);
	solve.ignore();
	
	cout << "fr: " << solve.getFriction() << endl;
	cout << "rs: " << solve.getRestitution() << endl;
	cout << "vl: " << solve.getSurfaceVelocity().x << ", " << solve.getSurfaceVelocity().y << endl;
	return true;
    }
    
    return true;
}

/* TOOLS */

void WaterScene::processMeteorCollision(MeteorNode* meteor) {
    if(_meteors.find(meteor) == _meteors.end()) {
        return;
    }
    _meteors.erase(meteor);
    _waterNode->touch(meteor);
}

void WaterScene::addPlatform(double xOffset, double length) {
    PlatformAsset* n = PlatformAsset::create(Size(length, _size.height * 0.013));
    n->setTag(TAG_PLATFORM);
    n->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    addChild(n, 2);
    n->setPosition(
	xOffset, _waterNode->getContentSize().height + n->getContentSize().height
    );
}

void WaterScene::dropMeteor(Vec2 pt) {
    auto m = MeteorNode::create();
    m->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    m->setPosition(pt);
    m->setTag(TAG_METEOR);
    _meteors.emplace(m, MeteorInfo());
    addChild(m, 2);
}

