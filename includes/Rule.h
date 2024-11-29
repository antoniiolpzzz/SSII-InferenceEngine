//
// Created by Antonio López Toboso on 29/11/24.
//

#ifndef SSII_MOTORINFERENCIA_RULE_H
#define SSII_MOTORINFERENCIA_RULE_H

#include <string>

class Rule {

    public:
        Rule(){}
        ~Rule();
        Rule(int identifier, double certaintyFactor, const std::string &antecedent, const std::string &consequent);
        int getIdentifier() const;
        double getCertaintyFactor() const;
        std::string getAntecedent();
        std::string getConsequent();


    private:
        int identifier;
        double certaintyFactor;
        std::string antecedent;
        std::string consequent;

    };


#endif //SSII_MOTORINFERENCIA_RULE_H
