//
// Created by danie on 12/8/2023.
//

#ifndef OOP_OWNER_H
#define OOP_OWNER_H


#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "livestock.h"
#include "Parcel.h"
#include "Crop.h"
#include "Culture.h"

class Owner {
private:
    std::string name;
    long double balance;
    std::vector<std::shared_ptr<livestock>> Animals;
    std::vector<std::shared_ptr<parcel>> Lots;
    std::vector<std::shared_ptr<crop>> Crops;
    std::vector<Culture> Cultures;
    std::mutex balanceMutex;

public:
    Owner(const std::string Name = "Dani", long double Balance = 10000);
    ~Owner();

    void Add_lots(std::shared_ptr<parcel> &lot);
    void Add_crops(std::shared_ptr<crop> &crop);
    void Add_Culture();
    void sell_crops();
    void Add_Animal(std::shared_ptr<livestock> animal);
    void Income_Generation();

    const std::string &getName() const;
    long double getBalance() const;
    void display_balance();
    void display_lots();
    void display_crops();
    void display_cultures();
    void display_animals();
    void display_owner();
};

#endif //OOP_OWNER_H
