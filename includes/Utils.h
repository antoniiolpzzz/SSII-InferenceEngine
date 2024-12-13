//
// Created by Antonio López Toboso on 11/12/24.
//

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <filesystem>
#include "FactBase.h"

/**
 * The extension of the log files.
 */
#define LOG_FILE_EXTENSION ".log"

/**
 * The small separator string used in the log files.
 */
const std::string SMALL_SEPARATOR = "··································";
/**
 * The big separator string used in the log files.
 */
const std::string BIG_SEPARATOR = "======================================================================";

/**
 * Method to print the header of the log file.
 *
 * @param path1 the path of the knowledge base file.
 * @param path2 the path of the fact base file.
 * @param goal the goal fact.
 */
void printLogHeader(const std::string& path1, const std::string& path2, const Fact& goal);

/**
 * Method to print the footer of the log file.
 *
 * @param goal the goal fact.
 */
void printLogFooter(const Fact& goal);


/**
 * Method to get the stem of a path.
 *
 * @param path the path.
 * @return the stem of the path.
 */
std::string stem(const std::string& path);

#endif //UTILS_H