//
// Created by danie on 12/7/2023.
//
// Culture.cpp
/*
 * la crearea unei culturi pot aparea 2 probleme
 * 1.nu e destul spatiu pentru 1 planta din tipul ales. se arunca NotEnoughFor1
 * 2.nr de plante e prea mare pentru cat spatiu mai este pe lotul ales
 * se da val maxima de plante care pot fi plantate, iar userul e rugat sa reintroduca
 * un nr mai mic ca val maxima. daca si acum nr de plante introdus este mai mare se arunca NrTooLarge
 * cand se creaza cultura suprafata culturii este adaugata la suprafata ocupata din lotul asociat culturii
 * Observatorii sunt notificati atunci cand se creaza cultura sau cand se modifica suprafata(se vand plante)
 */
#include "Culture.h"
#include "Exceptii.h"
#include "Parcel.h"
#include "Crop.h"

int Culture::Id = 0;

Culture::Culture() : id_culture(Id++), size(0), number_of_plants(0),
                     lot(std::make_shared<parcel>()), plant(std::make_shared<crop>()) {}

Culture::Culture(int Nr, std::shared_ptr<parcel>& Lot, std::shared_ptr<crop>& Plant)
        : id_culture(Id++), number_of_plants(Nr), lot(Lot), plant(Plant) {
    if ((lot->getSize() - lot->getOccupiedArea()) < plant->getSurfaceFor1Plant()) {
        throw NotEnoughFor1();
    } else if ((plant->getSurfaceFor1Plant() * this->number_of_plants) > (lot->getSize() - lot->getOccupiedArea())) {
        std::cout << "Alege un nr mai mic de plante decat "
                  << (lot->getSize() - lot->getOccupiedArea()) / plant->getSurfaceFor1Plant() << ": ";
        int nr;
        std::cin >> nr;
        if (nr <= (lot->getSize() - lot->getOccupiedArea()) / plant->getSurfaceFor1Plant()) {
            number_of_plants = nr;
            this->size = number_of_plants * plant->getSurfaceFor1Plant();
            lot->setOccupiedArea(size);
        } else {
            throw NrTooLarge();
        }
    } else {
        size = plant->getSurfaceFor1Plant() * number_of_plants;
        lot->setOccupiedArea(size);
    }
    notifyObservers();
}

Culture::~Culture() {}

void Culture::display_culture() {
    std::cout << "Cultura cu Id: " << this->id_culture << std::endl;
    std::cout << "Dimensiunea: " << this->size << std::endl;
    std::cout << "Numar plante: " << this->number_of_plants << std::endl;
    lot->display_parcel();
    plant->display_crop();
}

int Culture::get_id_culture() const {
    return this->id_culture;
}

long double Culture::get_size() const {
    return this->size;
}

void Culture::set_size(long double size) {
    this->size = size;
    notifyObservers();
}

int Culture::getNumberOfPlants() const {
    return number_of_plants;
}

void Culture::setNumberOfPlants(int numberOfPlants) {
    number_of_plants = numberOfPlants;
    //notifyObservers();
}

std::shared_ptr<parcel>& Culture::getLot() {
    return lot;
}

void Culture::setLot(std::shared_ptr<parcel>& lot) {
    Culture::lot = lot;
}

std::shared_ptr<crop>& Culture::getPlant() {
    return plant;
}

void Culture::setPlant(std::shared_ptr<crop>& plant) {
    Culture::plant = plant;
}

void Culture::addObserver(Observer* observer) {
    observatori.push_back(observer);
}

void Culture::notifyObservers() {
    for (Observer* observer : observatori) {
        observer->update(this);
    }
}