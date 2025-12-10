#pragma once
#include <sqlite3.h>
#include <string>
#include <iostream>

class Database {
private:
    sqlite3* db;
    static Database* instance;
    Database();

public:
    static Database* getInstance();
    ~Database();
    
    sqlite3* getDB();
    bool executeQuery(const std::string& query);
};
