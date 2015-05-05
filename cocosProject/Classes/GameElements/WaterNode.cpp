#include "WaterNode.h"
#include <chipmunk.h>
#include <cocos2d.h>

#include <iostream>

using namespace cocos2d;
using namespace std;

constexpr int BAR_COUNT = 200;
constexpr double DAMPENING = 0.025;
constexpr double TENSION = 0.005;
constexpr double SPREAD = 0.3;
constexpr double DEFAULT_SPEED = -80;


void WaterNode::touch(float x) {
    auto closestSpring = std::min_element(_springs.begin(), _springs.end(), [&](const Spring& a, const Spring& b) {
        return std::abs(a.position.x - x) < std::abs(b.position.x - x);
    });

    closestSpring->velocity += DEFAULT_SPEED;
}

bool WaterNode::init() {
    if(!Node::init())
        return false;

    auto windowSize = Director::getInstance()->getWinSize();

    _time = 0;
    _drawNode = DrawNode::create();
    _drawNode->setContentSize(windowSize);
    _seaLevel = windowSize.height / 2;
    setContentSize(windowSize);

    initBorder();

    addChild(_drawNode);

    scheduleUpdate();
    return true;
}

void WaterNode::initBorder() {
    const auto size = getContentSize();
    const auto barWidth = size.width / BAR_COUNT;

    for (int i = 0; i <= BAR_COUNT; ++i) {
        _border.push_back(Vec2(i * barWidth, _seaLevel));
    }

    for (auto& point : _border) {
        _springs.push_back({Vec2(point.x, point.y), 0});
    }
}

void WaterNode::update(float dt) {
    _drawNode->clear();
    const auto size = getContentSize();

    updateSprings();

    std::vector<double> leftDeltas(_springs.size());
    std::vector<double> rightDeltas(_springs.size());

    for (size_t j = 0; j < 8; ++j)
    {
        for (size_t i = 0; i < _springs.size(); ++i)
        {
            if (i > 0)
            {
                leftDeltas[i] = SPREAD * (_springs[i].position.y - _springs[i - 1].position.y);
                _springs[i - 1].velocity += leftDeltas[i];
            }
            if (i < _springs.size() - 1)
            {
                rightDeltas[i] = SPREAD * (_springs[i].position.y - _springs[i + 1].position.y);
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

    for (size_t i = 0; i < _springs.size(); ++i) {
        _border[i] = _springs[i].position;
    }
    drawWater();
}

void WaterNode::updateSprings() {
    for (auto& spring : _springs) {
        double yShift = spring.position.y - _seaLevel;
        double accelration = (-TENSION * yShift) - DAMPENING * spring.velocity;

        spring.position.y += spring.velocity;
        spring.velocity += accelration;
    }
}

void WaterNode::drawWater() {
    for (size_t i = 0; i < _border.size() - 1; ++i) {
        std::vector<Vec2> piece {_border[i], _border[i + 1],
                                 Vec2(_border[i + 1].x, 0), Vec2(_border[i].x, 0)};
        _drawNode->drawSolidPoly(piece.data(), piece.size(), Color4F::BLUE);
    }
}
