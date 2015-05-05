#pragma once

#include "BasicManager.h"

#include "Models/LevelModel.h"


struct LevelsManager : public BasicManager {

    virtual bool init() override { return true; }

    static LevelsManager* getInstance();

    Models::Level getFirstLevel();
    Models::Level getLevel(int i);

};