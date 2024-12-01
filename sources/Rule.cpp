//
// Created by Antonio López Toboso on 29/11/24.
//

#include "Rule.h"

#include <list>
#include <sstream>


Rule::Rule(const int identifier, const double certaintyFactor, const std::string &antecedents, const std::string &consequent) {
    this->identifier = identifier;
    this->certaintyFactor = certaintyFactor;
    this->parseAntecedents(antecedents);
    this->consequent = consequent;
}


int Rule::getIdentifier() const {
    return identifier;
}


double Rule::getCertaintyFactor() const {
    return certaintyFactor;
}


std::vector<std::string> Rule::getAntecedents() const {
    return antecedents;
}


std::string Rule::getConsequent() const {
    return consequent;
}


std::string Rule::getRuleType() const {
    return ruleType;
}


std::string Rule::getJoinedAntecedents() const {
    std::stringstream joinedAntecedents;
    auto it = antecedents.begin();
    if (it != antecedents.end()) {
        joinedAntecedents << *it;
        ++it;
    }
    for (; it != antecedents.end(); ++it) {
        joinedAntecedents << " " + this->ruleType + " " << *it;
    }
    return joinedAntecedents.str();
}


void Rule::parseAntecedents(const std::string &antecedents) {
    std::string currentToken;
    std::istringstream antecedentsStream(antecedents);
    this->ruleType = ATOMIC;

    //if (antecedents.find(" " + OR + " ") != std::string::npos) {
    //    this->ruleType = OR;
    //} else if (antecedents.find(" " + AND + " ") != std::string::npos) {
    //    this->ruleType = AND;
    //}

    while (std::getline(antecedentsStream, currentToken, ' ')) {

        if (currentToken != DISJUNCTION && currentToken != CONJUNCTION) {
            this->antecedents.push_back(currentToken);
        }else {
            this->ruleType = currentToken;
        }
    }
}
