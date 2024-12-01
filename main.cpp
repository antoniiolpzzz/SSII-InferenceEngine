//
// Created by Antonio López Toboso on 29/11/24.
//

#include <iostream>
#include <vector>

#include "Rule.h"
#include "Fact.h"
#include "FactBase.h"
#include "KnowledgeBase.h"

int main(int argc, char *argv[]) {

    /*
    std::cout << "Hello, World!" << std::endl;

    std::vector<Rule> rules;
    std::vector<Fact> facts;

    Rule rule1(1, 0.8, "A", "B");
    Rule rule2(2, 0.6, "B", "C");
    Rule rule3(3, 0.4, "C", "D");

    Fact fact1("A", 0.9);
    Fact fact2("B", 0.7);
    Fact fact3("C", 0.5);

    rules.push_back(rule1);
    rules.push_back(rule2);
    rules.push_back(rule3);

    facts.push_back(fact1);
    facts.push_back(fact2);
    facts.push_back(fact3);


    for (auto &rule : rules) {
        std::cout << "Rule: " << rule.getIdentifier()
        << " | FC:" << rule.getCertaintyFactor()
        << " | Ant:" << rule.getAntecedent()
        << " | Con:" << rule.getConsequent() << std::endl;
    }

    std::cout << std::endl;

    for (auto &fact : facts) {
        std::cout << "Fact: " << fact.getIdentifier()
        << " | FC:" << fact.getCertaintyFactor() << std::endl;
    }
    */

    if (argc >= 3) {
        std::ifstream inputFileBC;
        inputFileBC.open(argv[1], std::ifstream::in);
        std::ifstream inputFileBH;
        inputFileBH.open(argv[2], std::ifstream::in);

        //create knowledge base and fact base

        KnowledgeBase knowledgeBase(inputFileBC);
        FactBase factBase(inputFileBH);

        std::vector<Rule> rules = knowledgeBase.getRules();

        for (const auto &rule : rules) {
            std::cout << "Rule: " << rule.getIdentifier()
            << " | FC:" << rule.getCertaintyFactor()
            << " | Ant:" << rule.getAntecedent()
            << " | Con:" << rule.getConsequent() << std::endl;
        }

        for (const auto &fact : factBase.getFacts()) {
            std::cout << "Fact: " << fact.getIdentifier()
            << " | FC:" << fact.getCertaintyFactor() << std::endl;
        }
        std::cout << "Goal: " << factBase.getGoal().getIdentifier() << std::endl;

    }


    return 0;
}
