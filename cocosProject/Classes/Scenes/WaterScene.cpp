#include "WaterScene.h"
#include "GameElements/WaterNode.h"

#include <iostream>


using namespace cocos2d;

bool WaterScene::init() {
    if (!BasicScene::init())
        return false;

    auto node = WaterNode::create();
    node->setContentSize(Director::getInstance()->getWinSize());
    addChild(node, 1);
    return true;
}



/* STATE */

/* HANDLERS */

/* UPDATES */










