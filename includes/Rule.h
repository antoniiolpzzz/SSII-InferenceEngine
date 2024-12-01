//
// Created by Antonio López Toboso on 29/11/24.
//

#ifndef SSII_MOTORINFERENCIA_RULE_H
#define SSII_MOTORINFERENCIA_RULE_H

#include <list>
#include <string>

static const std::string CONJUNCTION = "y";
static const std::string DISJUNCTION = "o";
static const std::string ATOMIC = "";

class Rule {

    public:
        Rule() = default;
        ~Rule() = default;
        Rule(int identifier, double certaintyFactor, const std::string &antecedents, const std::string &consequent);
        int getIdentifier() const;
        double getCertaintyFactor() const;
        std::vector<std::string> getAntecedents() const;
        std::string getConsequent() const;
        std::string getRuleType() const;
        std::string getJoinedAntecedents() const;


    private:
        int identifier;
        double certaintyFactor;
        std::vector<std::string> antecedents;
        std::string consequent;
        std::string ruleType;

        void parseAntecedents(const std::string &antecedents);

    };


#endif //SSII_MOTORINFERENCIA_RULE_H
