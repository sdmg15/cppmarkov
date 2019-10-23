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
            ipMap_.insert( {incr_++, aPair} ); 
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

auto Markov::Chain::transitionProbability(const Markov::NextState& ns, const Markov::Ngram& currentState) -> double {
    
    if( currentState.size() != m_order){
        throw 1;
    }
    
    int frequenceOfng{0}, sumOther{0};

    Pair pairToLookFor{ currentState,ns };

    if( transitionMatrix.count( pairToLookFor ) ){

        frequenceOfng = transitionMatrix[ pairToLookFor ] ;
        // Divide by the currentState to any other.

        for(auto& [key,val] : transitionMatrix){

            if( compare(key.first,currentState) ){
                sumOther += val; 
            }
        }

    }else{
        std::cout << "The transition was not found "<< pairToLookFor.first.back() << " " << pairToLookFor.second <<"\n";
        return -1;
    }

    return static_cast<double>(frequenceOfng) / static_cast<double>(sumOther); 
}


auto Markov::Chain::storeProbabilities() -> void {
    
    if( ! computed_ ){
        for(const auto& [k,v] : transitionMatrix) {
            auto prob = transitionProbability(k.second,k.first);
            probabilities_.push_back( prob );
        }
        computed_ = true;
    }
    return;
}

auto Markov::Chain::generateWord(int length) -> std::string {    
    
    this->storeProbabilities();

    std::vector<double> v;
    std::random_device rd;
    std::mt19937 gen(rd());

    for(double& c : probabilities_ ) {
        v.push_back( c*100 );
    }

    std::discrete_distribution<> dist( v.begin(), v.end());

    std::string res;

    for(int n=0; n<length; ++n) {
        auto r = ipMap_[dist(gen)]; 

        auto s = std::string(r.second.c_str()) ;

        if( "$" != s ){
            res+=s;
        }
        if( "$" != r.first.front()){
            res += " " + r.first.front() + " ";
        }
    }

    return res;
}

auto Markov::split(std::string str,char delimiter ) -> std::vector<std::string>{

    std::vector<std::string> internal;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tok;
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
}

auto Markov::compare(const Markov::Ngram& lhs,const Markov::Ngram& rhs) -> bool {
    bool areOfEqualWord = true;

    if( lhs.size() != rhs.size() ) {
        return false;   
    }

    for(int i(0); i< rhs.size() ; ++i){
        if( lhs.at(i) != rhs.at(i) ) {
            areOfEqualWord = false;
            break;
        }
    }

    return areOfEqualWord;
}

auto Markov::join(Markov::Ngram& ngram) -> std::string {

    std::string res;

    for(auto& str: ngram){
        res+=str +" ";
    }
    return res;
}

int Markov::Chain::incr_{0};
