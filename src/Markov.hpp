#ifndef H_MARKOV_INCLUDED
#define H_MARKOV_ICLUDED
#pragma once 

#include <string>
#include <map>
#include <vector>
#include <sstream>

#define START_TOKEN "^"
#define END_TOKEN "$"

namespace Markov {

//using SparseArray = std::map<std::string,int>;  // The int here is the probability from State i to State j 
using Ngram = std::vector<std::string>;
using NextState = std::string;
//using Pair = std::pair<Ngram,NextState>;

    struct Pair {
        Ngram currentState;
        NextState nextState;
    };

    struct Occurence{
        int occurence;

        Occurence(){
            occurence = 0;
        }

        void operator++(int i){
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

        std::map<Pair,Occurence> transitionMatrix; //

        int m_order; // The Order of the Markov Chain. 1-order , 2-order etc.

        Chain(int order): m_order(order){}; 

        /**
         * @brief Returns the transition probability between two states
         */

        auto transitionProbability(NextState ns, Ngram ngram) -> double;
        
        /**
         * @brief add a new String to the chain
         */

        auto add(std::string&& s) -> Ngram;

        /**
         * @brief Create a new pair according to the order
         */

        auto makePairs(std::vector<std::string>&& v,int order) -> std::vector<Pair>;

    };

    /**
     * Helper to split string into vector
     */
    auto split(std::string str,char delimiter) -> std::vector<std::string> {

        std::vector<std::string> internal;
        std::stringstream ss(str); // Turn the string into a stream.
        std::string tok;
        
        while(getline(ss, tok, delimiter)) {
            internal.push_back(tok);
        }
        
        return internal;
    }
    


};


#endif 