//
// Created by Antonio López Toboso on 29/11/24.
//

#ifndef SSII_MOTORINFERENCIA_RULE_H
#define SSII_MOTORINFERENCIA_RULE_H

#include <list>
#include <string>

/**
 * The conjunction, disjunction and empty operators.
 */
static const std::string CONJUNCTION = "y";
static const std::string DISJUNCTION = "o";
static const std::string ATOMIC = "";

/**
 * The Rule class represents a rule of the expert system.
 */
class Rule {

    public:
        /**
         * Default constructor of the Rule class.
         */
        Rule() = default;

        /**
         * Destructor of the Rule class.
         */
        ~Rule() = default;

        /**
         * Constructor of the Rule class.
         * @param identifier the identifier of the rule.
         * @param certaintyFactor the certainty factor of the rule.
         * @param antecedents the antecedents of the rule.
         * @param consequent the consequent of the rule.
         */
        Rule(int identifier, double certaintyFactor, const std::string &antecedents, const std::string &consequent);

        /**
         * Getter of the identifier of the rule.
         * @return the identifier of the rule.
         */
        int getIdentifier() const;

        /**
         * Getter of the certainty factor of the rule.
         * @return the certainty factor of the rule.
         */
        double getCertaintyFactor() const;

        /**
         * Getter of the antecedents of the rule.
         * @return the antecedents of the rule.
         */
        std::vector<std::string> getAntecedents() const;

        /**
         * Getter of the consequent of the rule.
         * @return the consequent of the rule.
         */
        std::string getConsequent() const;

        /**
         * Getter of the rule type.
         * @return the rule type.
         */
        std::string getRuleType() const;

        /**
         * Method to print the rule.
         * Used during the log process of the expert system.
         */
        std::string getJoinedAntecedents() const;


    private:
        /**
         * The identifier of the rule.
         */
        int identifier;

        /**
         * The certainty factor of the rule.
         */
        double certaintyFactor;

        /**
         * The antecedents of the rule.
         */
        std::vector<std::string> antecedents;

        /**
         * The consequent of the rule.
         */
        std::string consequent;

        /**
         * The type of the rule.
         */
        std::string ruleType;

        /**
         * Method to parse the antecedents of the rule.
         * @param antecedents the antecedents of the rule.
         */
        void parseAntecedents(const std::string &antecedents);

    };


#endif //SSII_MOTORINFERENCIA_RULE_H
