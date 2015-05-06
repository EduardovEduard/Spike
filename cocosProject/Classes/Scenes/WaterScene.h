#pragma once 

#include "BasicScene.h"
#include <cocos2d.h>
#include "GameElements/WaterNode.h"
#include "GameElements/WaterNodeRadial.h"
#include "GameElements/MeteorNode.h"
#include <map>


class WaterScene : public BasicScene {
public:
    CREATE_FUNC(WaterScene);
private:
    
    struct MeteorInfo {
        bool collided = false;
    };

    /* STATE */
    WaterNode* _node;
    
    std::map<MeteorNode*, MeteorInfo> _meteors;

    /* ELEMENTS */

    /* HANDLERS */
    virtual void onMouseDown(cocos2d::Vec2 pt) override;
    bool onContactBegin(cocos2d::PhysicsContact& contact);

    /* INITS */
    bool init() override;
    
    
    
    /* UPDATES */
    
    /* TOOLS */
    void processMeteorCollision(MeteorNode*);
    void dropItem();
    
};
