#include "WaterScene.h"
#include "GameElements/WaterNode.h"
#include "GameElements/WaterNodeRadial.h"

#include <iostream>


using namespace cocos2d;

void WaterScene::onMouseDown(Vec2 pt)
{
    _node->touch(pt);
}

bool WaterScene::init() {
    if (!BasicScene::init())
        return false;
    _node = WaterNodeRadial::create();
    _node->setContentSize(Director::getInstance()->getWinSize());
    addChild(_node, 1);
    return true;
}



/* STATE */

/* HANDLERS */

/* UPDATES */