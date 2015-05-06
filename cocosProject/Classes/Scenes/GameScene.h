#pragma once 

#include "BasicScene.h"
#include <cocos2d.h>
#include "GameElements/WaterNode.h"
#include "GameElements/WaterNodeRadial.h"
#include "GameElements/MeteorNode.h"
#include <map>


class GameScene : public BasicScene {
public:
    CREATE_FUNC(GameScene);
private:
    
    struct MeteorInfo {
        bool collided = false;
    };

    /* STATE */
    WaterNode* _waterNode;
    std::map<MeteorNode*, MeteorInfo> _meteors;

    /* ELEMENTS */

    /* HANDLERS */
    virtual void onMouseDown(cocos2d::Vec2 pt) override;
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
    /* INITS */
    bool init() override;
    void initPhysics();
    void initWater();
    void initStartPlatform();
    void initFinishPlatform();
    void initPlatforms();
    
    /* UPDATES */
    
    /* TOOLS */
    void processMeteorCollision(MeteorNode*);
    void dropItem(double xOffset, double length);
    void dropMeteor(cocos2d::Vec2 pt);
    
};
