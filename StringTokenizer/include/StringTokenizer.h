#ifndef STRINGTOKENIZER_H
#define STRINGTOKENIZER_H
#include <string>
#include <vector>

using namespace std;

namespace stringtoken {

class CharSet {
private:
    static const int BITS  = 8;
    static const int BYTES = 256 / BITS;
    char *data;
    int bit, loc;
public:
    CharSet();
    CharSet(const unsigned char &in);
    CharSet(const unsigned char *in);
    CharSet(const std::string &in);
    CharSet(const CharSet& other);
    CharSet& operator= (const CharSet& other);
    void clear();
    void add(const unsigned char &in);
    void add(const unsigned char *in);
    void add(const std::string &in);
    void add(const CharSet &in);
    void remove(const unsigned char &in);
    void remove(const unsigned char *in);
    void remove(const string &in);
    void remove(const CharSet &in);
    CharSet setUnion(const CharSet &in);
    CharSet intersection(const CharSet &in);
    CharSet complement();
    bool contains(const unsigned char &in);
    bool isEmpty();
    virtual ~CharSet();
};


class StringTokenizer {
private:
    static const CharSet QUOTES;
    StringTokenizer() {};
    CharSet delim;
    CharSet quotes;
    std::string** tokens;
    char *scratchpad;
    unsigned int position, size, token, inSize, numTokens, dataSize;
    unsigned char next;
    bool onTokens;
    bool keepQuotes;
    void readTokens(const std::string &in);
    void nextChar(const std::string &in);
    void addToken(const std::string &in);
    void readQuote(const std::string &in, const unsigned char qmark);
    void readEscape(const std::string &in);
public:
    StringTokenizer(const std::string &in, std::string  delim, bool keepQuotes = false);
    StringTokenizer(const std::string &in, char   *delim, bool keepQuotes = false);
    StringTokenizer(const std::string &in, CharSet delim, bool keepQuotes = false);
    StringTokenizer(const std::string &in, std::string  delim, std::string  quotes, bool keepQuotes = false);
    StringTokenizer(const std::string &in, char   *delim, char   *quotes, bool keepQuotes = false);
    StringTokenizer(const string &in, CharSet delim, CharSet quotes, bool keepQuotes = false);
    StringTokenizer(const StringTokenizer& other);
    StringTokenizer& operator= (const StringTokenizer& other);
    unsigned int  countTokens();
    bool hasMoreTokens();
    void reset();
    std::string* peek();
    std::string* nextToken();
    std::string* getToken(unsigned int index);
    virtual ~StringTokenizer();
};
}
#endif // STRINGTOKENIZER_H
