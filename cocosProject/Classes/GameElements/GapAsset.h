#pragma once

#include <cocos2d.h>
#include "Models/Article.h"
#include <vector>

class GapAsset : public cocos2d::Node {

public:
    CREATE_FUNC(GapAsset);
    void unlock(Models::Article a, bool success);
    
private:
    
    /* STATE */
    
    /* ELEMENTS */
    cocos2d::Sprite* _sprite;
    
    /* INITS */
    bool init() override;
    
    /* FUNS */
    
};