//
// Created by Antonio López Toboso on 29/11/24.
//

#ifndef SSII_MOTORINFERENCIA_FACT_H
#define SSII_MOTORINFERENCIA_FACT_H

#include <string>

class Fact {

    public:
        Fact() {}
        ~Fact();
        Fact(const std::string &identifier, double certaintyFactor);
        std::string getIdentifier();
        double getCertaintyFactor() const;

    private:
        std::string identifier;
        double certaintyFactor;

};


#endif //SSII_MOTORINFERENCIA_FACT_H
