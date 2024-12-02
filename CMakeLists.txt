cmake_minimum_required(VERSION 3.30)
project(SSII_MotorInferencia)

set(CMAKE_CXX_STANDARD 20)

include_directories(includes)

add_executable(SSII_MotorInferencia main.cpp
        sources/Fact.cpp includes/Fact.h
        sources/Rule.cpp includes/Rule.h
        sources/KnowledgeBase.cpp includes/KnowledgeBase.h
        sources/FactBase.cpp includes/FactBase.h
        sources/InferenceEngine.cpp includes/InferenceEngine.h
        )

# Generate windows executable
if (WIN32)
    set_target_properties(SSII_MotorInferencia PROPERTIES WIN32_EXECUTABLE TRUE)
endif()


