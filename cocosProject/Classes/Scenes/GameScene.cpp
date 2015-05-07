#include "GameScene.h"
#include "GameElements/MeteorNode.h"
#include "GameElements/WaterNode.h"
#include "GameElements/StartPlatformAsset.h"
#include "GameElements/FinishPlatformAsset.h"

#include <cassert>
#include <iostream>
#include <utility>

using namespace cocos2d;
using namespace std;

static const int TAG_WATER = 0x05;
static const int TAG_METEOR = 0x06;
static const int TAG_START_PLATFROM = 0x07;
static const int TAG_FINISH_PLATFROM = 0x08;
static const int TAG_FLOOR = 0x09;
static const int TAG_HERO = 0x0A;

constexpr float HERO_JUMP_RATE = 0.2;

/* INTIS */

bool GameScene::init() {
    if (!BasicScene::initWithPhysics())
        return false;
    initPhysics();
    initStartPlatform();
    initFinishPlatform();
    initWater();
    initPlatforms();
    initHero();
    return true;
}

void GameScene::initPhysics() {
    getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameScene::initPlatforms() {
    vector<pair<double, double>> plfs;
    plfs.emplace_back(0.1, 0.1);
    plfs.emplace_back(0.25, 0.12);
    plfs.emplace_back(0.44, 0.18);
    plfs.emplace_back(0.62, 0.1);
    plfs.emplace_back(0.8, 0.05);
    double w = _waterNode->getContentSize().width;
    for(auto p: plfs) {
	dropItem(
	    _waterNode->getPosition().x + w * p.first, w * p.second
	);
    }
}


void GameScene::initStartPlatform() {
    Vec2 sz(_size.width * 0.1, _size.height / 1.9);
    auto sp = StartPlatformAsset::create(Size(sz));
    sp->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    sp->setTag(TAG_START_PLATFROM);
    sp->setPosition(sz/2);
    addChild(sp, 1, TAG_START_PLATFROM);
}

void GameScene::initFinishPlatform() {
    Vec2 sz(_size.width * 0.1, _size.height / 1.9);
    auto sp = FinishPlatformAsset::create(Size(sz));
    sp->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    sp->setTag(TAG_FINISH_PLATFROM);
    sp->setPosition(Vec2(_size.width, _size.height / 1.9) - sz/2);
    addChild(sp, 1, TAG_FINISH_PLATFROM);
}

void GameScene::initWater() {
    _waterNode = WaterNode::create(Size(
	_size.width * 0.8, _size.height / 2
    ));
    _waterNode->setWaterPhysicsNodesTag(TAG_WATER);
    _waterNode->setPosition(Vec2(_size.width * 0.1, 0));
    addChild(_waterNode, 1);
}


void GameScene::initHero() {
    _hero = HeroAsset::create(Size(_size.width * 0.02, _size.height * 0.08));
    StartPlatformAsset* sp = static_cast<StartPlatformAsset*>(
	    getChildByTag(TAG_START_PLATFROM));
    Vec2 pos = sp->getPosition() + Vec2(0, sp->getContentSize().height / 2);
    pos+=_hero->getContentSize()/2;
    _hero->setPosition(pos);
    _hero->setTag(TAG_HERO);
    _hero->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    addChild(_hero, 2);
    _hero->setSpeedX(_size.width * 0.07);
}

/* UPDATES */

void GameScene::update(float delta) {
    BasicScene::update(delta);
}


/* HANDLERS */

void GameScene::onMouseDown(Vec2 pt) {
    if(_gameModel.heroJumpState == Models::HeroJumpState::inSecondJump)
	return;
    onHeroJump();
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
    
    if(isTagPair(TAG_HERO, TAG_START_PLATFROM) || 
       isTagPair(TAG_HERO, TAG_FINISH_PLATFROM) || 
       isTagPair(TAG_HERO, TAG_FLOOR)
    ) {
	onHeroTouchFloor();
    }
    
    if(isTagPair(TAG_WATER, TAG_WATER)) return false;
    if(isTagPair(TAG_METEOR, TAG_METEOR)) return false;
    if(isTagPair(TAG_WATER, TAG_METEOR)) {
        MeteorNode* mn = dynamic_cast<MeteorNode*>(nodeA->getTag() == TAG_METEOR ? nodeA : nodeB);
        processMeteorCollision(mn);
        return false;
    }
    return true;
}

void GameScene::onHeroJump() {
    assert(_gameModel.heroJumpState != Models::HeroJumpState::inSecondJump);
    if(_gameModel.heroJumpState == Models::HeroJumpState::inFirstJump) {
	_gameModel.heroJumpState =  Models::HeroJumpState::inSecondJump;
    }
    if(_gameModel.heroJumpState == Models::HeroJumpState::idle) {
	_gameModel.heroJumpState =  Models::HeroJumpState::inFirstJump;
    }
    _hero->addSpeedY(HERO_JUMP_RATE * _size.height);
    _gameModel.heroWaitTime = 0;
}

void GameScene::onHeroTouchFloor() {
    _gameModel.heroJumpState = Models::HeroJumpState::idle;
}


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
    n->setTag(TAG_FLOOR);
    n->setContentSize(Size(length, 10));
    n->setPhysicsBody(PhysicsBody::createBox(n->getContentSize()));
    n->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    addChild(n, 2);
    n->setPosition(
	xOffset, _waterNode->getContentSize().height + n->getContentSize().height/2
    );
}

void GameScene::dropMeteor(Vec2 pt) {
    auto m = MeteorNode::create();
    m->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
    m->setPosition(pt);
    m->setTag(TAG_METEOR);
    _meteors.emplace(m, MeteorInfo());
    addChild(m, 2);
}

