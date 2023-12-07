//
// Created by danie on 12/6/2023.
//

#ifndef OOP_COW_H
#define OOP_COW_H


#include "livestock.h"
#include <string>
#include <iostream>
#include "livestock.h"

class Cow : public livestock {
private:
    double milk_production_per_day;
    double price_per_liter;
    double proffit_per_litter;
    static int price;  // Static price for Cow

public:
    Cow(double local_milk_production = 0, double local_price_per_liter = 0, double local_proffit = 0,
        const std::string& name = "unknown", int Weight = 0);

    Cow(const Cow& other);

    ~Cow();

    void display() override;

    friend std::ostream& operator<<(std::ostream& out, const Cow& ob);

    Cow& operator=(const Cow& other);

    double getMilkProduction() const;

    void setMilkProduction(double milkProduction);

    double getPricePerLiter() const;

    void setPricePerLiter(double pricePerLiter);

    double getProffitPerLitter() const;

    void setProffitPerLitter(double proffitPerLitter);

    double total_proffit() override;

    int getPrice() override;
};



#endif //OOP_COW_H
