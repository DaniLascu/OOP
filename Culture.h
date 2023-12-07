//
// Created by danie on 12/7/2023.
//

#ifndef OOP_CULTURE_H
#define OOP_CULTURE_H


#include <iostream>
#include <memory>
#include "Parcel.h"
#include "Crop.h"

class Culture {
private:
    int id_culture;
    static int Id;
    long double size;
    int number_of_plants;
    std::shared_ptr<parcel> lot;
    std::shared_ptr<crop> plant;

public:
    Culture();
    Culture(int Nr, std::shared_ptr<parcel>& Lot, std::shared_ptr<crop>& Plant);
    ~Culture();

    void display_culture();
    int get_id_culture() const;
    long double get_size() const;
    void set_size(long double size);

    int getNumberOfPlants() const;
    void setNumberOfPlants(int numberOfPlants);

    std::shared_ptr<parcel>& getLot();
    void setLot(std::shared_ptr<parcel>& lot);

    std::shared_ptr<crop>& getPlant();
    void setPlant(std::shared_ptr<crop>& plant);
};


#endif //OOP_CULTURE_H
