#pragma once

#include <cocos2d.h>
#include "Models/Article.h"
#include <vector>
#include <functional>


class ResultsLayer : public cocos2d::LayerColor {

public:
    CREATE_FUNC(ResultsLayer);
    inline void setOnRestart(std::function<void()> fun) {
        _onRestart = fun;
    }
    inline void setOnNext(std::function<void()> fun) {
        _onNext = fun;
    }
    
private:
    
    /* STATE */
    std::function<void()> _onRestart;
    std::function<void()> _onNext;
    
    /* ELEMENTS */
    
    /* INITS */
    bool init() override;
    void initButtons();
    
    /* FUNS */
    
};