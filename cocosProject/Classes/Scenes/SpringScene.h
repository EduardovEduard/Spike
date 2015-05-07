#pragma once 

#include "BasicScene.h"
#include <cocos2d.h>
#include "GameElements/HeroAsset.h"
#include "Models/GameModel.h"


class SpringScene : public BasicScene {
public:
    CREATE_FUNC(SpringScene);
private:

    /* STATE */   
    
    /* ELEMENTS */

    /* HANDLERS */

    /* INITS */
    bool init() override;
    void initNodes();
    
    /* UPDATES */
    
    /* TOOLS */
};










