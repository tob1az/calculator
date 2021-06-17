# Command line calculator

Requires a C++17 compliant compiler and CMake 3.10+. Should be cloned with submodules.

## Syntax

- expression ::= sum
- sum ::= product,  {('+'|'-'), product}
- product ::= power, {('*'|'/'), power}
- power ::= \['-'\], factor, {'^', factor}
- factor ::= number | '(', sum, ')'
- number ::= integer | floating point
- floating point ::= integer, '.', integer
- integer ::= digit, {digit}
- digit ::= '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'

## Unsupported features

- Numeric overflow handling
- NaN/Inf handling
- Whitespace symbols
- Variables
- Math functions
- Detailed error messages

## How to run

1. mkdir build && cd build
2. cmake ..
3. make -j
4. ./src/calculator "-1+(4-1)*-2^3"
