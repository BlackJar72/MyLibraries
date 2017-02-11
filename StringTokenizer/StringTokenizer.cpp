#include "StringTokenizer.h"

namespace stringtoken {

StringTokenizer::StringTokenizer(const string &in, string delim, bool keepQuotes) {
    //TODO: Everything!!!
}


StringTokenizer::StringTokenizer(const string &in, char *delim, bool keepQuotes) {
    //TODO: Everything!!!
}


StringTokenizer::StringTokenizer(const string &in, CharSet delim, bool keepQuotes) {
    //TODO: Everything!!!
}


StringTokenizer::~StringTokenizer() {
    delete scratchpad;
}


void StringTokenizer::readTokens(const string &in) {
    tokens = vector<string*>((in.size() / 5) + 1);
    scratchpad = new char[in.size() + 1];
    scratchpad[in.size()] = 0;
    position = size = next = 0;
    while(position < in.size()) {
        nextChar(in);
        if(delim.contains(next)) {

        } else {


        }
    }
}


}

