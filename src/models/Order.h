#pragma once
#include <vector>
#include "Product.h"

struct OrderItem {
    Product product;
    int quantity;
    double subtotal;
};

struct Order {
    int id;
    std::vector<OrderItem> items;
    double totalAmount;
    std::string timestamp;
};
