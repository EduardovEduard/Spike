#include "WaterNode.h"
#include <cocos2d.h>

#include <iostream>

using namespace cocos2d;
using namespace std;

constexpr int BAR_COUNT = 20;

bool WaterNode::init() {
    if(!Node::init())
        return false;

    auto windowSize = Director::getInstance()->getWinSize();

    _drawNode = DrawNode::create();
    _drawNode->setContentSize(windowSize);
    setContentSize(windowSize);

    initBorder();

    addChild(_drawNode);

    scheduleUpdate();
    return true;
}

void WaterNode::initBorder() {
    const auto size = getContentSize();
    const auto barHeight = size.height / 2;
    const auto barWidth = size.width / BAR_COUNT;

    for (int i = 0; i <= BAR_COUNT; ++i) {
        _border.push_back(Vec2(i * barWidth, barHeight));
    }
}

void WaterNode::update(float dt) {
    _drawNode->clear();
    drawWater();
}

void WaterNode::drawWater() {
    for (size_t i = 0; i < _border.size() - 1; ++i) {
        std::vector<Vec2> piece {_border[i], _border[i + 1],
                                 Vec2(_border[i + 1].x, 0), Vec2(_border[i].x, 0)};
        _drawNode->drawSolidPoly(piece.data(), piece.size(), Color4F::BLUE);
    }
}
