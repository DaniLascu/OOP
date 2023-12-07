//
// Created by danie on 12/6/2023.
//

#ifndef OOP_CROP_H
#define OOP_CROP_H


#include <iostream>
#include <string>

class crop {
protected:
    std::string name;
    double surface_for_1_plant;
    double cost_for_1_plant;
    double price_unit;
    int plant_id;
    static int Id;

public:
    crop(const std::string& name = "unknown", double surface = 0, double price = 0, double cost = 0);

    crop(const crop& other);

    virtual ~crop();

    void display_crop();

    const std::string& getName() const;

    void setName(const std::string& name);

    double getSurfaceFor1Plant() const;

    void setSurfaceFor1Plant(double surfaceFor1Plant);

    int getPlantId() const;

    void setPlantId(int plantId);

    double getPriceUnit() const;

    void setPriceUnit(double priceKg);

    double getCostFor1Plant() const;

    void setCostFor1Plant(double costFor1Plant);

    static int getId();

    friend std::ostream& operator<<(std::ostream& out, const crop& ob);
};


#endif //OOP_CROP_H
