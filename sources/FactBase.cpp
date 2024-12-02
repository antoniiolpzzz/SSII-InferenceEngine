//
// Created by Antonio López Toboso on 29/11/24.
//

#include "FactBase.h"

#include <iostream>
#include <regex>

//estructura del archivo de entrada
/*
6
A, FC=0.6
B, FC=0.4
D, FC=0.9
E, FC=0.7
F, FC=0.8
G, FC=-0.3
Objetivo
goalIdentifier
*/

FactBase::FactBase(std::ifstream &inputFile) {
    std::string line;
    std::string identifier;
    double certaintyFactor;

    int i = 0;
    while (std::getline(inputFile, line)) {
        if (i == 0) {
            this->numberOfFacts = std::stoi(line);
            this->facts.reserve(numberOfFacts);

        } else if (i <= numberOfFacts) {
            //std::regex pattern(R"((\w+), FC=(-?\d+\.\d+))");
            std::regex pattern(R"((\w+), FC=(-?\d+(\.\d+)?))");
            std::smatch matches;
            if (std::regex_search(line, matches, pattern)) {
                identifier = matches[1].str();
                certaintyFactor = std::stod(matches[2].str());

                this->facts.emplace_back(Fact(identifier, certaintyFactor));
            }
        } else if (i == numberOfFacts + 1) {
            std::getline(inputFile, line);
            std::smatch goalMatches;
            std::regex goalPattern(R"((\w+))");
            if (std::regex_search(line, goalMatches, goalPattern)) {
                identifier = goalMatches[1].str();
                this->goal = Fact(identifier, 0.0);
            }

        } else {
            break;
        }
        i++;
    }
}


FactBase::FactBase(const FactBase &factBase) {
    this->numberOfFacts = factBase.numberOfFacts;
    this->facts = factBase.facts;
    this->goal = factBase.goal;
}


Fact FactBase::getFactFromBase(const std::string &identifier) const {

    for (const auto &potentialFact : facts) {
        if (potentialFact.getIdentifier() == identifier) {
            return potentialFact;
        }
    }
    return Fact("", CERTAINTY_FACTOR_MIN_THRESHOLD);
}



Fact FactBase::getFactFromBase(const Fact& fact) const {

    for (const auto &potentialFact : facts) {
        if (potentialFact.getIdentifier() == fact.getIdentifier()) {
            return potentialFact;
        }
    }
    return Fact("", CERTAINTY_FACTOR_MIN_THRESHOLD);
}


Fact FactBase::getGoal() {
    return goal;
}


std::vector<Fact> FactBase::getFacts() const {
    return facts;
}


int FactBase::getNumberOfFacts() const {
    return numberOfFacts;
}


void FactBase::addFact(const Fact& fact) {

    facts.emplace_back(fact);
    numberOfFacts++;
}




void FactBase::toString() const {
    std::cout << "FactBase: " << std::endl;
    for (const auto &fact : facts) {
        std::cout << "Fact: " << fact.getIdentifier()
        << " | FC:" << fact.getCertaintyFactor() << std::endl;
    }
    std::cout << "Goal: " << goal.getIdentifier() << std::endl;
}


