//
// Created by Antonio López Toboso on 29/11/24.
//

#ifndef FACTBASE_H
#define FACTBASE_H

#include <cfloat>
#include <fstream>
#include <vector>
#include "Fact.h"


class FactBase {

    public:
        ~FactBase();
        explicit FactBase(std::ifstream &inputFile);
        FactBase(const FactBase &factBase);
        Fact isFactInBase(const Fact& fact) const;
        Fact getGoal() const;
        std::vector<Fact> getFacts() const;
        int getNumberOfFacts() const;
        void addFact(const Fact& fact);

        const double CERTAINTY_FACTOR_THRESHOLD = -DBL_MAX;

        void toString() const;

    /*TODO: CHECK WHETHER I NEED A "TOSTRING" LIKE METHOD IN ORDER TO
     * ACCOMPLISH THE PRACTICE REQUIREMENTS OR IS NOT NECESSARY*/

    private:
          Fact goal;
          std::vector<Fact> facts;
          int numberOfFacts;

};



#endif //FACTBASE_H
