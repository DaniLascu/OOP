//
// Created by danie on 12/8/2023.
//
/*
 * clasa Owner centralizeaza toate resursele fermei
 * pastreaza balanta contului fermei i.e. suma din contul fermei
 * in clasa Owner se pastreaza un vector de tip pointer de livestock in care se pastreaza toate animalele fermei
 * se pastreaza un vector de pointeri de parcel unde se pastreaza toate loturile detinute de ferma, pe care se pot crea culturi
 * se pastreaza un vector de tip pointer de crop unde se pastreaza toate plantele disponobile
 * se pstreaza un vector de tip Culture unde se pastreaza culturile fermei
 * loturile sunt prestabilite si se insereaza automat la inceperea programului
 * userul poate introduce orice tip de planta vrea pe parcursul programului
 * cand se creaza o cultura din balanta se scade suma necesara cumpararii plantelor care vor fi plantate
 * cand se vand plante dintr-o cultura se adauga in balanta nr_plante_vandute * pret_vanzare_o_planta
 * userul poate sa cumpere animale, care costa o anumita suma
 * Am implementat Observer pattern. Clasa Owner mosteneste clasa abstracta Observer si implementeaza functia
 * update
 * Subiectul ale carei modificari sunt observate de Owner este clasa Culture.
 * Owner este notificat atunci cand asupra unei culturi sunt facute modificari
 */
#ifndef OOP_OWNER_H
#define OOP_OWNER_H


#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "livestock.h"
#include "Parcel.h"
#include "Crop.h"
#include "Culture.h"
#include "Observer.h"

class Owner : public Observer{
private:
    std::string name;
    long double balance;
    std::vector<std::shared_ptr<livestock>> Animals;
    std::vector<std::shared_ptr<parcel>> Lots;
    std::vector<std::shared_ptr<crop>> Crops;
    std::vector<Culture> Cultures;
    std::mutex balanceMutex;

public:
    Owner(const std::string Name = "Dani", long double Balance = 10000);
    ~Owner();

    void Add_lots(std::shared_ptr<parcel> &lot);
    void Add_crops(std::shared_ptr<crop> &crop);
    void Add_Culture();
    void sell_crops();
    void Add_Animal(std::shared_ptr<livestock> animal);
    void Income_Generation();

    const std::string &getName() const;
    long double getBalance() const;
    void display_balance();
    void display_lots();
    void display_crops();
    void display_cultures();
    void display_animals();
    void display_owner();
    void update(Culture* culture) override;
};

#endif //OOP_OWNER_H
