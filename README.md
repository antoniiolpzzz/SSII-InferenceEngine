# User Manual - SBR Inference Engine

## General Description
This inference engine implements a rule-based system (RBS) with backward chaining and certainty factors. The system is developed in C++ and allows processing knowledge bases and facts to infer conclusions.

## Requirements
- C++ compiler with support for C++17 or higher
- Git installed (if you need to clone the repository)
- Code::Blocks 20.3

## Repository Structure

```
├── includes/           # Header files (.h)
├── sources/            # Source files (.cpp)
└── main.cpp            # Program entry point
```

## Main Classes

### 1. Fact
Represents a fact with:
- Identifier
- Certainty factor

### 2. FactBase
Manages the fact base:
- Stores facts
- Allows querying and adding facts
- Handles the goal fact

### 3. Rule
Represents a rule with:
- Identifier
- Antecedents
- Consequent
- Certainty factor
- Rule type (AND/OR)

### 4. KnowledgeBase
Manages the knowledge base:
- Stores rules
- Allows querying rules

### 5. InferenceEngine
Implements the inference engine:
- Backward chaining algorithm
- Certainty factor calculation
- Conflict resolution

## Input File Format

### Knowledge Base (.bc)
```
<number_of_rules>
R1: If <antecedent> Then <consequent>, CF=<factor>
R2: If <antecedent1> and <antecedent2> Then <consequent>, CF=<factor>
R3: If <antecedent1> or <antecedent2> Then <consequent>, CF=<factor>
...
```

### Fact Base (.bh)
```
<number_of_facts>
<fact1>, CF=<factor>
<fact2>, CF=<factor>
...
Goal
<goal>
```

## Program Usage

### Compilation
Import the project into Code::Blocks 20.03 and compile it. By default, the compilation is configured to use the C++17 standard and static linking, since the GCC and Code::Blocks version provided by the EVA Windows environment has major linking and standard library access issues. Therefore, make sure the options `-std=c++17` and `-static` are enabled if they are not already.

### Execution
```bash
.\<executable_name> <knowledge_base> <fact_base1> [<fact_base2> ...]
```

### Output
The program generates .log files with:
- Record of the inference process
- Calculated certainty factors
- Final result for the goal

## Common Error Messages

1. "Invalid input file format"
   - Check the format of the .bc and .bh files

2. "Not enough arguments provided"
   - Make sure to provide at least one knowledge base and one fact base

## Usage Examples

```bash
# Process a fact base
".\SSII - InferenceEngine" example.bc example.bh

# Process multiple fact bases
".\SSII - InferenceEngine" example.bc example1.bh example2.bh
```

## Output Format

The system generates a structured output in .log files with the following format:

### 1. Header
```
··································
KNOWLEDGE BASE: "<KB_name>"
··································
FACT BASE: "<FB_name>"
··································
GOAL: <goal>
··································
```

### 2. Inference Process
For each rule triggered during the process, the following is shown:

```
======================================================================
<tabs>R<num> (Rule Triggered)
<tabs>    CASE 1 (if necessary): <antecedents>, CF=<factor>     # Antecedent evaluation
<tabs>    CASE 3: <consequent>, CF=<factor>                    # Rule application
<tabs>CASE 2 (if necessary): <consequent>, CF=<factor>         # Rule combination (if applicable)
======================================================================
```

Where:
- **CASE 1**: Shows the evaluation of the combined antecedents
  - For AND rules: shows antecedents joined by "and"
  - For OR rules: shows antecedents joined by "or"
  - CF = certainty factor resulting from the combination

- **CASE 2**: Appears when multiple rules are combined for the same consequent
  - Shows the final certainty factor after combining the rules

- **CASE 3**: Shows the result of applying an individual rule
  - CF = certainty factor calculated for the consequent

### 3. Final Result
```
RESULT OBTAINED IN THE INFERENCE PROCESS:

··································
<goal>, CF=<final_factor>
··································
```

The indentation (tabs) in the log indicates the depth in the inference tree, allowing you to visually follow the system's reasoning process.

Additionally, the depth assigns a downward hierarchy. This means that evaluations indented at the same level, which have an immediately following evaluation with a lower indentation, are required evaluations for that last one.

## Important Notes

- Certainty factors must be in the range [-1,1]
- Rules support "and"/"or" operators for multiple antecedents
- The system uses backward chaining from the goal
- Detailed .log files of the inference process are generated

## Support

To report problems or request help:
1. Open an issue in the repository
2. Include the input files and the error message
3. Describe the steps to reproduce the problem

