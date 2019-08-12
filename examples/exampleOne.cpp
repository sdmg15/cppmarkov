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