#include "WaterNodeRadial.h"
#include <chipmunk.h>
#include <cocos2d.h>

#include <iostream>

using namespace cocos2d;
using namespace std;

constexpr size_t BAR_COUNT = 100;
constexpr double DAMPENING = 0.025;
constexpr double TENSION = 0.005;
constexpr double SPREAD = 0.3;
constexpr double DEFAULT_SPEED = -60;

void WaterNodeRadial::touch(Vec2 pt) {
    Spring* closestSpring = &_springs[1];
    if((pt-_center).length() > closestSpring->radius)
	closestSpring->velocity += DEFAULT_SPEED;
    else
	closestSpring->velocity -= DEFAULT_SPEED;
}

bool WaterNodeRadial::init() {
    if(!Node::init())
        return false;
    auto windowSize = Director::getInstance()->getWinSize();
    _center = Vec2(windowSize.width, windowSize.height) / 2;
    _time = 0;
    _drawNode = DrawNode::create();
    _drawNode->setContentSize(windowSize);
    _seaLevel = windowSize.height / 2;
    setContentSize(windowSize);
    initBorder();
    addChild(_drawNode);
    scheduleUpdate();
    drawWater();
    return true;
}

void WaterNodeRadial::initBorder() {
    for (size_t i = 0; i < BAR_COUNT; ++i) {
        _springs.push_back({i, levelFun((i * 1.0) / BAR_COUNT), 0});
    }
}

void WaterNodeRadial::update(float dt) {
    _drawNode->clear();
    computeSpringPositions();
    updateSprings();
    drawWater();
}

void WaterNodeRadial::computeSpringPositions() {
    std::vector<double> leftDeltas(_springs.size());
    std::vector<double> rightDeltas(_springs.size());
    
    auto springAt = [&](size_t i) -> Spring& {
	return _springs.at((i + _springs.size()) % _springs.size());
    };
    
    for (size_t j = 0; j < 8; ++j)
    {
        for (size_t i = 0; i < _springs.size(); ++i)
        {
            leftDeltas[i] = SPREAD * (springAt(i).radius - springAt(i - 1).radius);
            springAt(i - 1).velocity += leftDeltas[i];
            
            rightDeltas[i] = SPREAD * (springAt(i).radius - springAt(i + 1).radius);
            springAt(i + 1).velocity += rightDeltas[i];
        }

        for (size_t i = 0; i < _springs.size(); ++i)
        {
            springAt(i - 1).radius += leftDeltas[i];
            springAt(i + 1).radius += rightDeltas[i];
        }
    }
}

void WaterNodeRadial::updateSprings() {
    for (auto& spring : _springs) {
        double yShift =  spring.radius - levelFun(spring.radius);
        double accelration = (-TENSION * yShift) - DAMPENING * spring.velocity;
        spring.radius += spring.velocity;
        spring.velocity += accelration;
    }
}

void WaterNodeRadial::drawWater() {
    vector<Vec2> border;
    std::transform(_springs.begin(), _springs.end(), 
	    back_inserter(border), bind(&WaterNodeRadial::computePosition, this, std::placeholders::_1));
    _drawNode->drawPolygon(
	border.data(), border.size(), Color4F::BLUE, 0, Color4F::BLUE
    );
}

double WaterNodeRadial::levelFun(double part) {
    return _seaLevel + 100 * sin(part * 3.1415926 * 1.5);
}

Vec2 WaterNodeRadial::computePosition(const Spring& s) {
    Vec2 res(s.radius, 0);
    const auto barAngle = (2 * M_PI) / BAR_COUNT;
    res.rotate(Vec2::ZERO, s.index * barAngle);
    return res + _center;
}

