//
// Created by Antonio López Toboso on 29/11/24.
//

#include <iostream>
#include <vector>

#include "Rule.h"
#include "Fact.h"
#include "FactBase.h"
#include "InferenceEngine.h"
#include "KnowledgeBase.h"
#include "Utils.h"

int main(int argc, char *argv[]) {

    if (argc >= 3) {

        for (int i = 2; i < argc; i++){

            std::filesystem::path path1(argv[1]);
            std::filesystem::path path2(argv[i]);

            std::cout << "Processing KnowledgeBase: " << path1.stem() << std::endl;
            std::cout << "Processing FactBase: " << path2.stem() << std::endl;
            std::cout << std::endl;

            std::string outputFileName;
            outputFileName = path1.stem().string() + "_" + path2.stem().string() + LOG_FILE_EXTENSION;

            std::ofstream outputFile(outputFileName);

            std::streambuf* coutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(outputFile.rdbuf());


            if (!outputFile) {
                std::cerr << "Error: No se ha podido abrir el fichero en el que se producirá la salida. " << std::endl
                          << "Compruebe que el fichero es accesible y en ultima instancia borre cualquier "
                          << "fichero con el siguiente nombre \"" << outputFileName << "\" en el directorio actual."
                          << std::endl;
                return 1;
            }


            std::ifstream inputFileBC;
            inputFileBC.open(argv[1], std::ifstream::in);
            std::ifstream inputFileBH;
            inputFileBH.open(argv[i], std::ifstream::in);



            KnowledgeBase knowledgeBase(inputFileBC);
            FactBase factBase(inputFileBH);
            InferenceEngine inferenceEngine(knowledgeBase, factBase);
            Fact goal = factBase.getGoal();

            printLogHeader(path1.stem(), path2.stem(), goal);

            inferenceEngine.backwardChaining(goal);

            printLogFooter(goal);

            outputFile.close();
            std::cout.rdbuf(coutBuffer);
        }

    } else {

        std::string binaryRelativePath = std::filesystem::path(argv[0]).filename().string();

            std::cerr << "Error: No se han proporcionado suficientes argumentos. "
                    << "Por favor, introduzca al menos dos ficheros de entrada." << std::endl
                    << "Siga la siguiente convencion: ./" << binaryRelativePath << " <ficheroBC> <ficheroBH1> ... <ficheroBHn>" << std::endl
                    << "Para n = numero de Bases de Hechos a procesar." << std::endl << std::endl
                    << "Para mas información consulte el manual de usuario. En caso de que el problema persista, contacte con el autor del programa." << std::endl;

            return 1;
    }

    return 0;

}
