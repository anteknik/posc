#pragma once
#include <vector>
#include "../models/Product.h"
#include "../database/Database.h"

class ProductRepository {
private:
    Database* db;
public:
    ProductRepository();
    void initializeTable();
    std::vector<Product> getAllProducts();
    void addProduct(const Product& product);
    Product getProductById(int id);
};
