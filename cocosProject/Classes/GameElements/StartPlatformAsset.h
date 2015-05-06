#pragma once

#include <cocos2d.h>

class StartPlatformAsset : public cocos2d::Node {

public:
    static StartPlatformAsset* create(const cocos2d::Size& size);
    
private:
    
    /* STATE */
    
    /* ELEMENTS */
    cocos2d::Sprite* _sprite;
    
    /* INITS */
    bool init(const cocos2d::Size& size);
    void initView();
    void initPhysics();
    
};