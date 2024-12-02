//
// Created by Antonio López Toboso on 29/11/24.
//

#ifndef FACTBASE_H
#define FACTBASE_H

#include <cfloat>
#include <fstream>
#include <vector>
#include "Fact.h"

constexpr double CERTAINTY_FACTOR_MIN_THRESHOLD  = -DBL_MAX;
constexpr double CERTAINTY_FACTOR_MAX_THRESHOLD = DBL_MAX;

class FactBase {

    public:
        FactBase() = default;
        ~FactBase() = default;
        explicit FactBase(std::ifstream &inputFile);
        FactBase(const FactBase &factBase);
        Fact getFactFromBase(const Fact& fact) const;
        Fact getFactFromBase(const std::string& identifier) const;
        Fact getGoal();
        std::vector<Fact> getFacts() const;
        int getNumberOfFacts() const;
        void addFact(const Fact& fact);


        void toString() const;

    /*TODO: CHECK WHETHER I NEED A "TOSTRING" LIKE METHOD IN ORDER TO
     * ACCOMPLISH THE PRACTICE REQUIREMENTS OR IS NOT NECESSARY*/

    private:
          Fact goal;
          std::vector<Fact> facts;
          int numberOfFacts;

};



#endif //FACTBASE_H
