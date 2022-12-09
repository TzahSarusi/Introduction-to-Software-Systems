#ifndef IP_H
#define IP_H

#include "field.h"

class IP : public Field {
private:
    unsigned int min_ip;
    unsigned int max_ip;
public:
    //constructor and deconstructor
    IP(String parameter);
    ~IP();
    //match_value: recieves string and checks
    //if packet fulfills rule
    bool match_value(String packet) const;
    //set_value: recieve rule and set it
    bool set_value(String val);
};

#endif


