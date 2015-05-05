#pragma once

#include "BasicManager.h"
#include "Scenes/BasicScene.h"

class ScenesManager : public BasicManager {
    
public:
    
    inline bool init() override { return true; }
    
    static ScenesManager* getInstance() {
        static ScenesManager instance;
        return &instance;
    }
    
    void runWithMain();
    void runWithWater();
    
    void gotoMain(int num);
    
    void onAppPause() override;
    void onAppResume() override;
    


private:

    ScenesManager();
    
    
    /* ELEMENTS */
    BasicScene* _currentScene = nullptr;
    
    /* TOOLS */
    void hideByTag(const int tag);
    
    ScenesManager(const ScenesManager &orig);

};



