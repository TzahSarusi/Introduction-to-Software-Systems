#ifndef PORT_H
#define PORT_H

#include "field.h"

class Port : public Field {
private:
    int minimumPortNumber;
    int maximumPortNumber;

public:
    Port(String patternValue);
    ~Port();
    bool set_value(String port_val);
    bool match_value(String port) const;
};

#endif