#pragma once

#include <cocos2d.h>
#include "Models/Article.h"
#include <vector>


class LivesAsset : public cocos2d::Node {

public:
    CREATE_FUNC(LivesAsset);
    void removeLife();
    
private:
    
    /* STATE */
    
    /* ELEMENTS */
    std::queue<cocos2d::Node*> _icons;
    
    /* INITS */
    bool init() override;
    void initIcons();
    
    /* FUNS */
    
};