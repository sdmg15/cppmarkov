# cppmarkov

> A Markov chain is a mathematical system which keeps track of transitions between different states and tells you the probability of a transition occurring between two states.

This repository is an implementation in C++17 of that stochastic process. 

# Compiling and running the example 

## Requirements 

- CMake 3.10.2 or greater
- A C++ compiler (GCC or Clang etc. ) that supports C++17

## Compiling 

In order to compile just run 

```cmake

~ $ cmake --build . 

```

And the resulting binary will be in the `bin` folder.

## Code example 

```cpp

#include <iostream>
#include "Markov.hpp"

auto main() -> int {

Markov::Chain chain(1);

chain.add("I am sam");
chain.add("I am an Engineer");
chain.add("I like coding");

Markov::Ngram currentState = {"Engineer"};
Markov::NextState ns("$"); 

std::cout << chain.transitionProbability(ns,currentState) << "\n"; // Printing 1

return 1;
}

```

