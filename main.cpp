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

class Owner{
private:
    std::string name;
    long double balance;
    std::vector<std::shared_ptr<livestock>> Animals;
    std::vector<std::shared_ptr<parcel>> Lots;
    std::vector<std::shared_ptr<crop>> Crops;
    std::vector<Culture> Cultures;
    std::mutex balanceMutex; // Mutex for synchronizing access to balance
public:
    Owner(const std::string Name = "Dani", long double Balance = 10000): name(Name),balance(Balance){}
    ~Owner(){}
    void Add_lots(std::shared_ptr<parcel> &lot){
        Lots.push_back((lot));
    }
    void Add_crops(std::shared_ptr<crop> &crop){
        Crops.push_back(crop);
    }
    void Add_Culture(){
        for(int i = 0; i < Lots.size(); i++){
            std::cout<<"Parcela cu nr: "<<i<<std::endl;
            Lots[i]->display_parcel();
        }
        std::cout<<"Alege o parcela\n";
        int n;
        std::cin>>n;
        if(n < 0 || n > Lots.size())
            throw std::logic_error("Index invalid\n");

        for(int i = 0; i < Crops.size(); i++){
            std::cout<<"Planta cu nr: "<<i<<std::endl;
            Crops[i]->display_crop();
        }
        std::cout<<"Alege o planta\n";
        int m;
        std::cin>>m;
        if(m < 0 || m > Crops.size())
            throw std::logic_error("Index invalid\n");

        int nr;
        std::cout<<"Alege nr de plante\n";
        std::cin>>nr;
        if(balance < nr * Crops[m]->getCostFor1Plant()){
            throw NotMoney();
            //Cultures.pop_back();
        }
        if((Lots[n]->getSize() - Lots[n]->getOccupiedArea()) < nr * Crops[m]->getSurfaceFor1Plant()){
            throw NrTooLarge();
            //Cultures.pop_back();
        }
        else{
            try {
                balance -= nr * Crops[m]->getCostFor1Plant();
                Cultures.push_back(Culture(nr, Lots[n], Crops[m]));
            } catch (const NotEnoughFor1& e) {
                std::cerr << "Exception: " << e.what() << std::endl;
                // Handle the exception appropriately (log, display message, etc.)
            } catch (const NrTooLarge& e) {
                std::cerr << "Exception: " << e.what() << std::endl;
                // Handle the exception appropriately (log, display message, etc.)
            }
        }

    }
    void sell_crops(){
        for(int i = 0; i < Cultures.size(); i++){
            std::cout<<"Id cultura: "<<i<<"\n";
            Cultures[i].display_culture();
        }
        int culture_index;
        std::cout<<"Alege o cultura:\n";
        std::cin>>culture_index;
        std::cout<<"Alege nr de plante pe care le vinzi\n";
        int numberOfCrops;
        std::cin>>numberOfCrops;
        if (culture_index >= 0 && culture_index < Cultures.size()) {

            // Check if there are enough crops to sell
            if (Cultures[culture_index].getNumberOfPlants() >= numberOfCrops) {
                // Update balance
                balance += numberOfCrops * Cultures[culture_index].getPlant()->getPriceUnit();

                // Clear occupied area on the parcel
                double x = -(Cultures[culture_index].getPlant()->getSurfaceFor1Plant()*numberOfCrops);
                Cultures[culture_index].getLot()->setOccupiedArea(x);

                // Update number of plants in the culture
                Cultures[culture_index].setNumberOfPlants(Cultures[culture_index].getNumberOfPlants() - numberOfCrops);

                std::cout << "Crops sold successfully!" << std::endl;
            }
            else {
                std::cout << "Not enough crops in the culture to sell." << std::endl;
            }
        }
        else {
            std::cout << "Invalid culture index." << std::endl;
        }

    }
    void Add_Animal(std::shared_ptr<livestock> animal){
        if(balance < animal->getPrice())
            throw NotMoney();
        balance -= animal->getPrice();
        if(std::dynamic_pointer_cast<Cow> (animal) != NULL){
            Animals.push_back(std::make_shared<Cow>(*std::dynamic_pointer_cast<Cow>(animal)));
        }
        else if(std::dynamic_pointer_cast<Sheep> (animal) != NULL){
            Animals.push_back(std::make_shared<Sheep>(*std::dynamic_pointer_cast<Sheep>(animal)));
        }
        else if(std::dynamic_pointer_cast<Chicken> (animal) != NULL){
            Animals.push_back(std::make_shared<Chicken>(*std::dynamic_pointer_cast<Chicken>(animal)));
        }
    }
    void Income_Generation(){
        while (true) {
            // Increment balance every 10 seconds by 5 for cows and chickens
            std::this_thread::sleep_for(std::chrono::seconds(10));

            // Lock the mutex to ensure exclusive access to balance
            std::lock_guard<std::mutex> lock(balanceMutex);

            for (int i = 0; i < Animals.size(); i++) {
                if (std::dynamic_pointer_cast<Cow>(Animals[i]) != nullptr ||
                    std::dynamic_pointer_cast<Chicken>(Animals[i]) != nullptr) {
                    balance += Animals[i]->total_proffit();
                }
                if (std::dynamic_pointer_cast<Sheep>(Animals[i]) != nullptr) {
                    balance += Animals[i]->total_proffit()/7;
                }
            }

            // Unlock the mutex when done with balance
            // The lock_guard's destructor will do this automatically
        }
    }

