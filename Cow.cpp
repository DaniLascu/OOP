//
// Created by danie on 12/6/2023.
//


#include "Cow.h"
#include <iostream>

int Cow::price = 500;  // Set a default price for Cow

Cow::Cow(double local_milk_production, double local_price_per_liter, double local_proffit,
         const std::string& name, int Weight)
        : livestock(name, Weight),
          milk_production_per_day(local_milk_production),
          price_per_liter(local_price_per_liter),
          proffit_per_litter(local_proffit) {
}

Cow::Cow(const Cow& other)
        : livestock(other),
          milk_production_per_day(other.milk_production_per_day),
          price_per_liter(other.price_per_liter),
          proffit_per_litter(other.proffit_per_litter) {
}

Cow::~Cow() {
    // Destructor implementation (if needed)
}

void Cow::display() {
    livestock::display();
    std::cout << "Litrii de lapte produsi pe zi: " << this->milk_production_per_day << std::endl;
    std::cout << "Pret / litru de lapte: " << this->price_per_liter << std::endl;
    std::cout << "Profit: " << this->proffit_per_litter << "%" << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Cow& ob) {
    out << "Id: " << ob.animal_id << std::endl;
    out << "Nume: " << ob.animal_name << std::endl;
    out << "Greutate: " << ob.weight << std::endl;
    out << "Litrii de lapte produsi pe zi: " << ob.milk_production_per_day << std::endl;
    out << "Pret / litru de lapte: " << ob.price_per_liter << std::endl;
    out << "Profit / litru ca %: " << ob.proffit_per_litter << std::endl;
    return out;
}

Cow& Cow::operator=(const Cow& other) {
    if (this == &other) {
        return *this;
    }
    this->animal_id = other.animal_id;
    this->animal_name = other.animal_name;
    this->weight = other.weight;
    this->milk_production_per_day = other.milk_production_per_day;
    this->price_per_liter = other.price_per_liter;
    this->proffit_per_litter = other.proffit_per_litter;
    return *this;
}

double Cow::getMilkProduction() const {
    return milk_production_per_day;
}

void Cow::setMilkProduction(double milkProduction) {
    milk_production_per_day = milkProduction;
}

double Cow::getPricePerLiter() const {
    return price_per_liter;
}

void Cow::setPricePerLiter(double pricePerLiter) {
    price_per_liter = pricePerLiter;
}

double Cow::getProffitPerLitter() const {
    return proffit_per_litter;
}

void Cow::setProffitPerLitter(double proffitPerLitter) {
    proffit_per_litter = proffitPerLitter;
}

double Cow::total_proffit() {
    return (this->milk_production_per_day * this->price_per_liter * this->proffit_per_litter);
}

int Cow::getPrice() {
    return price;
}