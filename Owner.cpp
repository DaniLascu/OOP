//
// Created by danie on 12/8/2023.
//
/*
 * functia addCulture creaza culturi si le introduce in vectorul de culturi
 * daca in balanta nu sunt suficienti bani pentru a cumpara nr de plante introdus de user
 * se arunca eroarea NotMoney
 * daca lotul ales nu are o suprafata libera suficient de mare pentru numarul de plante ales pentru cultura
 * se arunca eroarea NrTooLarge (s-a ales un nr de plante prea mare penru suprafata disponibila din lot)
 * functia Add_Animal introduce animale noi in vectorul de animale
 * daca nu exista suficienti bani pentru a cumpara un anumit animal se arunca eroare NotMoney
 *
 * venitul se genereaza din 2 surse:
 * 1. Vanzarea de plante. cand plante sunt vandute dintr-o cultura balanta contului creste, suprafata culturii
 * este scazuta cu nr_plante_vandute * suprafata_1_planta si suprafata ocupata a lotului asociat culturii respective
 * este scazuta cu aceeasi valoare (se elibereaza suprafata ocupata din lot).
 * Daca dintr-o cultura sunt vandute toate plantele cultura respective este stearsa din vectorul de culturi
 * 2.functia IncomeGeneration. Cele 3 tipuri de animale posibile sunt pui, vaci si oi.
 * se considera ca puii si vacile produc oua si lapte zilnic, produse care sunt vandute zilnic.
 * se considera ca oile produc lana saptamanal, deci lana oilor se va vinde o data la 7 zile.
 * In logica programului o zi = 10 sec, iar o saptamana = 70 sec
 * Functia adauga la balanta la fiecare 10 sec profitul produs de fiecare pui si vaca
 * si o data la 70 de sec profitul produs de fiecara oaie
 * Am implementat functia update. Aceasta notifica clasa Owner atunci cand o cultura este modificata, afisand-o
 * Cand o cultura e creata Owner este introdus in lista de observatori
 */
#include "Owner.h"
#include "Exceptii.h"
#include "livestock.h"
#include "Cow.h"
#include "Chicken.h"
#include "Sheep.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>

Owner::Owner(const std::string Name, long double Balance) : name(Name), balance(Balance) {}

Owner::~Owner() {}

void Owner::Add_lots(std::shared_ptr<parcel> &lot) {
    Lots.push_back(lot);
}

void Owner::Add_crops(std::shared_ptr<crop> &crop) {
    Crops.push_back(crop);
}

