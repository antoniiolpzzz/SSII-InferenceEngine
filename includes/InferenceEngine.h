//
// Created by Antonio López Toboso on 30/11/24.
//

#ifndef INFERENCEENGINE_H
#define INFERENCEENGINE_H

#include "KnowledgeBase.h"
#include "FactBase.h"
#include "Fact.h"

//class to implement the inference engine
//using a backward chaining algorithm

//double backwardChaining(KnowledgeBase& knowledgeBase, FactBase& factBase, Fact& goal);
//std::vector<Rule> obtainRulesWithGivenConsequent(std::string consequent, KnowledgeBase& knowledgeBase);
//std::vector<std::string> obtainAntecedentsOfAGivenRule(const Rule& rule);


class InferenceEngine {

	//public:
    //	InferenceEngine();
    //	~InferenceEngine();
    //	double backwardChaining(KnowledgeBase& knowledgeBase, FactBase& factBase, Fact& goal);
	//	std::vector<Rule> obtainRulesWithGivenConsequent(std::string consequent, KnowledgeBase& knowledgeBase);
    //    std::vector<std::string> obtainAntecedentsOfAGivenRule(const Rule& rule);

	public:
		InferenceEngine(const KnowledgeBase& knowledgeBase, const FactBase& factBase);
		~InferenceEngine() = default;
		InferenceEngine(const InferenceEngine& inferenceEngine) = default;
		double backwardChaining(Fact& goal);


		//std::vector<std::string> obtainAntecedentsOfAGivenRule(const Rule& rule);


    private:
        KnowledgeBase knowledgeBase;
		FactBase factBase;

		std::vector<Rule> obtainRulesWithGivenConsequent(const std::string& consequent) const;
		double resolveAntecedentsCombinedCertaintyFactor(const Rule& rule) const;
		static double resolveSingleRuleFactCertaintyFactor(const Rule& rule, const Fact& goal, const double antecedentsCertaintyFactors);
		static double resolveMultipleRuleFactCertaintyFactor(const Fact& goal, std::vector<double>& rulesCertaintyFactors);
		static double abs(double value);




};



#endif //INFERENCEENGINE_H
