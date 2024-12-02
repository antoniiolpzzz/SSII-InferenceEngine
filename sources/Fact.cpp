//
// Created by Antonio López Toboso on 29/11/24.
//

#include "Fact.h"

Fact::Fact(const std::string &identifier, const double certaintyFactor) {
    this->identifier = identifier;
    this->certaintyFactor = certaintyFactor;
}

Fact::Fact(const std::string &identifier) {
    this->identifier = identifier;
    this->certaintyFactor = DEFAULT_RULE_CERTAINTY_FACTOR;
}


std::string Fact::getIdentifier() const {
    return identifier;
}

double Fact::getCertaintyFactor() const {
    return certaintyFactor;
}

void Fact::setCertaintyFactor(double certaintyFactor) {
    this->certaintyFactor = certaintyFactor;
}