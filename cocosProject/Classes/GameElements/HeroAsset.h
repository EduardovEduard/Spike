#pragma once

#include <cocos2d.h>

class HeroAsset : public cocos2d::Node {

public:
    CREATE_FUNC(HeroAsset);
    
private:
    
    /* STATE */
    
    /* ELEMENTS */
    cocos2d::Sprite* _sprite;
    
    /* INITS */
    bool init() override;
    void initSprite();
    
};