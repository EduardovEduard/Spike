#pragma once 

#include "BasicScene.h"
#include <cocos2d.h>
#include "GameElements/WaterNode.h"
#include "Models/GameModel.h"

#include <map>

class WaterScene : public BasicScene {
public:
    CREATE_FUNC(WaterScene);
private:
    /* STATE */
    
    /* MODELS */
    Models::GameModel _gameModel;

    struct MeteorInfo {
        bool collided = false;
    };
    
    /* ELEMENTS */
    WaterNode* _waterNode;
    std::map<MeteorNode*, MeteorInfo> _meteors;

    /* HANDLERS */
    virtual void onMouseDown(cocos2d::Vec2 pt) override;
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    bool onContactPreSolve(
	cocos2d::PhysicsContact& contact, 
	cocos2d::PhysicsContactPreSolve& solve
    );
    
    /* INITS */
    bool init() override;
    void initPhysics();
    void initWater();
    void initPlatforms();
    
    /* UPDATES */
    virtual void update(float delta) override;

    /* TOOLS */
    void processMeteorCollision(MeteorNode*);
    void addPlatform(double xOffset, double length);
    void dropMeteor(cocos2d::Vec2 pt);
};
