//
// Created by Antonio López Toboso on 30/11/24.
//

#include "InferenceEngine.h"

#include <iostream>

#include "Utils.h"


InferenceEngine::InferenceEngine(const KnowledgeBase &knowledgeBase, const FactBase &factBase) {
    this->knowledgeBase = knowledgeBase;
    this->factBase = factBase;
    this->tabs = "";
}



double InferenceEngine::backwardChaining(Fact &goal) {
    double currentCertaintyFactor = this->factBase.getFactFromBase(goal).getCertaintyFactor();

    if ( 1 <= currentCertaintyFactor && currentCertaintyFactor >= -1) {
        return currentCertaintyFactor;
    }

    this->increaseTabs();

    std::vector<Rule> conflictSet = this->obtainRulesWithGivenConsequent(goal.getIdentifier());
    std::vector<double> rulesCertaintyFactors;
    //std::vector<double> antecedentsCertaintyFactors;

    while (!conflictSet.empty()) {
        Rule currentRule = conflictSet.back();
        conflictSet.pop_back();

        std::vector<std::string> newGoals = currentRule.getAntecedents();

        while (!newGoals.empty()) {
            Fact currentGoal = Fact(newGoals.back());
            newGoals.pop_back();
            double currentGoalCertaintyFactor = this->backwardChaining(currentGoal);
            currentGoal.setCertaintyFactor(currentGoalCertaintyFactor); //TEST THIS LINE
            //this->factBase.addFact(currentGoal);
            //antecedentsCertaintyFactors.emplace_back(currentGoalCertaintyFactor);
        }

        double antecedentsCertaintyFactor = this->resolveAntecedentsCombinedCertaintyFactor(currentRule);

        double singleRuleFactCertaintyFactor = resolveSingleRuleFactCertaintyFactor(currentRule, goal, antecedentsCertaintyFactor);
        rulesCertaintyFactors.emplace_back(singleRuleFactCertaintyFactor);

    }
    const double multipleRuleFactCertaintyFactor = resolveMultipleRuleFactCertaintyFactor(goal, rulesCertaintyFactors);

    this->decreaseTabs();
    goal.setCertaintyFactor(multipleRuleFactCertaintyFactor);
    this->factBase.addFact(goal);
    return multipleRuleFactCertaintyFactor;

}



double InferenceEngine::resolveAntecedentsCombinedCertaintyFactor(const Rule &rule) const {

    std::cout << BIG_SEPARATOR << std::endl;
    std::cout << this->tabs << "R" << rule.getIdentifier() << " (Regla Activada)" << std::endl;

    double antecedentsCombinedCertaintyFactor;
    std::string ruleType = rule.getRuleType();

    if (ruleType == ATOMIC) {
        const std::string antecedentIdentifier = rule.getAntecedents().back();
        antecedentsCombinedCertaintyFactor = this->factBase.getFactFromBase(antecedentIdentifier).getCertaintyFactor();
        return antecedentsCombinedCertaintyFactor;


        //TODO: CHECK IF I CAN USE STD::MAX AND MIN IN HERE, IN CASE EVA ENVIRONMENT SUPPORTS IT
    } else if (ruleType == CONJUNCTION) {
        antecedentsCombinedCertaintyFactor = CERTAINTY_FACTOR_MAX_THRESHOLD;
        for (const auto &antecedent : rule.getAntecedents()) {

            double antecedentCertaintyFactor = this->factBase.getFactFromBase(antecedent).getCertaintyFactor();
            if (antecedentCertaintyFactor < antecedentsCombinedCertaintyFactor) {
                antecedentsCombinedCertaintyFactor = antecedentCertaintyFactor;
            }
        }

        std::vector<std::string> antecedents = rule.getAntecedents();
        std::cout << this->tabs << "\tCASO 1: ";
        for (int i=0; i< antecedents.size(); i++) {
            std::cout << antecedents[i];
            if (i != antecedents.size() - 1) {
                std::cout << " y ";
            }
        }
        std::cout << ", FC=" << antecedentsCombinedCertaintyFactor << std::endl;
        return antecedentsCombinedCertaintyFactor;


    } else if (ruleType == DISJUNCTION) {
        antecedentsCombinedCertaintyFactor = CERTAINTY_FACTOR_MIN_THRESHOLD;
        for (const auto &antecedent : rule.getAntecedents()) {

            double antecedentCertaintyFactor = this->factBase.getFactFromBase(antecedent).getCertaintyFactor();
            if (antecedentCertaintyFactor > antecedentsCombinedCertaintyFactor) {
                antecedentsCombinedCertaintyFactor = antecedentCertaintyFactor;
            }
        }

        std::vector<std::string> antecedents = rule.getAntecedents();
        std::cout << this->tabs << "\tCASO 1: ";
        for (int i=0; i< antecedents.size(); i++) {
            std::cout << antecedents[i];
            if (i != antecedents.size() - 1) {
                std::cout << " o ";
            }
        }
        std::cout << ", FC=" << antecedentsCombinedCertaintyFactor << std::endl;

        return antecedentsCombinedCertaintyFactor;
    }

    //TODO: CHECK IF I NEED TO RETURN A VALUE IN CASE OF ERROR
    // AND IF I NEED TO THROW AN EXCEPTION OR DO SOMETHING ELSE
    return DEFAULT_RULE_CERTAINTY_FACTOR;
}



