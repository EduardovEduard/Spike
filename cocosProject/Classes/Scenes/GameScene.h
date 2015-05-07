#pragma once 

#include "BasicScene.h"
#include <cocos2d.h>
#include "GameElements/WaterNode.h"
#include "GameElements/WaterNodeRadial.h"
#include "GameElements/MeteorNode.h"
#include "GameElements/HeroAsset.h"
#include "Models/GameModel.h"

#include <map>


class GameScene : public BasicScene {
public:
    CREATE_FUNC(GameScene);
private:
    
    struct MeteorInfo {
        bool collided = false;
    };

    /* STATE */
    
    /* MODELS */
    Models::GameModel _gameModel;

    /* ELEMENTS */
    WaterNode* _waterNode;
    std::map<MeteorNode*, MeteorInfo> _meteors;
    HeroAsset* _hero;

    /* HANDLERS */
    virtual void onMouseDown(cocos2d::Vec2 pt) override;
    virtual void onMouseUp(cocos2d::Vec2 ) override;
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void onHeroJump();
    void onHeroTouchFloor();
    
    /* INITS */
    bool init() override;
    void initPhysics();
    void initWater();
    void initStartPlatform();
    void initFinishPlatform();
    void initPlatforms();
    void initHero();
    
    /* UPDATES */
    virtual void update(float delta) override;

    
    /* TOOLS */
    void processMeteorCollision(MeteorNode*);
    void dropItem(double xOffset, double length);
    void dropMeteor(cocos2d::Vec2 pt);
    
};
