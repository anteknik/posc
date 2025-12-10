#pragma once
#include <vector>
#include "../models/Product.h"
#include "../models/Order.h"
#include "../repositories/ProductRepository.h"
#include "../repositories/OrderRepository.h"

class PosService {
private:
    ProductRepository productRepo;
    OrderRepository orderRepo;
    Order currentOrder;

public:
    PosService();
    std::vector<Product> getCatalog();
    void addToCart(int productId, int quantity);
    Order getCurrentOrder();
    bool checkout();
    void clearCart();
};
