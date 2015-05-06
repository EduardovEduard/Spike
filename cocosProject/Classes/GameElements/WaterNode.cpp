#include "WaterNode.h"
#include <chipmunk.h>
#include <cocos2d.h>
#include <unistd.h>
#include "Utils.h"
#include "MeteorNode.h"
#include <sstream>

#include <fstream>
#include <iostream>
#include <unistd.h>

using namespace cocos2d;
using namespace std;


void WaterNode::readInit(const string& filepath) {
    stringstream fin(Utils::getFileData(filepath));
    string name;
    double value;
    while (fin.good()) {
        fin >> name >> value;
        config[name] = value;
    }
}

double WaterNode::configValue(const std::string& key) const {
    assert(config.count(key) != 0);
    return config.find(key)->second;
}

void WaterNode::touch(Vec2 point, double verticalVelocity) {
    auto closestSpring = std::min_element(_springs.begin(), _springs.end(), [&](const Spring& a, const Spring& b) {
        return std::abs(a.position.x - point.x) < std::abs(b.position.x - point.x);
    });

    if(point.y > closestSpring->position.y)
        closestSpring->velocity += verticalVelocity;
    else
        closestSpring->velocity -= verticalVelocity;
}

bool WaterNode::init() {
    if(!Node::init())
        return false;

    readInit("init.ini");
    
    auto windowSize = Director::getInstance()->getWinSize();
    windowSize.width *= 2;
    
    _drawNode = DrawNode::create();
    _drawNode->setContentSize(windowSize);
    _drawNode->setPosition({windowSize.width / 4, 0});
    _seaLevel = windowSize.height / 2;
    
    setContentSize(windowSize);
    initSprings();
    _waterPhysics.resize(_springs.size());
    addChild(_drawNode);
    
//    schedule(CC_SCHEDULE_SELECTOR(WaterNode::tick), 0.3f);
	
    scheduleUpdate();
    
    return true;
}

void WaterNode::initSprings() {
    auto size = getContentSize();

    const auto barCount = config["BAR_COUNT"];;
    const auto barWidth = size.width / barCount;
    
    for (int i = 0; i <= barCount; i++) {
        const float xpos = i * barWidth;
	auto node = Node::create();
	node->setPosition({xpos, _seaLevel});
	auto physicsPart = PhysicsBody::createCircle(5);
	physicsPart->setGravityEnable(false);
	physicsPart->setCollisionBitmask(0x03);
	physicsPart->setCategoryBitmask(0x03);
	physicsPart->setContactTestBitmask(0xFFFFFFFF);
	node->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	node->setPhysicsBody(physicsPart);
	addChild(node);
	_springs.push_back({node, {xpos, _seaLevel}, 0.0});
    }
 }

void WaterNode::update(float dt) {
    _drawNode->clear();

    updateSprings();

    std::vector<double> leftDeltas(_springs.size());
    std::vector<double> rightDeltas(_springs.size());

    for (size_t j = 0; j < 8; ++j)
    {
        for (size_t i = 0; i < _springs.size(); ++i)
        {
            if (i > 0)
            {
                leftDeltas[i] = config["SPREAD"] * (_springs[i].position.y - _springs[i - 1].position.y);
                _springs[i - 1].velocity += leftDeltas[i];
            }
            if (i < _springs.size() - 1)
            {
                rightDeltas[i] = config["SPREAD"] * (_springs[i].position.y - _springs[i + 1].position.y);
                _springs[i + 1].velocity += rightDeltas[i];
            }
        }

        for (size_t i = 0; i < _springs.size(); ++i)
        {
            if (i > 0)
                _springs[i - 1].position.y += leftDeltas[i];
            if (i < _springs.size() - 1)
                _springs[i + 1].position.y += rightDeltas[i];
        }
    }
    
    for(auto& sp: _springs) {
	sp.node->setPosition(sp.position);
    }
    
    drawWater();
}

void WaterNode::updateSprings() {
    for (auto& spring : _springs) {
        double yShift =  spring.position.y - levelFun(spring.position.x);
        double accelration = (-config["TENSION"] * yShift) - config["DAMPENING"] * spring.velocity;
        spring.position.y += spring.velocity;
        spring.velocity += accelration;
    }
    
}

void WaterNode::drawWater() {
    size_t offset = getContentSize().width / 2;

    for (size_t i = 0; i < _springs.size() - 1; ++i) {
        auto left = _springs[i].position; left.x -= offset;
        auto right = _springs[i + 1].position; right.x -= offset;
	
        std::vector<Vec2> piece {left, right, Vec2(right.x, 0), Vec2(left.x, 0)};
        _drawNode->drawSolidPoly(piece.data(), piece.size(), Color4F::BLUE);
    }
}

double WaterNode::levelFun(double x, int lvl) {
    return _seaLevel;
}

void WaterNode::tick(float dt)
{
    // TODO Add meteors at random positions.
//    auto sprite1 = addSpriteAtPosition(Vec2(s_centre.x + cocos2d::random(-300,300),
//      s_centre.y + cocos2d::random(-300,300)));
//    auto physicsBody = sprite1->getPhysicsBody();
//    physicsBody->setVelocity(Vec2(cocos2d::random(-500,500),cocos2d::random(-500,500)));
//    physicsBody->setContactTestBitmask(0xFFFFFFFF);
}

void WaterNode::setWaterPhysicsNodesTag(int tag) {
    for(auto& sp: _springs) {
	sp.node->setTag(tag);
    }
}


