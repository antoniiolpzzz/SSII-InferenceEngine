//
// Created by Antonio López Toboso on 29/11/24.
//

#ifndef FACTBASE_H
#define FACTBASE_H

#include <cfloat>
#include <fstream>
#include <vector>
#include "Fact.h"

/*
 * The lower threshold of the certainty factor.
 * Used to set an out of range certainty factor.
 * The minimum value of a double.
 */
constexpr double CERTAINTY_FACTOR_MIN_THRESHOLD  = -DBL_MAX;

/*
 * The upper threshold of the certainty factor.
 * Used to set an out of range certainty factor.
 * The maximum value of a double.
 */
constexpr double CERTAINTY_FACTOR_MAX_THRESHOLD = DBL_MAX;

class FactBase {

    public:
        /*
         * Default constructor of the FactBase class.
         */
        FactBase() = default;

        /*
         * Destructor of the FactBase class.
         */
        ~FactBase() = default;

        /*
         * Constructor of the FactBase class.
         * @param inputFile the file containing the facts.
         */
        explicit FactBase(std::ifstream &inputFile);

        /*
         * Copy constructor of the FactBase class.
         * @param factBase the FactBase object to be copied.
         */
        FactBase(const FactBase &factBase);

        /*
         * Getter of the goal fact.
         * @param fact the fact to be compared with the fact in base.
         * @return the fact or a default out of range Fact.
         */
        Fact getFactFromBase(const Fact& fact) const;

        /*
         * Getter of a fact.
         * @param identifier the identifier of the fact to be returned.
         * @return the fact or a default out of range Fact.
         */
        Fact getFactFromBase(const std::string& identifier) const;

        /*
         * Getter of the goal fact.
         * @return the goal fact.
         */
        Fact getGoal();

        /*
         * Getter of the facts array.
         * @return the facts array.
         */
        std::vector<Fact> getFacts() const;

        /*
         * Getter of the number of facts.
         * @return the number of facts.
         */
        int getNumberOfFacts() const;

        /*
         * Method to add a fact to the fact base.
         * @param fact the fact to be added.
         */
        void addFact(const Fact& fact);

        /*
         * Method to print the facts of the fact base.
         * Used during the development of the expert system.
         */
        void toString() const;

    private:
        /*
         * The goal fact of the fact base.
         */
        Fact goal;

        /*
         * The array of facts of the fact base.
         */
        std::vector<Fact> facts;

        /*
         * The number of facts contained in the fact base.
         */
        int numberOfFacts;

};



#endif //FACTBASE_H
