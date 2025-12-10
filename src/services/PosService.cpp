#include "PosService.h"
#include <iostream>

PosService::PosService() {
    currentOrder.totalAmount = 0;
}

std::vector<Product> PosService::getCatalog() {
    return productRepo.getAllProducts();
}

void PosService::addToCart(int productId, int quantity) {
    Product p = productRepo.getProductById(productId);
    if (p.id == 0) {
        std::cout << "Product not found!\n";
        return;
    }

    OrderItem item;
    item.product = p;
    item.quantity = quantity;
    item.subtotal = p.price * quantity;

    currentOrder.items.push_back(item);
    currentOrder.totalAmount += item.subtotal;
}

Order PosService::getCurrentOrder() {
    return currentOrder;
}

bool PosService::checkout() {
    if (currentOrder.items.empty()) {
        return false;
    }
    bool success = orderRepo.saveOrder(currentOrder);
    if (success) {
        clearCart();
    }
    return success;
}

void PosService::clearCart() {
    currentOrder.items.clear();
    currentOrder.totalAmount = 0;
}
