#include "Managers/EconomicsManager.h"
#include <functional>
#include <unistd.h>
#include <thread>
#include <iostream>

using namespace std;


struct EconomicsManagerImpl : public EconomicsManager {
    bool init() override {
	return true;
    }
    
    void askPurchase(function<void(bool, string)> fun) {
//	usleep(1000000);
	fun(false, "asdsa");
    }
    
    bool hasBoughtItem() override {
	return false;
    }
};

EconomicsManager* EconomicsManager::getInstance() {
    static EconomicsManagerImpl instance;
    return &instance;
}
