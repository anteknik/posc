#include <iostream>
#include <iomanip>
#include "services/PosService.h"

void printHeader() {
    std::cout << "========================================\n";
    std::cout << "       ELEGANT POS SYSTEM (MVP)         \n";
    std::cout << "========================================\n";
}

void showMenu() {
    std::cout << "\n[1] View Menu & Order\n";
    std::cout << "[2] View Current Cart\n";
    std::cout << "[3] Checkout\n";
    std::cout << "[4] Exit\n";
    std::cout << "> Select Option: ";
}

void viewMenu(PosService& service) {
    auto products = service.getCatalog();
    std::cout << "\n--- PRODUCT MENU ---\n";
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(20) << "Name" 
              << std::setw(10) << "Price" 
              << "Category\n";
    std::cout << "----------------------------------------\n";
    for (const auto& p : products) {
        std::cout << std::left << std::setw(5) << p.id 
                  << std::setw(20) << p.name 
                  << std::setw(10) << p.price 
                  << p.category << "\n";
    }
    
    int id, qty;
    std::cout << "\nEnter Product ID (0 to cancel): ";
    std::cin >> id;
    if (id != 0) {
        std::cout << "Enter Quantity: ";
        std::cin >> qty;
        service.addToCart(id, qty);
        std::cout << "Item added to cart.\n";
    }
}

void viewCart(PosService& service) {
    auto order = service.getCurrentOrder();
    std::cout << "\n--- CURRENT CART ---\n";
    if (order.items.empty()) {
        std::cout << "Cart is empty.\n";
        return;
    }
    
    std::cout << std::left << std::setw(20) << "Item" 
              << std::setw(10) << "Qty" 
              << "Subtotal\n";
    std::cout << "----------------------------------------\n";
    for (const auto& item : order.items) {
        std::cout << std::left << std::setw(20) << item.product.name 
                  << std::setw(10) << item.quantity 
                  << item.subtotal << "\n";
    }
    std::cout << "----------------------------------------\n";
    std::cout << "TOTAL: " << order.totalAmount << "\n";
}

void performCheckout(PosService& service) {
    viewCart(service);
    char confirm;
    std::cout << "\nConfirm Checkout? (y/n): ";
    std::cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
        if (service.checkout()) {
            std::cout << "\nTransaction Successful! Order saved.\n";
        } else {
            std::cout << "\nTransaction Failed (Empty Cart or DB Error).\n";
        }
    }
}

int main() {
    PosService service;
    
    // Seed some data if empty (Optional, strictly we should check repo count)
    // For MVP, if we see no products, we can assume we need to seed.
    if (service.getCatalog().empty()) {
       ProductRepository repo; // Direct access for seeding
       repo.addProduct({0, "Nasi Goreng", 25000, "Food"});
       repo.addProduct({0, "Mie Goreng", 22000, "Food"});
       repo.addProduct({0, "Es Teh Manis", 5000, "Beverage"});
       repo.addProduct({0, "Kopi Hitam", 8000, "Beverage"});
    }

    int choice;
    do {
        printHeader();
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: viewMenu(service); break;
            case 2: viewCart(service); break;
            case 3: performCheckout(service); break;
            case 4: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid Option.\n";
        }
    } while (choice != 4);

    return 0;
}
