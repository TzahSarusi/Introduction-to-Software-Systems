#ifndef FIELD_H
#define FIELD_H

#include "string.h"

class Field {
private:
    String patternValue;
protected:
    virtual bool match_value(String packet) const = 0;
public:
    Field(String patternValue);
    virtual ~Field();
    virtual bool set_value(String val) = 0;
    bool match(String packet);
};

#endif
#pragma once