    const std::string &getName() const {
        return name;
    }

    long double getBalance() const {
        return balance;
    }
    void display_balance(){
        std::cout<<"Balanta din cont: "<<this->balance<<"\n";
    }
    void display_lots(){
        for(int i = 0; i < Lots.size(); i++)
            Lots[i]->display_parcel();
        std::cout<<std::endl;
    }
    void display_crops(){
        for(int i = 0; i < Crops.size(); i++)
            Crops[i]->display_crop();
        std::cout<<std::endl;
    }
    void display_cultures(){
        for(int i = 0; i < Cultures.size(); i++)
            Cultures[i].display_culture();
        std::cout<<std::endl;
    }
    void display_animals(){
        for(int i = 0; i < Animals.size(); i++)
            Animals[i]->display();
        std::cout<<std::endl;
    }
    void display_owner(){
        std::cout<<this->name<<std::endl;
        display_balance();
        display_crops();
        display_lots();
        display_animals();
    }
};

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
                    if(option2 == 1){
                            double milk;
                            std::cout << "Cati litrii de lapte produce pe zii\n";
                            std::cin >> milk;
                            double price_per_litter;
                            std::cout << "Pretul unui litru de lapte\n";
                            std::cin >> price_per_litter;
                            //double proffit;
                            std::cout << "Profit per litru\n";
                            std::cin >> proffit;
                            std::string name;
                            std::cout << "Numele\n";
                            std::cin >> name;
                            int weight;
                            std::cout << "Greutate\n";
                            std::cin >> weight;
                            animal = std::make_shared<Cow>(milk, price_per_litter, proffit, name, weight);

                    }
                    if(option2 == 2){
                            double eggs;
                            std::cout << "Cate oua produce pe zii\n";
                            std::cin >> eggs;
                            double price_per_egg;
                            std::cout << "Pretul unui ou\n";
                            std::cin >> price_per_egg;
                            //double proffit;
                            std::cout << "Profit per ou\n";
                            std::cin >> proffit;
                            std::string name;
                            std::cout << "Numele\n";
                            std::cin >> name;
                            int weight;
                            std::cout << "Greutate\n";
                            std::cin >> weight;
                            animal = std::make_shared<Chicken>(eggs, price_per_egg, proffit, name, weight);

                    }
                    if(option2 == 3){
                            double whool;
                            std::cout << "Cata lana produce pe saptamana\n";
                            std::cin >> whool;
                            double price_per_kg;
                            std::cout << "Pretul unui kg de lana\n";
                            std::cin >> price_per_kg;
                            //double proffit;
                            std::cout << "Profit per kg\n";
                            std::cin >> proffit;
                            std::string name;
                            std::cout << "Numele\n";
                            std::cin >> name;
                            int weight;
                            std::cout << "Greutate\n";
                            std::cin >> weight;
                            animal = std::make_shared<Chicken>(whool, price_per_kg, proffit, name, weight);

                    }
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
