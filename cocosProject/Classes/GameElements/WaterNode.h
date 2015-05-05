#pragma once

#include <cocos2d.h>
#include <vector>

class WaterNode: public cocos2d::Node {

public:
    CREATE_FUNC(WaterNode);
    
    void touch(cocos2d::Vec2 pt);
    
private:

    /* STATE */
    struct Spring {
        cocos2d::Vec2 position;
        double velocity;
    };

    std::vector<cocos2d::Vec2> _border;
    std::vector<Spring> _springs;

    cocos2d::DrawNode* _drawNode;
    double _time;
    float _seaLevel;

    /* ELEMENTS */

    /* INITS */
    bool init() override;
    void initBorder();

    void update(float dt) override;
    void updateSprings();

    /* FUNS */
    void drawWater();
    
    double levelFun(double x, int lvl = 1);
};