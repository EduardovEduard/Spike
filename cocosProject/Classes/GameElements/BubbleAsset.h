#pragma once

#include <cocos2d.h>
#include <vector>
#include <string>
#include <cocos/ui/UIScale9Sprite.h>

class BubbleAsset : public cocos2d::ui::Scale9Sprite {

public:
    CREATE_FUNC(BubbleAsset);
    void setText(const std::string& txt);
    cocos2d::Label* _label = nullptr;
    
private:
    
    /* STATE */
    
    /* ELEMENTS */
    cocos2d::Sprite* _sprite;
    
    /* INITS */
    bool init() override;
    
    /* FUNS */
    
};