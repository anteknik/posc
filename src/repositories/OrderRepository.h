#pragma once
#include "../models/Order.h"
#include "../database/Database.h"

class OrderRepository {
private:
    Database* db;
public:
    OrderRepository();
    void initializeTable();
    bool saveOrder(const Order& order);
};
