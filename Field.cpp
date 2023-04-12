#include "Field.h"

Field::Field() {
    this->tag = tags::none;
    this->type = fieldType::none;
}

Field::Field(tags tag, fieldType field) {
    this->set(tag, field);
}

Field::~Field() {
}

Field& Field::operator=(const Field &field) {
    this->set(field);
    return *this;
}

Field &Field::set(const Field &field) {
    this->tag = field.tag;
    this->type = field.type;
    return *this;
}

Field &Field::set(tags tag, fieldType field) {
    this->tag = tag;
    this->type = field;
    return *this;
}

tags Field::getTag() const {
    return tag;
}

fieldType Field::getType() const {
    return type;
}

void Field::setTag(tags tag) {
    this->tag = tag;
}

void Field::setType(fieldType type) {
    this->type = type;
}

void Field::nextFieldType() {
    switch (this->type) {
        case fieldType::none:
            this->type = fieldType::one;
            break;
        case fieldType::one:
            this->type = fieldType::two;
            break;
        case fieldType::two:
            this->type = fieldType::three;
            break;
        case fieldType::three:
            this->type = fieldType::four;
            break;
        case fieldType::four:
            this->type = fieldType::five;
            break;
        case fieldType::five:
            this->type = fieldType::six;
            break;
        case fieldType::six:
            this->type = fieldType::seven;
            break;
        case fieldType::seven:
            this->type = fieldType::eight;
        case fieldType::eight:
            this->type = fieldType::none;
            break;
        case fieldType::mine:
        default:
            break;
    }
}

void Field::previousFieldType() {
    switch (this->type) {
        case fieldType::none:
            this->type = fieldType::eight;
            break;
        case fieldType::one:
            this->type = fieldType::none;
            break;
        case fieldType::two:
            this->type = fieldType::one;
            break;
        case fieldType::three:
            this->type = fieldType::two;
            break;
        case fieldType::four:
            this->type = fieldType::three;
            break;
        case fieldType::five:
            this->type = fieldType::four;
            break;
        case fieldType::six:
            this->type = fieldType::five;
            break;
        case fieldType::seven:
            this->type = fieldType::six;
        case fieldType::eight:
            this->type = fieldType::seven;
            break;
        case fieldType::mine:
        default:
            break;
    }
}

