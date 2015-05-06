#pragma once

#include "MeteorNode.h"

#include <cocos2d.h>
#include <vector>
#include <map>
#include <string>

class WaterNode: public cocos2d::Node {

public:
    CREATE_FUNC(WaterNode);
    
    void touch(cocos2d::Vec2 pt, double verticalVelocity = 0, double horiontalVelocity = 0);
    void touch(MeteorNode* node);
    double configValue(const std::string& key) const;
    
    void setWaterPhysicsNodesTag(int tag);
    
private:

    /* STATE */
    struct Spring {
        cocos2d::Node* node;
        double velocity;

        const cocos2d::Vec2& getPosition() const {
            return node->getPosition();
        }

        void setPosition(const cocos2d::Vec2& vec) {
            node->setPosition(vec);
        }
    };

    std::vector<Spring> _springs;

    struct MeteorCollision {
        MeteorNode* node;
        size_t index;
        int tries;
    };

    std::vector<MeteorCollision> _meteors;

    std::map<std::string, double> config;
    cocos2d::DrawNode* _drawNode;
    float _seaLevel;
    
    std::vector<cocos2d::PhysicsBody*> _waterPhysics;

    /* ELEMENTS */

    /* INITS */
    bool init() override;
    
    void initSprings();
    void readInit(const std::string& filepath);
    
    /* UPDATES */
    void update(float dt) override;
    void updateSprings();
    void updatePlatforms();
    void updateMeteors();
    

    /* FUNS */
    void redrawWater();
    std::vector<cocos2d::Vec2> narrowPlaform(const cocos2d::Vec2&, const cocos2d::Vec2);
    double levelFun(double x, int lvl = 1);
};
