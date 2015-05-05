
#include <cocos2d.h>
#include "DataManager.h"
#include "leveldb/options.h"
#include "leveldb/db.h"
#include <assert.h>


using namespace std;
using namespace cocos2d;


struct DataManagerImpl : public DataManager {
    
    leveldb::DB* _db;
    
    DataManagerImpl() {
	const string path = FileUtils::getInstance()->getWritablePath() + "userData.db";
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options, path, &_db);
	assert(status.ok());
    }
    
    int get(const string& key, int defaultValue) override {
	std::string value;
	leveldb::Status s = _db->Get(leveldb::ReadOptions(), key, &value);
	if(value == "") {
	    put(key, defaultValue);
	    return defaultValue;
	}
	stringstream ss(value);
	int valueInt;
	ss >> valueInt;
	return valueInt;
    }
    
    bool get(const string& key, bool defaultValue) override {
	int v = get(key, defaultValue ? 1 : 0);
	return v == 1 ? true : false;
    }
    
    string get(const string& key, const string& defaultValue) override {
	std::string value;
	leveldb::Status s = _db->Get(leveldb::ReadOptions(), key, &value);
	if(value == ""){
	    put(key, defaultValue);
	    return defaultValue;
	}
	return value;
    }
    
    void put(const string& key, const string& value) override {
	_db->Put(leveldb::WriteOptions(), key, value);
    }
    
    void put(const string& key, int value) override {
	stringstream ss;
	ss << value;
	_db->Put(leveldb::WriteOptions(), key, ss.str());
    }
    
    void put(const string& key, bool value) override {
	int res = value ? 1 : 0;
	put(key, res);
    }
    
 
   ~DataManagerImpl() {
	delete _db;
    }
    
    

};

DataManager* DataManager::getInstance() {    
    static DataManagerImpl instance;
    return &instance;
}