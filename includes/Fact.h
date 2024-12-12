//
// Created by Antonio López Toboso on 29/11/24.
//

#ifndef SSII_MOTORINFERENCIA_FACT_H
#define SSII_MOTORINFERENCIA_FACT_H

#include <string>

/**
 * The default certainty factor of a fact.
 * Used when the certainty factor is not provided.
 */
static const double DEFAULT_RULE_CERTAINTY_FACTOR = 0.0;

/**
 * The Fact class represents a fact of the expert system.
 */
class Fact {

    public:
        /**
         * Default constructor of the Fact class.
         */
        Fact() = default;

        /**
         * Destructor of the Fact class.
         */
        ~Fact() = default;

        /**
         * Constructor of the Fact class.
         * @param identifier the identifier of the fact.
         * @param certaintyFactor the certainty factor of the fact.
         */
        Fact(const std::string &identifier, double certaintyFactor);

        /**
         * Constructor of the Fact class.
         * Used to create a fact with a default certainty factor of 0.0.
         * @param identifier the identifier of the fact.
         */
        explicit Fact(const std::string &identifier);

        /**
         * Getter of the identifier of the fact.
         * @return the identifier of the fact.
         */
        std::string getIdentifier() const;

        /**
         * Getter of the certainty factor of the fact.
         * @return the certainty factor of the fact.
         */
        double getCertaintyFactor() const;

        /**
         * Setter of the certainty factor of the fact.
         * @param certaintyFactor the certainty factor of the fact.
         */
        void setCertaintyFactor(double certaintyFactor);

    private:
        /**
         * The identifier of the fact.
         */
        std::string identifier;

        /**
         * The certainty factor of the fact.
         */
        double certaintyFactor;

};


#endif //SSII_MOTORINFERENCIA_FACT_H
