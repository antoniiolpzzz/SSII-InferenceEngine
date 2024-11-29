//
// Created by Antonio López Toboso on 29/11/24.
//

#include "Rule.h"


Rule::Rule(const int identifier, const double certaintyFactor, const std::string &antecedent, const std::string &consequent) {
    this->identifier = identifier;
    this->certaintyFactor = certaintyFactor;
    this->antecedent = antecedent;
    this->consequent = consequent;
}

int Rule::getIdentifier() const {
    return identifier;
}

double Rule::getCertaintyFactor() const {
    return certaintyFactor;
}

std::string Rule::getAntecedent() {
    return antecedent;
}

std::string Rule::getConsequent() {
    return consequent;
}

Rule::~Rule() {
    // Destructor
}


