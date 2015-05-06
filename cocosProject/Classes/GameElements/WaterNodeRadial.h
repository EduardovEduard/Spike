#pragma once

#include <cocos2d.h>
#include <vector>

class WaterNodeRadial: public cocos2d::Node {

public:
    CREATE_FUNC(WaterNodeRadial);
    
    void touch(cocos2d::Vec2 pt);
    
private:

    /* STATE */
    struct Spring {
	size_t index;
	double radius;
        double velocity;
    };

    std::vector<Spring> _springs;
    cocos2d::Vec2 _center;

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
    
    void computeSpringPositions();
    double levelFun(double part);
    
    cocos2d::Vec2 computePosition(const Spring& s);
    
};