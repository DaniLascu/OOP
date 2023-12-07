//
// Created by danie on 12/6/2023.
//

#include "Sheep.h"
#include <iostream>

int Sheep::price = 300;

Sheep::Sheep(double local_whool, double local_price, double local_proffit, const std::string& name, int Weight)
        : livestock(name, Weight),
          whool_production_per_week(local_whool),
          whool_price_per_kg(local_price),
          proffit_per_kg(local_proffit) {
}

Sheep::Sheep(const Sheep& other)
        : livestock(other),
          whool_production_per_week(other.whool_production_per_week),
          whool_price_per_kg(other.whool_price_per_kg),
          proffit_per_kg(other.proffit_per_kg) {
}

Sheep::~Sheep() {
    // Destructor implementation (if needed)
}

void Sheep::display() {
    livestock::display();
    std::cout << "Cantitate de lana produsa intr-o saptamana: " << this->whool_production_per_week << std::endl;
    std::cout << "Pret / kg de lana: " << this->whool_price_per_kg << std::endl;
    std::cout << "Profit / kg ca %: " << this->proffit_per_kg << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Sheep& ob) {
    out << "Id: " << ob.animal_id << std::endl;
    out << "Nume: " << ob.animal_name << std::endl;
    out << "Greutate: " << ob.weight << std::endl;
    out << "Kg de lana produse: " << ob.whool_production_per_week << std::endl;
    out << "Pret / kg de lana: " << ob.whool_price_per_kg << std::endl;
    out << "Profit / kg ca %: " << ob.proffit_per_kg << std::endl;
    return out;
}

double Sheep::getWhoolProductionPerWeek() const {
    return whool_production_per_week;
}

void Sheep::setWhoolProductionPerWeek(double whoolProductionPerWeek) {
    whool_production_per_week = whoolProductionPerWeek;
}

double Sheep::getWhoolPricePerKg() const {
    return whool_price_per_kg;
}

void Sheep::setWhoolPricePerKg(double whoolPricePerKg) {
    whool_price_per_kg = whoolPricePerKg;
}

double Sheep::getProffitPerKg() const {
    return proffit_per_kg;
}

void Sheep::setProffitPerKg(double proffitPerKg) {
    proffit_per_kg = proffitPerKg;
}

double Sheep::total_proffit() {
    return (this->whool_production_per_week * this->whool_price_per_kg * this->proffit_per_kg);
}

int Sheep::getPrice() {
    return price;
}
