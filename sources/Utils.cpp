//
// Created by Antonio López Toboso on 11/12/24.
//

#include "Utils.h"

#include "InferenceEngine.h"

void printLogHeader(const std::filesystem::path &path1, const std::filesystem::path& path2, const Fact& goal){

    std::cout<< SMALL_SEPARATOR << std::endl;
    std::cout << "BASE DE CONOCIMIENTOS: " << path1.stem() << std::endl;
    std::cout << SMALL_SEPARATOR << std::endl;
    std::cout << "BASE DE HECHOS: " << path2.stem() << std::endl;
    std::cout << SMALL_SEPARATOR << std::endl;
    std::cout << "OBJETIVO: " << goal.getIdentifier()  << std::endl;
    std::cout << SMALL_SEPARATOR << std::endl;
    std::cout << std::endl << "LOG PRODUCIDO EN EL PROCESO DE INFERENCIA:" << std::endl << std::endl;

}

void printLogFooter(const Fact& goal){

    std::cout << BIG_SEPARATOR << std::endl;
    std::cout << std::endl << "RESULTADO OBTENIDO EN EL PROCESO DE INFERENCIA:" << std::endl;
    std::cout << std::endl << SMALL_SEPARATOR << std::endl;

    std::cout << goal.getIdentifier() << ", FC=" << goal.getCertaintyFactor() << std::endl;
    std::cout << SMALL_SEPARATOR << std::endl;

}