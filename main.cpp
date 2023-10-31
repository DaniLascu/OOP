#include <iostream>
#include <string>

using namespace std;

class livestock {
private:
    int animal_id;
    static int number_of_animals;
    string animal_name;
    int weight;
    const static string owner;

public:
    livestock(string name = "unknown", int Weight = 0) : animal_id(number_of_animals) {
        this->animal_name = name;
        this->weight = Weight;
        number_of_animals++;
    }
    livestock(const livestock &other) : animal_id(other.animal_id), animal_name(other.animal_name), weight(other.weight) {

    }
    ~livestock() {}
    void display()
    {
        cout<<"Id animal "<<animal_id<<"\n";
        cout<<"Nume animal "<<animal_name<<"\n";
        cout<<"Greutate animal "<<weight<<"\n";
    }
    void set_weight(int kg)
    {
        weight = kg;
    }
    void set_name(string name)
    {
        animal_name = name;
    }
    int get_weight()
    {
        cout<<weight;
        return weight;
    }
    string get_name()
    {
        cout<<animal_name;
        return animal_name;
    }

    static int getNumberOfAnimals();

    friend ostream &operator<<(ostream& out, const livestock& ob);
    livestock &operator=(const livestock &other) {
        if (this == &other) {
            return *this;
        }
        this->animal_id = other.animal_id;
        this->animal_name = other.animal_name;
        this->weight = other.weight;
        return *this;
    }
};

// Initialize the static member
int livestock::number_of_animals = 0;
const  string livestock::owner = "Dani";

ostream& operator<<(ostream& out, const livestock& ob) {
    out<<"Id: "<<ob.animal_id<<endl;
    out<<"Nume: "<<ob.animal_name<<endl;
    out<<"Greutate: "<<ob.weight<<endl;
    return out;
}

int livestock::getNumberOfAnimals() {
    return number_of_animals;
}

//parcela
class parcel{
private:
    int parcel_id;
    static int Id;
    double size;
    double occupied_area;
public:
    parcel(double size):parcel_id(Id),occupied_area(0){
        this->size=size;
        Id++;
    }
    parcel(const parcel& other){
        parcel_id = other.parcel_id;
        size = other.size;
        occupied_area = other.occupied_area;
    }
    ~parcel(){}
    void display_parcel() {
        cout << "Id zona " << parcel_id << "\n";
        cout << "Dimensiune parcela " << size << "\n";
        cout << "Dimensiune ocupata " << occupied_area << "\n";

    }

    int getParcelId() const;

    void setParcelId(int parcelId);

    double getSize() const;

    void setSize(double size);

    double getOccupiedArea() const;

    void setOccupiedArea(double occupiedArea);

    static int getId();
    friend ostream &operator<<(ostream& out, const parcel& ob);


};
int parcel::Id = 1;

int parcel::getParcelId() const {
    return parcel_id;
}

void parcel::setParcelId(int parcelId) {
    parcel_id = parcelId;
}

double parcel::getSize() const {
    return size;
}

void parcel::setSize(double size) {
    parcel::size = size;
}

double parcel::getOccupiedArea() const {
    return occupied_area;
}

void parcel::setOccupiedArea(double occupiedArea) {
    occupied_area = occupied_area + occupiedArea;
}

int parcel::getId() {
    return Id;
}
ostream& operator<<(ostream& out, const parcel& ob) {
    out<<"Id: "<<ob.parcel_id<<endl;
    out<<"Size: "<<ob.size<<endl;
    out<<"Zona ocupata: "<<ob.occupied_area<<endl;
    return out;
}
//fructe
class crop{
private:
    string name;
    double surface_for_1_plant;
    double price_kg;
    int plant_id;
    static int Id;
public:
    crop(string name="unknown",double suprafata=0,double price = 0):plant_id(Id){
        Id++;
        this->name = name;
        surface_for_1_plant = suprafata;
        price_kg = price;
    }
    void display_crop()
    {
        cout<<"Nume planta "<<name<<"\n";
        cout<<"Id"<<plant_id<<"\n";
        cout<<"Suprafata/planta "<<surface_for_1_plant<<"\n";
        cout<<"Pret/kg "<<price_kg<<"\n";
    }

    virtual ~crop();

    const string &getName() const;

    void setName(const string &name);

    double getSurfaceFor1Plant() const;

    void setSurfaceFor1Plant(double surfaceFor1Plant);

    int getPlantId() const;

    void setPlantId(int plantId);

    double getPriceKg() const;

    void setPriceKg(double priceKg);

    static int getId();
    friend ostream &operator<<(ostream& out, const crop& ob);
};
int crop::Id = 1;

crop::~crop() {

}

const string &crop::getName() const {
    return name;
}

