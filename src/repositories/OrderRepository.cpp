#include "OrderRepository.h"
#include <iostream>

OrderRepository::OrderRepository() {
    db = Database::getInstance();
    initializeTable();
}

void OrderRepository::initializeTable() {
    std::string sqlOrders = "CREATE TABLE IF NOT EXISTS ORDERS("  \
                            "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                            "TOTAL REAL NOT NULL," \
                            "TIMESTAMP TEXT DEFAULT CURRENT_TIMESTAMP);";
    db->executeQuery(sqlOrders);

    std::string sqlItems = "CREATE TABLE IF NOT EXISTS ORDER_ITEMS("  \
                           "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                           "ORDER_ID INTEGER," \
                           "PRODUCT_ID INTEGER," \
                           "QUANTITY INTEGER," \
                           "SUBTOTAL REAL," \
                           "FOREIGN KEY(ORDER_ID) REFERENCES ORDERS(ID));";
    db->executeQuery(sqlItems);
}

bool OrderRepository::saveOrder(const Order& order) {
    // 1. Insert Order
    std::string sql = "INSERT INTO ORDERS (TOTAL) VALUES (" + std::to_string(order.totalAmount) + ");";
    if (!db->executeQuery(sql)) return false;

    // Get last insert ID
    int orderId = (int)sqlite3_last_insert_rowid(db->getDB());

    // 2. Insert Items
    for (const auto& item : order.items) {
        std::string itemSql = "INSERT INTO ORDER_ITEMS (ORDER_ID, PRODUCT_ID, QUANTITY, SUBTOTAL) VALUES (" +
                              std::to_string(orderId) + ", " + 
                              std::to_string(item.product.id) + ", " + 
                              std::to_string(item.quantity) + ", " + 
                              std::to_string(item.subtotal) + ");";
        db->executeQuery(itemSql);
    }
    return true;
}
