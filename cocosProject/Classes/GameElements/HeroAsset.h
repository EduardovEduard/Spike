#pragma once

#include <cocos2d.h>

class HeroAsset : public cocos2d::Node {

public:
    static HeroAsset* create(const cocos2d::Size& size);
    
    void setSpeedX(double sx);
    void addSpeedY(double sy);
    
private:
    
    /* STATE */
    
    /* ELEMENTS */
    cocos2d::Sprite* _sprite;
    
    /* INITS */
    bool init(const cocos2d::Size& size);
    void initPhysics();
    void initSprite();
    
};