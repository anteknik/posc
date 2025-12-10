#include "ProductRepository.h"
#include <iostream>

ProductRepository::ProductRepository() {
    db = Database::getInstance();
    initializeTable();
}

void ProductRepository::initializeTable() {
    std::string sql = "CREATE TABLE IF NOT EXISTS PRODUCTS("  \
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                      "NAME TEXT NOT NULL," \
                      "PRICE REAL NOT NULL," \
                      "CATEGORY TEXT NOT NULL);";
    db->executeQuery(sql);
}

void ProductRepository::addProduct(const Product& product) {
    std::string sql = "INSERT INTO PRODUCTS (NAME, PRICE, CATEGORY) VALUES ('" + 
                      product.name + "', " + std::to_string(product.price) + ", '" + product.category + "');";
    db->executeQuery(sql);
}

static int productCallback(void* data, int argc, char** argv, char** azColName) {
    std::vector<Product>* products = static_cast<std::vector<Product>*>(data);
    Product p;
    p.id = std::stoi(argv[0]);
    p.name = argv[1];
    p.price = std::stod(argv[2]);
    p.category = argv[3];
    products->push_back(p);
    return 0;
}

std::vector<Product> ProductRepository::getAllProducts() {
    std::vector<Product> products;
    std::string sql = "SELECT * FROM PRODUCTS;";
    char* zErrMsg = 0;
    int rc = sqlite3_exec(db->getDB(), sql.c_str(), productCallback, &products, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    return products;
}

Product ProductRepository::getProductById(int id) {
    std::vector<Product> products;
    std::string sql = "SELECT * FROM PRODUCTS WHERE ID=" + std::to_string(id) + ";";
    char* zErrMsg = 0;
    int rc = sqlite3_exec(db->getDB(), sql.c_str(), productCallback, &products, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
    if (!products.empty()) {
        return products[0];
    }
    return Product{0, "", 0.0, ""};
}
