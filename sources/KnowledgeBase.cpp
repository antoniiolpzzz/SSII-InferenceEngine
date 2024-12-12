//
// Created by Antonio López Toboso on 29/11/24.
//

#include "KnowledgeBase.h"

#include <iostream>
#include <regex>
#include <sstream>


KnowledgeBase::KnowledgeBase(std::ifstream &inputFile) {
    std::string line;
    std::string identifier;
    double certaintyFactor;
    std::string antecedent;
    std::string consequent;

    int i = 0;
    while (std::getline(inputFile, line)) {
        if (i == 0) {
            this->numberOfRules = std::stoi(line);
            this->rules.reserve(numberOfRules);
        } else if (i <= numberOfRules) {
            //std::regex pattern(R"(R(\d+): Si (.+) Entonces (.+), FC=(\d+\.\d+))");
            std::regex pattern(R"(R(\d+): Si (.+) Entonces (.+), FC=(-?\d+(\.\d+)?))");
            std::smatch matches;
            if (std::regex_search(line, matches, pattern)) {
                identifier = matches[1].str();
                antecedent = matches[2].str();
                consequent = matches[3].str();
                certaintyFactor = std::stod(matches[4].str());

                this->rules.emplace_back(std::stoi(identifier), certaintyFactor, antecedent, consequent);
            }
            else {
                std::string throwMessage = "Formato de la Base de Conocimientos de entrada inválido, en la regla numero "
                                                            + std::to_string(i)
                                                            + ". Verifique el formato del archivo de entrada.";

                std::cerr << throwMessage << std::endl;
                std::exit(EXIT_FAILURE);
            }

        } else {
            break;
        }
        i++;
    }
}


KnowledgeBase::KnowledgeBase(const KnowledgeBase &knowledgeBase) {
    this->numberOfRules = knowledgeBase.numberOfRules;
    this->rules = knowledgeBase.rules;
}


std::vector<Rule> KnowledgeBase::getRules() const {
    return rules;
}


int KnowledgeBase::getNumberOfRules() const {
    return numberOfRules;
}

void KnowledgeBase::toString() const {
    std::cout << "KnowledgeBase: " << std::endl;

    for (const auto &rule : rules) {
        std::cout << "Rule: " << rule.getIdentifier()
                  << " | FC:" << rule.getCertaintyFactor()
                  << " | Ant:" << rule.getJoinedAntecedents()
                  << " | Con:" << rule.getConsequent() << std::endl;
    }
}
