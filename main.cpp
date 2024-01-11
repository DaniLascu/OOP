#include <iostream>
#include "Parcel.h"
#include "Crop.h"
#include <memory>
#include "livestock.h"
#include "Sheep.h"
#include "Cow.h"
#include "Chicken.h"
#include <vector>
#include <thread>
#include <chrono>
#include <exception>
#include <mutex>
#include "Exceptii.h"
#include "Culture.h"
#include "Owner.h"
#include "AnimalFactory.h"


class Meniu{
private:
    Owner *farmer;
    //std::shared
public:
    Meniu(Owner *owner):farmer(owner){
        //this->start_meniu();
    }
    void afiseaza_meniu() const;
    void start_meniu();
};

void Meniu::afiseaza_meniu() const {
    std::cout << "----- MENIU -----\n";

    std::cout << "1. Cumpara un nou tip de planta\n";
    std::cout << "2. Creaza o cultura noua\n";
    std::cout << "3. Vanzare plante\n";
    std::cout << "4. Cumpara un nou animal\n";
    std::cout << "5. Afiseaza balanta cont-ului\n";
    std::cout << "6. Afiseaza loturile disponobile\n";
    std::cout << "7. Afiseaza plantele disponibile\n";
    std::cout << "8. Afiseaza culturile disponibile\n";
    std::cout << "9. Afiseaza animalele detinute\n";
    std::cout << "10. Afiseaza starea fermei\n";
    std::cout << "0. Inchide aplicatia\n";
}
void Meniu::start_meniu() {
    std::thread incomeThread(&Owner::Income_Generation, farmer);
    while(true) {
        this->afiseaza_meniu();
        int option;
        std::cout << "Introdu optiunea\n";
        std::cin >> option;
        try {
            switch (option) {
                case 0: {
                    return;
                }
                case 1: {
                    std::string nume;
                    std::cout<<"Introdu numele plantei\n";
                    std::cin>>nume;
                    double surface;
                    std::cout<<"Introdu suprafata ocupata de o planta\n";
                    std::cin>>surface;
                    double price;
                    std::cout<<"Introdu cu cat se vinde o planta\n";
                    std::cin>>price;
                    double cost;
                    std::cout<<"Introdu cu cat se cumpara o planta\n";
                    std::cin>>cost;
                    std::shared_ptr<crop> c1 = std::make_shared<crop>(nume,surface,price,cost);
                    farmer->Add_crops(c1);
                    break;
                }
                case 2:{
                    try{
                        farmer->Add_Culture();
                    }catch(NotEnoughFor1& e){
                        std::cout<<e.what()<<std::endl;
                    }
                    catch(NrTooLarge& e){
                        std::cout<<e.what()<<std::endl;
                    }
                    catch(NotMoney& e){
                        std::cout<<e.what()<<std::endl;
                    }
                    catch(std::logic_error& e){
                        std::cout<<e.what();
                    }
                    break;
                }
                case 3:{
                    farmer->sell_crops();
                    break;
                }
                case 4:{
                    int option2;
                    std::cout<<"Alege ce animal vrei sa adaugi\n";
                    std::cout<<"1. Vaca\n";
                    std::cout<<"2. Pui\n";
                    std::cout<<"3. Oaie\n";
                    try{
                        std::cin>>option2;
                        if(option2 != 1 && option2 != 2 && option2 != 3)
                            throw OptiuneInvalida();
                    }catch(OptiuneInvalida& e){
                        std::cout<<e.what()<<std::endl;
                    }
                    double proffit;
                    std::shared_ptr<livestock> animal;
                    AnimalFactory f;
                    animal = f.build(option2,proffit);
                    try{
                    if(proffit >= 1)
                        throw Profit_sub_unit();
                    farmer->Add_Animal(animal);

                    }catch(Profit_sub_unit& e){
                        std::cout<<e.what()<<std::endl;
                    }
                    catch(NotMoney& e){
                        std::cout<<e.what()<<std::endl;
                    }
                    break;
                }
                case 5:{
                    farmer->display_balance();
                    break;
                }
                case 6:{
                    farmer->display_lots();
                    break;
                }
                case 7:{
                    farmer->display_crops();
                    break;
                }
                case 8:{
                    farmer->display_cultures();
                    break;
                }
                case 9:{
                    farmer->display_animals();
                    break;
                }
                case 10:{
                    farmer->display_owner();
                    break;
                }
                default:
                    throw OptiuneInvalida();
            }
        }catch(OptiuneInvalida& e){
            std::cout<<e.what()<<std::endl;
        }
    }
}
int main() {

    std::shared_ptr<parcel> Lot1 = std::make_shared<parcel>(1000);
    std::shared_ptr<parcel> Lot2 = std::make_shared<parcel>(10000);
    std::shared_ptr<parcel> Lot3 = std::make_shared<parcel>(5000);
    std::shared_ptr<parcel> Lot4 = std::make_shared<parcel>(900);
    std::shared_ptr<parcel> Lot5 = std::make_shared<parcel>(4500);
    Owner farmer;
    farmer.Add_lots(Lot1);
    farmer.Add_lots(Lot2);
    farmer.Add_lots(Lot3);
    farmer.Add_lots(Lot4);
    farmer.Add_lots(Lot5);
    Meniu meniu(&farmer);
    meniu.start_meniu();
    return 0;
}
