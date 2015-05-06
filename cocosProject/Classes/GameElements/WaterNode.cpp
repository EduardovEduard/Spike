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
    closestSpring->velocity += verticalVelocity;
}

bool WaterNode::init() {
    if(!Node::init())
        return false;

    readInit("init.ini");
    
    auto windowSize = Director::getInstance()->getWinSize();
    
    _drawNode = DrawNode::create();
    _drawNode->setContentSize(windowSize);
    _drawNode->setPosition(Vec2::ZERO);
    _seaLevel = windowSize.height / 2;
    
    setContentSize(windowSize);
    initSprings();
    _waterPhysics.resize(_springs.size());
    addChild(_drawNode);
    	
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
	//physicsPart->setGravityEnable(false);
	physicsPart->setDynamic(false);
	physicsPart->setContactTestBitmask(0xFFFFFFFF);
	node->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	node->setPhysicsBody(physicsPart);
	addChild(node);
	_springs.push_back({node, {xpos, _seaLevel}, 0.0});
    }
 }

void WaterNode::update(float dt) {
    
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
    
    redrawWater();

    
}

void WaterNode::updateSprings() {
    for (auto& spring : _springs) {
        double yShift =  spring.position.y - levelFun(spring.position.x);
        double accelration = (-config["TENSION"] * yShift) - config["DAMPENING"] * spring.velocity;
        spring.position.y += spring.velocity;
        spring.velocity += accelration;
    }
}

void WaterNode::redrawWater() {
    _drawNode->clear();
    vector<Vec2> border;
    std::transform(
	_springs.begin(), _springs.end(), back_inserter(border), 
	[](const Spring& sp) {
	    return sp.node->getPosition();
	}
    );
//    border.push_back(Vec2(_drawNode->getContentSize().width - 100, 100));
//    border.push_back(Vec2(_drawNode->getContentSize().width, 100));
    border.push_back(Vec2(_drawNode->getContentSize().width,0));
    border.push_back(Vec2::ZERO);
//    _drawNode->drawPolygon(
//	border.data(), border.size(), Color4F::BLUE, 0, Color4F::BLUE
//    );
    
    _drawNode->drawPolygon(
	border.data(), border.size(), Color4F::BLUE, 0, Color4F::BLUE
    );
    
}

double WaterNode::levelFun(double x, int lvl) {
    return _seaLevel;
}

void WaterNode::setWaterPhysicsNodesTag(int tag) {
    for(auto& sp: _springs) {
	sp.node->setTag(tag);
    }
}