void crop::setName(const string &name) {
    crop::name = name;
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

double crop::getPriceKg() const {
    return price_kg;
}

void crop::setPriceKg(double priceKg) {
    price_kg = priceKg;
}
ostream& operator<<(ostream& out, const crop& ob) {
    out<<"Id: "<<ob.plant_id<<endl;
    out<<"nume: "<<ob.name<<endl;
    out<<"pret/kg: "<<ob.price_kg<<endl;
    out<<"suprafata/planta: "<<ob.surface_for_1_plant<<endl;
    return out;
}
//cultura plante
class culture{
private:
    int id_culture;
    static int Id;
    string plant_type;
    int plant_id;
    int number_of_plants;
    int size;
    crop plant;
    parcel lot;
public:
    culture(const crop &plant,  parcel &lot, int number);

    virtual ~culture();

    void display() const;

    int getIdCulture() const;

    void setIdCulture(int idCulture);

    const string &getPlantType() const;

    void setPlantType(const string &plantType);

    int getPlantId() const;

    void setPlantId(int plantId);

    int getNumberOfPlants() const;

    void setNumberOfPlants(int numberOfPlants);

    int getSize() const;

    void setSize(int size);

    const crop &getPlant() const;

    void setPlant(const crop &plant);

    const parcel &getLot() const;

    void setLot(const parcel &lot);

    friend ostream &operator<<(ostream& out, const culture& ob);
};
int culture::Id = 1;

culture::culture(const crop &plant, parcel &lot, int number)
        : id_culture(Id++), plant(plant), lot(lot), number_of_plants(number) {
    this->plant_type = plant.getName();
    this->plant_id = plant.getPlantId();
    if((lot.getSize() - lot.getOccupiedArea()) < plant.getSurfaceFor1Plant()){
        cout<<"nu se poate planta pe acest lot";
        //setter lot
    }
    else if( plant.getSurfaceFor1Plant() * number_of_plants > (lot.getSize() - lot.getOccupiedArea())){
        cout<<"alege un nr mai mic de plante, mai mic deacat "<<(lot.getSize()-lot.getOccupiedArea())/plant.getSurfaceFor1Plant()<<"\n";
        //setter numar_plante
        int nr;
        cin>>nr;
        if(nr<=(lot.getSize()-lot.getOccupiedArea())/plant.getSurfaceFor1Plant())
        {
            number_of_plants = nr;
            size = plant.getSurfaceFor1Plant() * number_of_plants;
            lot.setOccupiedArea(size);
        }
        else{
            cout<<"nr introdus este prea mare";
            number_of_plants = 0;
        }

    }
    else {
        size = plant.getSurfaceFor1Plant() * number_of_plants;
        lot.setOccupiedArea(size);
    }
}

culture::~culture() {

}

void culture::display() const {
    cout << "Culture ID: " << id_culture << endl;
    cout << "Plant Name: " << plant_id << endl;
    cout << "Plant Type: " << plant_type << endl;
    cout << "Number of Plants: " << number_of_plants << endl;
    cout << "Size: " << size << endl;
}

int culture::getIdCulture() const {
    return id_culture;
}

void culture::setIdCulture(int idCulture) {
    id_culture = idCulture;
}

const string &culture::getPlantType() const {
    return plant_type;
}

void culture::setPlantType(const string &plantType) {
    plant_type = plantType;
}

int culture::getPlantId() const {
    return plant_id;
}

void culture::setPlantId(int plantId) {
    plant_id = plantId;
}

int culture::getNumberOfPlants() const {
    return number_of_plants;
}

void culture::setNumberOfPlants(int numberOfPlants) {
    number_of_plants = numberOfPlants;
}

int culture::getSize() const {
    return size;
}

void culture::setSize(int size) {
    culture::size = size;
}

const crop &culture::getPlant() const {
    return plant;
}

void culture::setPlant(const crop &plant) {
    culture::plant = plant;
}

const parcel &culture::getLot() const {
    return lot;
}

void culture::setLot(const parcel &lot) {
    culture::lot = lot;
}

ostream& operator<<(ostream& out, const culture& ob) {
    out<<"Id cultura: "<<ob.id_culture<<endl;
    out<<"Nume planta: "<<ob.plant_type<<endl;
    out<<"Id planta "<<ob.plant_id<<endl;
    out<<"Numar plante: "<<ob.number_of_plants<<endl;
    out<<"Suprafata cultura: "<<ob.size<<endl;

    // functia returneaza ostream& deci trebuie as returnam obiectul out
    return out;
}
int main() {

    crop planta("morcov", 0.04, 1);
    planta.display_crop();
    cout<<"\n\n";
    parcel lot(1000);
    lot.display_parcel();
    cout<<"\n\n";
    culture cultura_1(planta,lot,20000);
    cout<<cultura_1;
    cout<<"\n";
    lot.display_parcel();
    cout<<"\n";
    crop planta_2("cartofi",0.1,2.5);
    planta_2.display_crop();
    cout<<"\n";
    culture cultura_2(planta_2,lot,1500);
    cout<<cultura_2;
    lot.display_parcel();
    return 0;
}
