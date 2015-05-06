#pragma once 

#include "BasicScene.h"
#include <cocos2d.h>
#include "GameElements/WaterNode.h"
#include "GameElements/WaterNodeRadial.h"

class WaterScene : public BasicScene {
public:
    CREATE_FUNC(WaterScene);
private:

    /* STATE */
    WaterNode* _node;

    /* ELEMENTS */

    /* HANDLERS */
    virtual void onMouseDown(cocos2d::Vec2 pt) override;

    /* INITS */
    bool init() override;
    
    /* UPDATES */
    
    /* TOOLS */
};
