#include "Markov.hpp"


Markov::Chain::Chain(int order): m_order(order){}

auto Markov::Chain::add(std::string&& str) -> void {
    // I am sam. I am an Engineer. I like Coding.
    
    auto startTokens = std::string(START_TOKEN, m_order);
    auto endTokens   = std::string(END_TOKEN,m_order);
    str = startTokens +" " +str +" " +endTokens;

    //Extract N-gram from the given string 
    auto strVec = Markov::split(str,' ');

    std::vector<Pair> pairs = makePairs( std::move(strVec), m_order ); 

    for(const auto& aPair : pairs ){

        if( transitionMatrix.count( aPair ) ) {
            transitionMatrix[aPair]++; 
        }else{
            transitionMatrix.insert( { aPair, 1 } ); 
        }
    }
}

auto Markov::Chain::makePairs(std::vector<std::string>&& strVec,int order) -> std::vector<Pair>{

    std::vector<Pair> pairList; 

    for(int i(1); i < strVec.size()-order;++i){
        
        Ngram currState; 
        NextState ns; 

        ns = strVec.at( i+order );

        for( int j(i); j< i+order; ++j){
            currState.push_back(strVec.at(j)); 
        }

        pairList.push_back( { currState,ns } );
    }

    return pairList;
}

auto Markov::Chain::transitionProbability(Markov::NextState ns, Markov::Ngram currentState) -> double {
    
    if( currentState.size() != m_order){
        throw 1;
    }
    
    int frequenceOfng{0}, sumOther{1};

    Pair pairToLookFor{currentState,ns};

    if( transitionMatrix.count( pairToLookFor ) ){

        frequenceOfng = transitionMatrix[ pairToLookFor ] ;
        // Divide by the currentState to any other.

        for(auto& [key,val] : transitionMatrix){

            if( compare(key.currentState,currentState) ){
                ++sumOther;
            }
        }
    }else{
        std::cout << "The transition was not found "<< pairToLookFor.currentState.back() << " " << pairToLookFor.nextState <<"\n";
        return 0;
    }

    return (frequenceOfng + 0.0)/(sumOther+0.0); 
}
