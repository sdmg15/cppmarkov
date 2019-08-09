#include "Markov.hpp"


auto Markov::Chain::add(std::string&& str) -> Markov::Ngram {
    // I am sam. I am an Engineer. I like Coding.
    
    auto startTokens = std::string(START_TOKEN, m_order);
    auto endTokens   = std::string(END_TOKEN,m_order);
    auto str = startTokens + str + endTokens;

    // Extract N-gram from the given string 
    auto strVec = split(str,' ');

    std::vector<Pair> pairs = makePairs( std::move(strVec), m_order ); 
    
    for(const auto& aPair : pairs ){

        if( transitionMatrix.count( aPair ) == 1){
            transitionMatrix[aPair]++; 
        }else{
            transitionMatrix.insert( { aPair,Occurence() } ); 
        }
    }
}

auto Markov::Chain::makePairs(std::vector<std::string>&& strVec,int order) -> std::vector<Pair>{

    std::vector<Pair> pairList; 

    for(int i(0); i < strVec.size();++i){
        
        Ngram currState; 
        NextState ns; 

        for( int j(i); j< order; ++j){
            currState.push_back(strVec.at(j));
            ns = strVec.at( i );

            pairList.push_back( { currState,ns } ); 
        }
    }

    return pairList;
}

auto Markov::Chain::transitionProbability(Markov::NextState ns, Markov::Ngram currentState) -> double {
    
    if( currentState.size() != m_order){
        throw 1;
    }
    
    int frequenceOfng{0}, sumOther{0};

    if( transitionMatrix.count( {currentState,ns} ) == 1){

        frequenceOfng = transitionMatrix[ {currentState,ns} ] ; 
        // Divide by the currentState to any other.

        for(const auto& [key,val] : transitionMatrix){
            if( key.currentState == currentState){
                ++sumOther;
            }
        }
    }

    return frequenceOfng/sumOther; 
}