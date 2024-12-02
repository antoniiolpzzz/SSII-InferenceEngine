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
            //antecedentsCertaintyFactors.push_back(currentGoalCertaintyFactor);
        }

        double antecedentsCertaintyFactor = this->resolveAntecedentsCombinedCertaintyFactor(currentRule);

        double singleRuleFactCertaintyFactor = resolveSingleRuleFactCertaintyFactor(currentRule, goal, antecedentsCertaintyFactor);
        rulesCertaintyFactors.push_back(singleRuleFactCertaintyFactor);

    }

    double multipleRuleFactCertaintyFactor = resolveMultipleRuleFactCertaintyFactor(goal, rulesCertaintyFactors);

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
    double ruleCertaintyFactor = rule.getCertaintyFactor();

    double singleRuleFactCertaintyFactor = ruleCertaintyFactor * std::max(0.0, antecedentsCertaintyFactors);

    //TODO: CHECK IF STD::MAX METHOS IS AVAILABLE ON EVA WINDOWS ENVIORNMENT

    return singleRuleFactCertaintyFactor;
}



double InferenceEngine::resolveMultipleRuleFactCertaintyFactor(const Fact &goal, std::vector<double>& rulesCertaintyFactors) {

    double multipleRuleFactCertaintyFactor;

    if (const unsigned int numberOfRules = rulesCertaintyFactors.size(); numberOfRules == 0) {
        //TODO: CHECK IF I NEED TO THROW AN EXCEPTION OR DO SOMETHING ELSE OR USE SOME VALUE
        //TODO: IM NOT SURE THIS VALUE BELONGS HERE
        multipleRuleFactCertaintyFactor = 0.0;

    } else if (numberOfRules == 1) {
        multipleRuleFactCertaintyFactor = rulesCertaintyFactors.back();


    } else {

        double firstRuleCertaintyFactor;
        double secondRuleCertaintyFactor;
        if (numberOfRules == 2) {
            firstRuleCertaintyFactor = rulesCertaintyFactors.back();
            rulesCertaintyFactors.pop_back();
            secondRuleCertaintyFactor = rulesCertaintyFactors.back();
            rulesCertaintyFactors.pop_back();

        } else {
            firstRuleCertaintyFactor = rulesCertaintyFactors.back();
            rulesCertaintyFactors.pop_back();

            secondRuleCertaintyFactor = resolveMultipleRuleFactCertaintyFactor(goal, rulesCertaintyFactors);
            rulesCertaintyFactors.clear();
        }

        if ( firstRuleCertaintyFactor >= 0 && secondRuleCertaintyFactor >= 0) {
            multipleRuleFactCertaintyFactor = firstRuleCertaintyFactor + secondRuleCertaintyFactor - (firstRuleCertaintyFactor * secondRuleCertaintyFactor);


        } else if (firstRuleCertaintyFactor <= 0 && secondRuleCertaintyFactor <= 0) {
            multipleRuleFactCertaintyFactor = firstRuleCertaintyFactor + secondRuleCertaintyFactor + (firstRuleCertaintyFactor * secondRuleCertaintyFactor);


        } else {
            multipleRuleFactCertaintyFactor = (firstRuleCertaintyFactor + secondRuleCertaintyFactor)
                                            / (1 - std::min(abs(firstRuleCertaintyFactor), abs(secondRuleCertaintyFactor)));

        }

    }
    return multipleRuleFactCertaintyFactor;
}



std::vector<Rule> InferenceEngine::obtainRulesWithGivenConsequent(const std::string &consequent) const {

    std::vector<Rule> rulesWithGivenConsequent;

    for (const auto &rule : this->knowledgeBase.getRules()) {
        if (rule.getConsequent() == consequent) {
            rulesWithGivenConsequent.push_back(rule);
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