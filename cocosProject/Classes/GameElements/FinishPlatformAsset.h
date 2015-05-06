#pragma once

#include <cocos2d.h>

class FinishPlatformAsset : public cocos2d::Node {

public:
    static FinishPlatformAsset* create(const cocos2d::Size& size);
    
private:
    
    /* STATE */
    
    /* ELEMENTS */
    cocos2d::Sprite* _sprite;
    
    /* INITS */
    bool init(const cocos2d::Size& size);
    void initView();
    void initPhysics();
    
};