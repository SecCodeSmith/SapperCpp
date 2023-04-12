#ifndef SAPPER_FIELD_H
#define SAPPER_FIELD_H
#include "SFML/Graphics.hpp"


enum class tags {
    none, discovered, flag, explosion
};

enum class fieldType {
    mine = -1 ,none = 0, one, two, three, four, five, six, seven, eight
};

class Field {
protected:
public:
    tags getTag() const;

    fieldType getType() const;

protected:
    tags tag;
    fieldType type;
public:
    void setTag(tags tag);
    void setType(fieldType type);
    void nextFieldType();
    void previousFieldType();
    Field();
    Field(tags tag, fieldType field);
    ~Field();
    Field& set(const Field& field);
    Field& set(tags tag, fieldType field);
    Field& operator=(const Field& field_);
};


#endif //SAPPER_FIELD_H
