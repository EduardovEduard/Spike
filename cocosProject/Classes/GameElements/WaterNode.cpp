#include "WaterNode.h"
#include <chipmunk.h>
#include <cocos2d.h>
#include <unistd.h>

#include <fstream>
#include <iostream>

using namespace cocos2d;
using namespace std;

void WaterNode::readInit(const string& filepath) {
    ifstream fin(filepath.c_str());
    string name;
    double value;
    while (fin.good()) {
        fin >> name >> value;
        config[name] = value;
    }
    for (auto pair : config)
        cout << pair.first << ' ' << pair.second << endl;
}

void WaterNode::touch(Vec2 pt) {
    auto closestSpring = std::min_element(_springs.begin(), _springs.end(), [&](const Spring& a, const Spring& b) {
        return std::abs(a.position.x - pt.x) < std::abs(b.position.x - pt.x);
    });

    closestSpring += config["WATER_NODE_OFFSET"];

    if(pt.y > closestSpring->position.y)
        closestSpring->velocity += config["DEFAULT_SPEED"];
    else
        closestSpring->velocity -= config["DEFAULT_SPEED"];
}

bool WaterNode::init() {
    if(!Node::init())
        return false;

    readInit("init.ini");

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
    auto size = getContentSize();
    size.width += size.width / 2;

    const auto barWidth = (2 * size.width) / config["BAR_COUNT"];
    for (int i = -config["WATER_NODE_OFFSET"]; i <= config["BAR_COUNT"] + config["WATER_NODE_OFFSET"]; i++) {
        auto pos = i * barWidth;
        _border.push_back(Vec2(pos, _seaLevel));
    }

    for (auto& point : _border) {
        _springs.push_back({Vec2(point.x, point.y), 0});
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

    for (size_t i = 0; i < _springs.size(); ++i) {
        _border[i] = _springs[i].position;
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

    for (size_t i = 0; i < _border.size() - 1; ++i) {
        auto left = _border[i]; left.x -= offset;
        auto right = _border[i + 1]; right.x -= offset;

        std::vector<Vec2> piece {left, right, Vec2(right.x, 0), Vec2(left.x, 0)};
        _drawNode->drawSolidPoly(piece.data(), piece.size(), Color4F::BLUE);
    }
}

double WaterNode::levelFun(double x, int lvl) {
    return _seaLevel;// + 100 * sin(x / _springs.size() * 3.1415926 * 1.5);
}
