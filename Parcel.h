//
// Created by danie on 12/6/2023.
//

#ifndef OOP_PARCEL_H
#define OOP_PARCEL_H


#include <iostream>

class parcel {
private:
    int parcel_id;
    static int Id;
    long double size;
    long double occupied_area;

public:
    explicit parcel(long double size = 0);

    parcel(const parcel& other);

    ~parcel();

    void display_parcel();

    int getParcelId() const;

    void setParcelId(int parcelId);

    long double getSize() const;

    void setSize(long double size);

    long double getOccupiedArea() const;

    void setOccupiedArea(long double occupiedArea);

    static int getId();

    friend std::ostream &operator<<(std::ostream& out, const parcel& ob);

    parcel& operator=(const parcel& other);
};

#endif //OOP_PARCEL_H
