#include "StringTokenizer.h"
#include <cstring>
#include <iostream>

namespace stringtoken {

const CharSet StringTokenizer::QUOTES = CharSet('\"');

StringTokenizer::StringTokenizer(const string &in, string delim, bool keepQuotes) {
    this->delim = CharSet(delim);
    quotes = QUOTES;
    this->keepQuotes = keepQuotes;
	readTokens(in);
}


StringTokenizer::StringTokenizer(const string &in, char *delim, bool keepQuotes) {
    this->delim = CharSet(delim);
    quotes = QUOTES;
    this->keepQuotes = keepQuotes;
	readTokens(in);
}


StringTokenizer::StringTokenizer(const string &in, CharSet delim, bool keepQuotes) {
    this->delim = CharSet(delim);
    quotes = QUOTES;
    this->keepQuotes = keepQuotes;
	readTokens(in);
}

StringTokenizer::StringTokenizer(const string &in, string  delim,
                                 string  quotes, bool keepQuotes) {
    this->delim = CharSet(delim);
    this->quotes = CharSet(quotes);
    this->keepQuotes = keepQuotes;
	readTokens(in);
}


StringTokenizer::StringTokenizer(const string &in, char   *delim,
                                 char   *quotes, bool keepQuotes) {
    this->delim = CharSet(delim);
    this->quotes = CharSet(quotes);
    this->keepQuotes = keepQuotes;
	readTokens(in);
}


StringTokenizer::StringTokenizer(const string &in, CharSet delim,
                                 CharSet quotes, bool keepQuotes) {
    this->delim = CharSet(delim);
    this->quotes = quotes;
    this->keepQuotes = keepQuotes;
	readTokens(in);
}


StringTokenizer::StringTokenizer(const StringTokenizer& other) {
    scratchpad = new char[inSize];
    memcpy(scratchpad, other.scratchpad, inSize);
    memcpy(tokens, other.tokens, dataSize * sizeof(string*));
    delim = other.delim;
    quotes = other.quotes;
    tokens = other.tokens;
    scratchpad = other.scratchpad;
    position = other.position;
    size = other.size;
    token = other.token;
    dataSize = other.dataSize;
    numTokens = other.numTokens;
    next = other.next;
    inSize = other.inSize;
    onTokens = other.onTokens;
    keepQuotes = other.keepQuotes;
}


StringTokenizer& StringTokenizer::operator= (const StringTokenizer& other) {
    if (this != &other) {
        memcpy(scratchpad, other.scratchpad, inSize);
        memcpy(tokens, other.tokens, dataSize * sizeof(string*));
        delim = other.delim;
        quotes = other.quotes;
        tokens = other.tokens;
        scratchpad = other.scratchpad;
        position = other.position;
        size = other.size;
        token = other.token;
        dataSize = other.dataSize;
        numTokens = other.numTokens;
        next = other.next;
        inSize = other.inSize;
        onTokens = other.onTokens;
        keepQuotes = other.keepQuotes;
    }
    return *this;
}


StringTokenizer::~StringTokenizer() {
    for(unsigned int i = 0; i < numTokens; i++) {
        delete[] tokens[i];
    }
    delete[] tokens;
    delete[] scratchpad;
}


/**
 * Reads the line of text and turns it into tokens.
 */
void StringTokenizer::readTokens(const string &in) {
    inSize = in.size() + 1;
    dataSize = (inSize / 5) + 1;
    tokens = new string*[dataSize];
    scratchpad = new char[inSize];
    scratchpad[in.size()] = 0;
    position = size = next = 0;
    token = 0;
    while(position < in.size())
    {
        nextChar(in);
        if(delim.contains(next)) {
			if(onTokens) {
				addToken(in);
				onTokens = false;
				size = 0;
			}
        } else {
			onTokens = true;
			if(quotes.contains(next)) {
				readQuote(in, next);
			} else {
				scratchpad[size] = next;
				size++;
			}
        }
    }
    if(onTokens) {
		addToken(in);
		onTokens = false;
		size = 0;
	}
	numTokens = token;
	token = 0;
}


/**
 * Adds a token that has been found.
 */
inline void StringTokenizer::addToken(const string &in) {
    if(token >= dataSize) {
        dataSize = (dataSize * 3) / 2;
        string** bigger = new string*[dataSize];
        memcpy(bigger, tokens, numTokens * sizeof(string*));
        delete[] tokens;
        tokens = bigger;
    }
	tokens[token] = new string(scratchpad, size);
	token++;
}


/**
 * This will find the the next character, and process escape characters.
 */
void StringTokenizer::nextChar(const string &in) {
    next = in.at(position);
    if(next == '\\') {
		readEscape(in);
	}
	position++;
}


/**
 * This will read every thing from the until the basis character is
 * encountered again, ignoring all delimiters.  The basis should always
 * be the same character that started the quote section, which should
 * usually be either a single or double quote (" or '), with double
 * quotes preferred.
 *
 * Note that escape sequences are not read literally. but still treated as
 * escaped.
 *
 * Also not that the quotation character itself in not included; to used
 * these are part of a string its required to include and escaped version.
 */
void StringTokenizer::readQuote(const string &in, const unsigned char qmark) {
    onTokens = true;
	addToken(in);
	size = 0;
	if(keepQuotes) {
        scratchpad[size++] = qmark;
	}
	do {
		nextChar(in);
		scratchpad[size++] = next;
	} while((position < in.size()) && (next != qmark));
	if((!keepQuotes) && (next == qmark)) {
        size--;
	}
	addToken(in);
	position++;
	size = 0;
}



/**
 * This will change a two character escape sequence into the correct
 * character, allowing quotes (among other things) to be used.  Note
 * that this uses the standard backslash as and that an literal
 * backslash must thus be represented as a double backslash.
 */
void StringTokenizer::readEscape(const string &in) {
	do {
		onTokens = true;
		position++;
		if(position >= in.length()) return;
		next = in.at(position);
		switch(next) {
			case '"':
				scratchpad[size] = '"';
				break;
			case '\'':
				scratchpad[size] = '\'';
				break;
			case 'n':
				scratchpad[size] = '\n';
				break;
			case 'r':
				scratchpad[size] = '\r';
				break;
			case 't':
				scratchpad[size] = '\t';
				break;
			case 'f':
				scratchpad[size] = '\f';
				break;
			case 'b':
				scratchpad[size] = '\b';
				break;
			case '0':
				scratchpad[size] = '\0';
				break;
			case 's':
				scratchpad[size] = ' ';
				break;
			// Any character not otherwise defined will be preserved as-is;
			// this also automatically covers the use of double backslash.
			default:
				scratchpad[size] = next;
				break;
		}
		size++;
		position++;
		next = in.at(position);
	} while(next == '\\');
}


/**
 * Returns the number of tokens.
 */
unsigned int StringTokenizer::countTokens() {
    return numTokens;
}


/**
 * Returns whether or not there are more tokens
 */
bool StringTokenizer::hasMoreTokens() {
	return (token < numTokens);
}


/**
 * Returns the next available token.  If there are no more tokens it
 * will return null.
 */
string* StringTokenizer::nextToken() {
	if(hasMoreTokens()) {
		return tokens[token++];
	} else return tokens[numTokens - 1];
}


/**
 * Returns the next available token, but not advance.  If there are no more tokens it
 * will return null.
 */
string* StringTokenizer::peek() {
	if(hasMoreTokens()) {
		return tokens[token];
	} else return tokens[numTokens - 1];
}


/**
 * Resets the to the first token
 */
void StringTokenizer::reset() {
	token = 0;
}


/**
 * Gets the token at the given index.  If an index is out of range this
 * will return null.
 */
string* StringTokenizer::getToken(unsigned int index) {
	if(index >= 0 && index <numTokens) {
		return tokens[index];
	} else return tokens[0];
}


}
