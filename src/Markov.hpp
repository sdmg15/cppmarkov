#ifndef H_MARKOV_INCLUDED
#define H_MARKOV_ICLUDED
#pragma once 

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <random>
#include <algorithm>

#define START_TOKEN "^"
#define END_TOKEN "$"

namespace Markov {

//using SparseArray = std::map<std::string,int>;  // The int here is the probability from State i to State j 
using Ngram = std::vector<std::string>;
using NextState = std::string;
using Pair = std::pair<Ngram,NextState>;


    struct Occurence{
        int occurence;

        Occurence(){
            occurence = 1;
        }

        void operator++(){
            ++occurence;
        }

        void operator=(int i){
            occurence = i;
        }

         operator int (){
            return occurence;
        }
    };

    struct Chain {

        std::map<Pair,int> transitionMatrix; //
        std::map<int,Pair> ipMap_; // index pair Map
        bool computed_;
        int m_order; // The Order of the Markov Chain. 1-order , 2-order etc.
        std::vector<double> probabilities_;

        static int incr_;

        explicit Chain(int order) ;

        /**
         * @brief Returns the transition probability between two states
         */

        auto transitionProbability(const NextState& ns, const Ngram& ngram) -> double;
        
        /**
         * @brief add a new String to the chain
         */

        auto add(std::string&& s) -> void;

        /**
         * @brief Create a new pair according to the order
         */

        auto makePairs(std::vector<std::string>&& v,int order) -> std::vector<Pair>;
         
         /**
         * @brief Generates new text based on an initial seed
         */

        auto generateWord(int length) -> std::string;

        auto storeProbabilities() -> void ;
    };

    

    auto operator<(const Pair& lhs, const Pair& rhs) -> bool;

    /**
     * Helper to split string into vector
     */
    auto split(std::string str,char delimiter) -> std::vector<std::string>;

    /**
     * @brief take two Ngram and tell whether they're equal or not
     * @return bool
     */

    auto compare(const Ngram& lhs, const Ngram& rhs) -> bool;

    /**
     * @brief Join the Ngram vector into string
     */
    auto join(Ngram& n) -> std::string; 
}; // end namespace Markov


#endif 