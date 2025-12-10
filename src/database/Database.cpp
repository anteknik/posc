#include "Database.h"

Database* Database::instance = nullptr;

Database::Database() {
    int rc = sqlite3_open("pos_system.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Opened database successfully\n";
    }
}

Database* Database::getInstance() {
    if (instance == nullptr) {
        instance = new Database();
    }
    return instance;
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

sqlite3* Database::getDB() {
    return db;
}

bool Database::executeQuery(const std::string& query) {
    char* zErrMsg = 0;
    int rc = sqlite3_exec(db, query.c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << "\nQuery: " << query << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}
