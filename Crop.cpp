//
// Created by danie on 12/6/2023.
//


#include "Crop.h"
#include <iostream>
#include <string>

int crop::Id = 0;

crop::crop(const std::string& name, double surface, double cost, double price)
        : name(name), surface_for_1_plant(surface), cost_for_1_plant(cost), price_unit(price), plant_id(Id++) {}


crop::crop(const crop& other)
        : name(other.name), surface_for_1_plant(other.surface_for_1_plant),
          cost_for_1_plant(other.cost_for_1_plant), price_unit(other.price_unit), plant_id(other.plant_id) {}


crop::~crop() {
    // Destructor implementation (if needed)
}

void crop::display_crop() {
    std::cout << "Nume planta " << name << "\n";
    std::cout << "Id " << plant_id << "\n";
    std::cout << "Suprafata/planta " << surface_for_1_plant << "\n";
    std::cout << "Pret/unitate " << price_unit << "\n";
    std::cout << "Cost cumparare o planta: " << cost_for_1_plant << "%" << std::endl;
}

const std::string& crop::getName() const {
    return name;
}

void crop::setName(const std::string& local_name) {
    name = local_name;
}

double crop::getSurfaceFor1Plant() const {
    return surface_for_1_plant;
}

void crop::setSurfaceFor1Plant(double surfaceFor1Plant) {
    surface_for_1_plant = surfaceFor1Plant;
}

int crop::getPlantId() const {
    return plant_id;
}

void crop::setPlantId(int plantId) {
    plant_id = plantId;
}

int crop::getId() {
    return Id;
}

double crop::getPriceUnit() const {
    return price_unit;
}

void crop::setPriceUnit(double priceKg) {
    price_unit = priceKg;
}

std::ostream& operator<<(std::ostream& out, const crop& ob) {
    out << "Id: " << ob.plant_id << std::endl;
    out << "Nume: " << ob.name << std::endl;
    out << "Pret/unitate: " << ob.price_unit << std::endl;
    out << "Cost cumparare: " << ob.cost_for_1_plant << "%" << std::endl;
    out << "Suprafata/planta: " << ob.surface_for_1_plant << std::endl;
    return out;
}

double crop::getCostFor1Plant() const {
    return cost_for_1_plant;
}

void crop::setCostFor1Plant(double costFor1Plant) {
    cost_for_1_plant = costFor1Plant;
}
