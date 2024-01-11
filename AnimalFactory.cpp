// AnimalFactory.cpp

#include "AnimalFactory.h"

std::shared_ptr<livestock> AnimalFactory::build(int optiune, double &profit) {
    if(optiune == 1) {
        double milk;
        std::cout << "Cati litrii de lapte produce pe zii\n";
        std::cin >> milk;
        double price_per_litter;
        std::cout << "Pretul unui litru de lapte\n";
        std::cin >> price_per_litter;
        std::cout << "Profit per litru\n";
        std::cin >> profit;
        std::string name;
        std::cout << "Numele\n";
        std::cin >> name;
        int weight;
        std::cout << "Greutate\n";
        std::cin >> weight;
        return std::make_shared<Cow>(milk, price_per_litter, profit, name, weight);
    }
    if(optiune == 2) {
        double eggs;
        std::cout << "Cate oua produce pe zii\n";
        std::cin >> eggs;
        double price_per_egg;
        std::cout << "Pretul unui ou\n";
        std::cin >> price_per_egg;
        std::cout << "Profit per ou\n";
        std::cin >> profit;
        std::string name;
        std::cout << "Numele\n";
        std::cin >> name;
        int weight;
        std::cout << "Greutate\n";
        std::cin >> weight;
        return std::make_shared<Chicken>(eggs, price_per_egg, profit, name, weight);
    }
    if(optiune == 3) {
        double whool;
        std::cout << "Cata lana produce pe saptamana\n";
        std::cin >> whool;
        double price_per_kg;
        std::cout << "Pretul unui kg de lana\n";
        std::cin >> price_per_kg;
        std::cout << "Profit per kg\n";
        std::cin >> profit;
        std::string name;
        std::cout << "Numele\n";
        std::cin >> name;
        int weight;
        std::cout << "Greutate\n";
        std::cin >> weight;
        return std::make_shared<Sheep>(whool, price_per_kg, profit, name, weight);
    }

    return nullptr;
}
