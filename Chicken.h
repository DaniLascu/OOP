//
// Created by danie on 12/6/2023.
//

#ifndef OOP_CHICKEN_H
#define OOP_CHICKEN_H

#include "livestock.h"

class Chicken : public livestock {
private:
    int number_of_eggs_day;
    double price_per_egg;
    double proffit_per_egg;
    static int price;  // Static price for Chicken

public:
    Chicken(int local_eggs = 0, double local_price = 0, double local_proffit = 0, const std::string& name = "unknown", int Weight = 0);

    Chicken(const Chicken& other);

    ~Chicken();

    void display() override;

    int getNumberOfEggsDay() const;

    void setNumberOfEggsDay(int numberOfEggsDay);

    double getPricePerEgg() const;

    void setPricePerEgg(double pricePerEgg);

    double getProffitPerEgg() const;

    void setProffitPerEgg(double proffitPerEgg);

    double total_proffit() override;

    int getPrice() override;
};

#endif //OOP_CHICKEN_H
