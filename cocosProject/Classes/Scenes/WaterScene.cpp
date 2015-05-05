#include "WaterScene.h"

#include <iostream>


using namespace cocos2d;

bool WaterScene::init() {
    if (!BasicScene::init())
        return false;

    auto node = DrawNode::create();
    node->setContentSize(Director::getInstance()->getWinSize());
    addChild(node);

    auto size = node->getContentSize();

    node->drawSolidRect(Vec2(0, 0), Vec2(size.width, size.height / 2), Color4F::BLUE);
    return true;
}



/* STATE */

/* HANDLERS */

/* UPDATES */










