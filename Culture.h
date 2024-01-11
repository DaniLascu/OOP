//
// Created by danie on 12/7/2023.
//
/*
 * se pot crea culturi. fiecare cultura retine numarul de plante din care este formata
 * in clasa cultura se mentine un pointer catre lotul de pamant pe care e crescuta cultura
 * si un pointer catre planta care constituie cultura
 * dimensiune = nr_plante * suprafata_unei_plante
 * mai multe culturi pot sa fie situate pe acelasi lot de pamant in limita spatiului disponibil
 * Am implementat Observer pattern. clasa Culture este subiectul, observat de clasa Owner
 * Mentine o lista de observatori si apeleaza functia notifyObservers pentru a-i notifica atunci cand s-a
 * intamplat o schimbare
 */
#ifndef OOP_CULTURE_H
#define OOP_CULTURE_H


#include <iostream>
#include <memory>
#include "Parcel.h"
#include "Crop.h"
#include <vector>
#include "Observer.h"

class Culture {
private:
    int id_culture;
    static int Id;
    long double size;
    int number_of_plants;
    std::shared_ptr<parcel> lot;
    std::shared_ptr<crop> plant;
    std::vector<Observer*> observatori;

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

    void addObserver(Observer* observer);
    void notifyObservers();
};


#endif //OOP_CULTURE_H
