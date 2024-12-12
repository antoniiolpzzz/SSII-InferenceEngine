//
// Created by Antonio López Toboso on 30/11/24.
//

#ifndef INFERENCEENGINE_H
#define INFERENCEENGINE_H

#include "KnowledgeBase.h"
#include "FactBase.h"
#include "Fact.h"


class InferenceEngine {

	public:
		/**
		 * Default constructor of the InferenceEngine class.
		 */
		InferenceEngine(const KnowledgeBase& knowledgeBase, const FactBase& factBase);

		/**
		 * Destructor of the InferenceEngine class.
		 */
		~InferenceEngine() = default;

		/**
		 * Copy constructor of the InferenceEngine class.
		 * @param inferenceEngine the InferenceEngine object to be copied.
		 */
		InferenceEngine(const InferenceEngine& inferenceEngine) = default;

		/**
		 * Main method of the inference engine.
		 * A backward chaining algorithm used to infer the certainty factor of a goal fact.
		 * Using the rules and facts of initialized on the class instantiation process.
		 * @param goal the fact to be inferred.
		 * @return certainty factor of the goal fact.
		 */
		double backwardChaining(Fact& goal);

    private:
		/**
		 * The knowledge base of the expert system.
		 */
		KnowledgeBase knowledgeBase;

		/**
		 * The fact base of the expert system.
		 */
		FactBase factBase;

		/**
		 * A string to store the current tabs used in each log stage.
		 */
		std::string tabs;

		/**
		 * Method to obtain the rules with a given consequent that are in the knowledge base.
		 * @param consequent the consequent of the rules to be obtained.
		 * @return the rules with the given consequent.
		 */
		std::vector<Rule> obtainRulesWithGivenConsequent(const std::string& consequent) const;

		/**
		 * Method to combine the certainty factors of the antecedents of a rule.
		 * @param rule the rule whose antecedents certainty factors are to be combined.
		 * @return the combined certainty factor of the antecedents of the given rule.
		 */
		double resolveAntecedentsCombinedCertaintyFactor(const Rule& rule) const;

		/**
		 * Method to obtain the partial certainty factor of the consequent of a rule.
		 * Concretely, the certainty factor produced by the application of the single rule.
		 * It uses the certainty factor of the antecedents of the rule and the certainty factor of the rule itself.
		 * @param rule the rule whose consequent certainty factor is to be obtained.
		 * @param goal the goal fact that is being inferred. Only used for debugging purposes.
		 * @param antecedentsCertaintyFactors the combined certainty factor of the antecedents of the rule.
		 * @return the partial certainty factor of the consequent of the given rule.
		 */
		double resolveSingleRuleFactCertaintyFactor(const Rule& rule, const Fact& goal, double antecedentsCertaintyFactors) const;

		/**
		 * Method to obtain the final combined certainty factor of the goal fact.
		 * Concretely, the certainty factor produced by the application of multiple rules.
		 * It uses the certainty factors produced by the rules that have the goal fact as consequent.
		 * @param goal the goal fact whose certainty factor is to be obtained.
		 * @param rulesCertaintyFactors the certainty factors produced by the rules that have the goal fact as consequent.
		 * @return the final certainty factor of the goal fact.
		 */
		double resolveMultipleRuleFactCertaintyFactor(const Fact& goal, std::vector<double>& rulesCertaintyFactors) const;

		/**
		 * Method to obtain the absolute value of a double.
		 * @param value the double whose absolute value is to be obtained.
		 * @return the absolute value of the given double.
		 */
		static double abs(double value);

		/**
		 * Method to increase the number of tabs used during the log process.
		 */
		void increaseTabs();

		/**
		 * Method to decrease the number of tabs used during the log process.
		 */
		void decreaseTabs();

};



#endif //INFERENCEENGINE_H
