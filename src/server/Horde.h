//
// Created by facundo on 31/10/17.
//

#ifndef TOWERDEFENSE_HORDE_H
#define TOWERDEFENSE_HORDE_H

#include <string>

class Horde {
public:
    Horde();
    Horde(std::string& type, int time_before_arrival, int quantity,
          unsigned int path_number);

    int getTimeBeforeArrival() const;
    int getQuantity() const;
    unsigned int getPathNumber() const;
    const std::string& getType() const;

private:
    std::string type;
    int time_before_arrival;
    int quantity;
    unsigned int path_number;
};


#endif //TOWERDEFENSE_HORDE_H
