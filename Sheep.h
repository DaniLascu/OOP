//
// Created by danie on 12/6/2023.
//

#ifndef OOP_SHEEP_H
#define OOP_SHEEP_H


#include "livestock.h"

class Sheep : public livestock {
private:
    double whool_production_per_week;
    double whool_price_per_kg;
    double proffit_per_kg;
    static int price;  // Static price for Sheep


public:
    Sheep(double local_whool = 0, double local_price = 0, double local_proffit = 0, const std::string& name = "unknown", int Weight = 0);

    Sheep(const Sheep& other);

    ~Sheep();

    void display() override;

    double getWhoolProductionPerWeek() const;

    void setWhoolProductionPerWeek(double whoolProductionPerWeek);

    double getWhoolPricePerKg() const;

    void setWhoolPricePerKg(double whoolPricePerKg);

    double getProffitPerKg() const;

    void setProffitPerKg(double proffitPerKg);

    friend std::ostream& operator<<(std::ostream& out, const Sheep& ob);

    double total_proffit() override;

    int getPrice() override;
};

#endif //OOP_SHEEP_H
