#pragma once

#include <cocos2d.h>

class StartPlatformAsset : public cocos2d::Node {

public:
    CREATE_FUNC(StartPlatformAsset);
    
private:
    
    /* STATE */
    
    /* ELEMENTS */
    cocos2d::Sprite* _sprite;
    
    /* INITS */
    bool init() override;
    void initView();
    void initPhysics();
    
};