void Owner::Add_Culture() {
    for (int i = 0; i < Lots.size(); i++) {
        std::cout << "Parcela cu nr: " << i << std::endl;
        Lots[i]->display_parcel();
    }

    std::cout << "Alege o parcela\n";
    int n;
    std::cin >> n;

    if (n < 0 || n >= Lots.size())
        throw std::logic_error("Index invalid\n");

    for (int i = 0; i < Crops.size(); i++) {
        std::cout << "Planta cu nr: " << i << std::endl;
        Crops[i]->display_crop();
    }

    std::cout << "Alege o planta\n";
    int m;
    std::cin >> m;

    if (m < 0 || m >= Crops.size())
        throw std::logic_error("Index invalid\n");

    int nr;
    std::cout << "Alege nr de plante\n";
    std::cin >> nr;

    if (balance < nr * Crops[m]->getCostFor1Plant()) {
        throw NotMoney();
    }

    if ((Lots[n]->getSize() - Lots[n]->getOccupiedArea()) < nr * Crops[m]->getSurfaceFor1Plant()) {
        throw NrTooLarge();
    } else {
        try {
            balance -= nr * Crops[m]->getCostFor1Plant();
            Cultures.push_back(Culture(nr, Lots[n], Crops[m]));
        } catch (const NotEnoughFor1 &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        } catch (const NrTooLarge &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }
    if (!Cultures.empty()) {
        Culture& lastCulture = Cultures.back();
        lastCulture.addObserver(this);
        lastCulture.notifyObservers();  // Notify immediately after setting the observer
    } else {
        std::cout << "Cultures vector is empty." << std::endl;
    }

}

void Owner::sell_crops() {
    for (int i = 0; i < Cultures.size(); i++) {
        std::cout << "Id cultura: " << i << "\n";
        Cultures[i].display_culture();
    }

    int culture_index;
    std::cout << "Alege o cultura:\n";
    std::cin >> culture_index;

    std::cout << "Alege nr de plante pe care le vinzi\n";
    int numberOfCrops;
    std::cin >> numberOfCrops;

    if (culture_index >= 0 && culture_index < Cultures.size()) {
        if (Cultures[culture_index].getNumberOfPlants() >= numberOfCrops) {
            balance += numberOfCrops * Cultures[culture_index].getPlant()->getPriceUnit();

            double x = -(Cultures[culture_index].getPlant()->getSurfaceFor1Plant() * numberOfCrops);
            Cultures[culture_index].getLot()->setOccupiedArea(x);

            Cultures[culture_index].setNumberOfPlants(Cultures[culture_index].getNumberOfPlants() - numberOfCrops);

            Cultures[culture_index].set_size(Cultures[culture_index].getNumberOfPlants() * Cultures[culture_index].getPlant()->getSurfaceFor1Plant());

            if (Cultures[culture_index].getNumberOfPlants() == 0) {
                // Remove the culture from the vector
                Cultures.erase(Cultures.begin() + culture_index);
            }

            std::cout << "Crops sold successfully!" << std::endl;
        } else {
            std::cout << "Not enough crops in the culture to sell." << std::endl;
        }
    } else {
        std::cout << "Invalid culture index." << std::endl;
    }
}

void Owner::Add_Animal(std::shared_ptr<livestock> animal) {
    if (balance < animal->getPrice())
        throw NotMoney();

    balance -= animal->getPrice();

    if (std::dynamic_pointer_cast<Cow>(animal) != NULL) {
        Animals.push_back(std::make_shared<Cow>(*std::dynamic_pointer_cast<Cow>(animal)));
    } else if (std::dynamic_pointer_cast<Sheep>(animal) != NULL) {
        Animals.push_back(std::make_shared<Sheep>(*std::dynamic_pointer_cast<Sheep>(animal)));
    } else if (std::dynamic_pointer_cast<Chicken>(animal) != NULL) {
        Animals.push_back(std::make_shared<Chicken>(*std::dynamic_pointer_cast<Chicken>(animal)));
    }
}

void Owner::Income_Generation() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(10));

        std::lock_guard<std::mutex> lock(balanceMutex);

        for (int i = 0; i < Animals.size(); i++) {
            if (std::dynamic_pointer_cast<Cow>(Animals[i]) != nullptr ||
                std::dynamic_pointer_cast<Chicken>(Animals[i]) != nullptr) {
                balance += Animals[i]->total_proffit();
            }
            if (std::dynamic_pointer_cast<Sheep>(Animals[i]) != nullptr) {
                balance += Animals[i]->total_proffit() / 7;
            }
        }
    }
}

const std::string &Owner::getName() const {
    return name;
}

long double Owner::getBalance() const {
    return balance;
}

void Owner::display_balance() {
    std::cout << "Balanta din cont: " << this->balance << "\n";
}

void Owner::display_lots() {
    std::cout<<"\nLoturile fermei: \n";
    for (int i = 0; i < Lots.size(); i++) {
        Lots[i]->display_parcel();
        std::cout<<"\n";
    }
    std::cout << std::endl;
}

void Owner::display_crops() {
    std::cout<<"\nPlantele disponibile\n";
    for (int i = 0; i < Crops.size(); i++) {
        Crops[i]->display_crop();
        std::cout<<"\n";
    }
    std::cout << std::endl;
}

void Owner::display_cultures() {
    std::cout<<"\nCulturile disponibile\n";
    for (int i = 0; i < Cultures.size(); i++) {
        Cultures[i].display_culture();
        std::cout<<"\n";
    }
    std::cout << std::endl;
}

void Owner::display_animals() {
    std::cout<<"\nAnimalele detinute\n";
    for (int i = 0; i < Animals.size(); i++) {
        Animals[i]->display();
        std::cout<<"\n";
    }
    std::cout << std::endl;
}

void Owner::display_owner() {
    std::cout << this->name << std::endl;
    display_balance();
    display_crops();
    display_lots();
    display_animals();
}

void Owner::update(Culture *culture){
    std::cout<<"NOTIFICARE\n";
    culture->display_culture();
    std::cout<<"SFARSIT NOTIFICARE\n";
}