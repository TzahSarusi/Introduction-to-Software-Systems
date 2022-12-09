#include <iostream>
#include "ip.h"
#include "port.h"
#include "field.h"
#define EMPTY_SIZE -1

Field::Field(String patternValue) { this->patternValue = patternValue; }

Field::~Field() { }


bool Field::match(String packet) 
{
    //A string are the fields within the packets
    String* firstString = NULL;
    size_t firstString_Size = 0;
    //B string are one field each time
    String* currentField = NULL;
    size_t currentField_Size = 0;
    packet.split(",", &firstString, &firstString_Size);

    //if empty packet
    if ((signed int)firstString_Size == EMPTY_SIZE) 
    {
        delete[] firstString;
        delete[] currentField;
        return false;
    }

    //search within packet for "match"
    for (int i = 0; i < (int)firstString_Size; i++) 
    {
        (firstString[i]).split("=", &currentField, &currentField_Size);
        if (currentField_Size <= 1) {
            delete[] currentField;
            currentField = NULL;
            continue;
        }
        currentField[0] = currentField[0].trim();
        currentField[1] = currentField[1].trim();
        if (patternValue.equals(currentField[0])) {
            if (match_value(currentField[1])) {
                delete[] firstString;
                delete[] currentField;
                return true;
            }
        }
        delete[] currentField;
    }
    delete[] firstString;
    return false;
}
