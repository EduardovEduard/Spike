#pragma once

#include <cocos2d.h>
#include <vector>

class WaterNode: public cocos2d::Node {

public:
    CREATE_FUNC(WaterNode);

private:

    /* STATE */
    std::vector<cocos2d::Vec2> _border;
    cocos2d::DrawNode* _drawNode;

    /* ELEMENTS */

    /* INITS */
    bool init() override;
    void initBorder();

    void update(float dt) override;

    /* FUNS */
    void drawWater();
};
