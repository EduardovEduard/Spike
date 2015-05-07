#pragma once

#include <cocos2d.h>

class PlatformAsset : public cocos2d::Node {

public:
    static PlatformAsset* create(const cocos2d::Size& size);

private:
    
    /* STATE */
    
    /* ELEMENTS */
    cocos2d::Sprite* _sprite;
    
    /* INITS */
    bool init(const cocos2d::Size& size);
    void initPhysics();
    void initSprite();
    
};