double InferenceEngine::resolveSingleRuleFactCertaintyFactor(const Rule &rule, const Fact &goal, double antecedentsCertaintyFactors) const {

    const double ruleCertaintyFactor = rule.getCertaintyFactor();
    const double resolvedCertaintyFactor = (ruleCertaintyFactor * std::max(DEFAULT_RULE_CERTAINTY_FACTOR, antecedentsCertaintyFactors)) + 0.0;

    std::cout << this->tabs << "\tCASO 3: " << rule.getConsequent() << ", FC=" << resolvedCertaintyFactor << std::endl;

    return resolvedCertaintyFactor;

    //TODO: SUM 0.0 TO AVOID NEGATIVE 0 VALUES
    //TODO: CHECK IF STD::MAX METHODS IS AVAILABLE ON EVA WINDOWS ENVIRONMENT

}



double InferenceEngine::resolveMultipleRuleFactCertaintyFactor(const Fact &goal, std::vector<double>& rulesCertaintyFactors) const {

    bool needToPrint = false;
    while (rulesCertaintyFactors.size() > 1) {
        double firstRuleCertaintyFactor = rulesCertaintyFactors.back();
        rulesCertaintyFactors.pop_back();
        double secondRuleCertaintyFactor = rulesCertaintyFactors.back();
        rulesCertaintyFactors.pop_back();

        double multipleRuleCertaintyFactor;
        if (firstRuleCertaintyFactor >= 0 && secondRuleCertaintyFactor >= 0) {
            multipleRuleCertaintyFactor = firstRuleCertaintyFactor + secondRuleCertaintyFactor - (firstRuleCertaintyFactor * secondRuleCertaintyFactor);
        } else if (firstRuleCertaintyFactor <= 0 && secondRuleCertaintyFactor <= 0) {
            multipleRuleCertaintyFactor = firstRuleCertaintyFactor + secondRuleCertaintyFactor + (firstRuleCertaintyFactor * secondRuleCertaintyFactor);
        } else {
            multipleRuleCertaintyFactor = (firstRuleCertaintyFactor + secondRuleCertaintyFactor) / (1 - std::min(abs(firstRuleCertaintyFactor), abs(secondRuleCertaintyFactor)));
        }

        rulesCertaintyFactors.emplace_back(multipleRuleCertaintyFactor);
        needToPrint = true;
    }

    double factCertaintyFactor = rulesCertaintyFactors.empty() ? DEFAULT_RULE_CERTAINTY_FACTOR : rulesCertaintyFactors.back();

    if (needToPrint) {
        std::cout << this->tabs << "CASO 2: " << goal.getIdentifier() << ", FC=" << factCertaintyFactor << std::endl;
        //TODO: CHECK WHETHER I NEED TO RETURN 0.0 OR ANOTHER VALUE
        // THIS IS THE CASE IN WHICH NO RULE HAS THE GOAL AS CONSEQUENT
        // SO I NEED TO DETERMINE WHETHER NO HAVING THE GOAL IN THE FACTBASE NOR
        // HAVING ANY RULE WITH THE GOAL AS CONSEQUENT MEANS THAT THE CERTAINTY FACTOR
        // OF THE GOAL IS 0.0 (WE DONT KNOW ANYTHING ABOUT IT) OR -1.0 (WE KNOW FOR SURE
        // THAT THE GOAL IS NOT GONNA TAKE PLACE)
    }

    return factCertaintyFactor;
}



std::vector<Rule> InferenceEngine::obtainRulesWithGivenConsequent(const std::string &consequent) const {

    std::vector<Rule> rulesWithGivenConsequent;

    for (const auto &rule : this->knowledgeBase.getRules()) {
        if (rule.getConsequent() == consequent) {
            rulesWithGivenConsequent.emplace_back(rule);
        }
    }
    return rulesWithGivenConsequent;
}



double InferenceEngine::abs(const double value) {
    if (value < 0.0) {
        return -value;
    } else {
        return value;
    }
}

void InferenceEngine::increaseTabs() {
    this->tabs += "\t\t";
}

void InferenceEngine::decreaseTabs() {
    this->tabs.pop_back();
    this->tabs.pop_back();
}