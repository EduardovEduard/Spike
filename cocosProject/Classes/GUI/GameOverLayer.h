#pragma once

#include <cocos2d.h>
#include <vector>
#include <functional>


class GameOverLayer : public cocos2d::LayerColor {

public:
    CREATE_FUNC(GameOverLayer);
    inline void setOnRestart(std::function<void()> fun) {
        _onRestart = fun;
    }
    inline void setOnReview(std::function<void()> fun) {
        _onReview = fun;
    }
    
private:
    
    /* STATE */
    std::function<void()> _onRestart;
    std::function<void()> _onReview;
    
    /* ELEMENTS */
    
    /* INITS */
    bool init() override;
    void initButtons();
    
    /* FUNS */
    
};