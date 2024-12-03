//
// Created by Antonio López Toboso on 30/11/24.
//

#include "InferenceEngine.h"



InferenceEngine::InferenceEngine(const KnowledgeBase &knowledgeBase, const FactBase &factBase) {
    this->knowledgeBase = knowledgeBase;
    this->factBase = factBase;
}



double InferenceEngine::backwardChaining(Fact &goal) {
    double currentCertaintyFactor = this->factBase.getFactFromBase(goal).getCertaintyFactor();

    if ( 1 <= currentCertaintyFactor && currentCertaintyFactor >= -1) {
        return currentCertaintyFactor;
    }

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
            this->factBase.addFact(currentGoal);
            //antecedentsCertaintyFactors.emplace_back(currentGoalCertaintyFactor);
        }

        double antecedentsCertaintyFactor = this->resolveAntecedentsCombinedCertaintyFactor(currentRule);

        double singleRuleFactCertaintyFactor = resolveSingleRuleFactCertaintyFactor(currentRule, goal, antecedentsCertaintyFactor);
        rulesCertaintyFactors.emplace_back(singleRuleFactCertaintyFactor);

    }

    const double multipleRuleFactCertaintyFactor = resolveMultipleRuleFactCertaintyFactor(goal, rulesCertaintyFactors);

    goal.setCertaintyFactor(multipleRuleFactCertaintyFactor);
    return multipleRuleFactCertaintyFactor;

}



double InferenceEngine::resolveAntecedentsCombinedCertaintyFactor(const Rule &rule) const {

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
        return antecedentsCombinedCertaintyFactor;


    } else if (ruleType == DISJUNCTION) {
        antecedentsCombinedCertaintyFactor = CERTAINTY_FACTOR_MIN_THRESHOLD;
        for (const auto &antecedent : rule.getAntecedents()) {

            double antecedentCertaintyFactor = this->factBase.getFactFromBase(antecedent).getCertaintyFactor();
            if (antecedentCertaintyFactor > antecedentsCombinedCertaintyFactor) {
                antecedentsCombinedCertaintyFactor = antecedentCertaintyFactor;
            }
        }
        return antecedentsCombinedCertaintyFactor;
    }

    //TODO: CHECK IF I NEED TO RETURN A VALUE IN CASE OF ERROR
    // AND IF I NEED TO THROW AN EXCEPTION OR DO SOMETHING ELSE
    return 0.0;
}



double InferenceEngine::resolveSingleRuleFactCertaintyFactor(const Rule &rule, const Fact &goal, const double antecedentsCertaintyFactors) {

    const double ruleCertaintyFactor = rule.getCertaintyFactor();
    return (ruleCertaintyFactor * std::max(0.0, antecedentsCertaintyFactors));
    //TODO: CHECK IF STD::MAX METHODS IS AVAILABLE ON EVA WINDOWS ENVIRONMENT

}



double InferenceEngine::resolveMultipleRuleFactCertaintyFactor(const Fact &goal, std::vector<double>& rulesCertaintyFactors) {

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
    }
    //TODO: CHECK WHETHER I NEED TO RETURN 0.0 OR ANOTHER VALUE
    return rulesCertaintyFactors.empty() ? 0.0 : rulesCertaintyFactors.back();
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