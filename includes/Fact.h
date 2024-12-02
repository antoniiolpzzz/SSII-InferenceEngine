//
// Created by Antonio López Toboso on 29/11/24.
//

#ifndef SSII_MOTORINFERENCIA_FACT_H
#define SSII_MOTORINFERENCIA_FACT_H

#include <string>

static const double DEFAULT_RULE_CERTAINTY_FACTOR = 0.0;

class Fact {

    public:
        Fact() = default;
        ~Fact() = default;
        Fact(const std::string &identifier, double certaintyFactor);
        explicit Fact(const std::string &identifier);
        std::string getIdentifier() const;
        double getCertaintyFactor() const;
        void setCertaintyFactor(double certaintyFactor);

    private:
        std::string identifier;
        double certaintyFactor;

};


#endif //SSII_MOTORINFERENCIA_FACT_H
