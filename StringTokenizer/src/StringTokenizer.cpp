#include "StringTokenizer.h"

namespace stringtoken
{

const CharSet StringTokenizer::QUOTES = CharSet('\"');

StringTokenizer::StringTokenizer(const string &in, string delim, bool keepQuotes) {
    this->delim = CharSet(delim);
    // FIXME: There must be a better way than either copying every time is standard
    // or dynamically allocating ever times it not.  For now, this...
    quotes = QUOTES;
	readTokens(in);
}


StringTokenizer::StringTokenizer(const string &in, char *delim, bool keepQuotes) {
    this->delim = CharSet(delim);
    // FIXME: There must be a better way than either copying every time is standard
    // or dynamically allocating ever times it not.  For now, this...
    quotes = QUOTES;
	readTokens(in);
}


StringTokenizer::StringTokenizer(const string &in, CharSet delim, bool keepQuotes) {
    this->delim = CharSet(delim);
    // FIXME: There must be a better way than either copying every time is standard
    // or dynamically allocating ever times it not.  For now, this...
    quotes = QUOTES;
	readTokens(in);
}

StringTokenizer::StringTokenizer(const string &in, string  delim,
                                 string  quotes, bool keepQuotes) {
    this->delim = CharSet(delim);
    // FIXME: There must be a better way than either copying every time is standard
    // or dynamically allocating ever times it not.  For now, this...
    this->quotes = CharSet(quotes);
	readTokens(in);
}


StringTokenizer::StringTokenizer(const string &in, char   *delim,
                                 char   *quotes, bool keepQuotes) {
    this->delim = CharSet(delim);
    // FIXME: There must be a better way than either copying every time is standard
    // or dynamically allocating ever times it not.  For now, this...
    this->quotes = CharSet(quotes);
	readTokens(in);
}


StringTokenizer::StringTokenizer(const string &in, CharSet delim,
                                 CharSet quotes, bool keepQuotes) {
    this->delim = CharSet(delim);
    // FIXME: There must be a better way than either copying every time is standard
    // or dynamically allocating ever times it not.  For now, this...
    this->quotes = quotes;
	readTokens(in);
}


StringTokenizer::~StringTokenizer()
{
    delete scratchpad;
}


/**
 * Reads the line of text and turns it into tokens.
 */
void StringTokenizer::readTokens(const string &in)
{
    tokens = vector<string*>((in.size() / 5) + 1);
    scratchpad = new char[in.size() + 1];
    scratchpad[in.size()] = 0;
    position = size = next = 0;
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
	//token = 0;
}


/**
 * Adds a token that has been found.
 */
inline void StringTokenizer::addToken(const string &in) {
	tokens.push_back(new string(scratchpad, size));
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
 * encountered again, ignoring all delimeters.  The basis should always
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
void StringTokenizer::readQuote(const string &in, unsigned char &qmark) {
	onTokens = true;
	if(!keepQuotes)nextChar(in);
	while((position < in.size()) && (next != qmark)) {
		scratchpad[size] = next;
		size++;
		nextChar(in);
	}
	if(keepQuotes && (next == qmark)) {
        scratchpad[size++] = next;
	}
}



/**
 * This will change a two character escape sequence into the correct
 * chracter, allowing quotes (among other things) to be used.  Note
 * that this uses the standered backslash as and that an literal
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


}
