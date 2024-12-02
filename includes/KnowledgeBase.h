//
// Created by Antonio López Toboso on 29/11/24.
//

#ifndef KNOWLEDGEBASE_H
#define KNOWLEDGEBASE_H

#include <fstream>
#include "Rule.h"
#include <vector>

/**
 * The KnowledgeBase class represents the knowledge base of the expert system.
 */
class KnowledgeBase {

  public:
    /**
     * Default constructor of the KnowledgeBase class.
     */
    KnowledgeBase() = default;

    /**
     * Destructor of the KnowledgeBase class.
     */
    ~KnowledgeBase() = default;

    /**
     * Constructor of the KnowledgeBase class.
     * @param inputFile the file containing the rules.
     */
    KnowledgeBase(std::ifstream &inputFile);

    /**
     * Copy constructor of the KnowledgeBase class.
     * @param knowledgeBase the KnowledgeBase object to be copied.
     */
    KnowledgeBase(const KnowledgeBase &knowledgeBase);

    /**
     * Getter of the rules array.
     * @return the rules array.
     */
    std::vector<Rule> getRules() const;

    /**
     * Getter of the number of rules.
     * @return the number of rules.
     */
    int getNumberOfRules() const;

    /**
     * Method to print the rules of the knowledge base.
     */
    void toString() const;

    /*TODO: CHECK WHETHER I NEED A "TOSTRING" LIKE METHOD IN ORDER TO
     * ACCOMPLISH THE PRACTICE REQUIREMENTS OR IS NOT NECESSARY*/

  private:
    /**
     * The array of rules.
     */
    std::vector<Rule> rules;

    /**
     * The number of rules.
     */
    int numberOfRules;


};



#endif //KNOWLEDGEBASE_H
