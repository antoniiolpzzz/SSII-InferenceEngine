//
// Created by Antonio López Toboso on 29/11/24.
//

#include "Fact.h"

Fact::Fact(const std::string &identifier, const double certaintyFactor) {
    this->identifier = identifier;
    this->certaintyFactor = certaintyFactor;
}

std::string Fact::getIdentifier() {
    return identifier;
}

double Fact::getCertaintyFactor() const {
    return certaintyFactor;
}

Fact::~Fact() {
    // Destructor
}