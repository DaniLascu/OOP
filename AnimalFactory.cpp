// AnimalFactory.cpp

#include "AnimalFactory.h"

std::shared_ptr<livestock> AnimalFactory::build(int option, double &profit) {
    double production, price, weight;
    std::string name;

    if(option == 1)
        std::cout<<"Cati litrii produce pe zi: ";
    else if(option == 2)
        std::cout<<"Cate oua produce pe zi: ";
    else if(option == 3)
        std::cout<<"Cate kg de lana produce pe saptamana: ";
    else return nullptr;
    std::cin >> production;

    if(option == 1)
        std::cout<<"Pret per litru: ";
    else if(option == 2)
        std::cout<<"Pret per ou: ";
    else if(option == 3)
        std::cout<<"Pret per kg: ";
    std::cin >> price;

    std::cout << "Profit per unit: ";
    std::cin >> profit;

    std::cout << "Numele: ";
    std::cin >> name;

    std::cout << "Greutate: ";
    std::cin >> weight;

    switch (option) {
        case 1:
            return std::make_shared<Cow>(production, price, profit, name, weight);
        case 2:
            return std::make_shared<Chicken>(production, price, profit, name, weight);
        case 3:
            return std::make_shared<Sheep>(production, price, profit, name, weight);
        default:
            throw std::invalid_argument("Invalid option");
    }
}
