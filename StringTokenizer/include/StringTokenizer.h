#ifndef STRINGTOKENIZER_H
#define STRINGTOKENIZER_H
#include <string>
#include <vector>

using namespace std;

namespace stringtoken
{

class CharSet
{
private:
    static const int BITS  = 8;
    static const int BYTES = 256 / BITS;
    char *data;
    int bit, loc;
public:
    CharSet();
    CharSet(const unsigned char *in);
    CharSet(const string &in);
    void clear();
    void add(const unsigned char &in);
    void add(const unsigned char *in);
    void add(const string &in);
    void add(const CharSet &in);
    void remove(const unsigned char &in);
    void remove(const unsigned char *in);
    void remove(const string &in);
    void remove(const CharSet &in);
    CharSet* setUnion(const CharSet &in);
    CharSet* intersection(const CharSet &in);
    CharSet* complement();
    bool contains(const unsigned char &in);
    bool isEmpty();
    virtual ~CharSet();
};


class StringTokenizer
{
private:
    StringTokenizer() {};
    CharSet delim;
    vector<string*> tokens;
    char *scratchpad;
    unsigned int position, size;
    unsigned char next;
    bool onTokens;
    bool keepQuotes;
    void readTokens(const string &in);
    void nextChar(const string &in);
    void addToken(const string &in);
    void readQuote(const string &in, char &qmark);
    void readEscape(const string &in);
public:
    StringTokenizer(const string &in, string  delim, bool keepQuotes = false);
    StringTokenizer(const string &in, char   *delim, bool keepQuotes = false);
    StringTokenizer(const string &in, CharSet delim, bool keepQuotes = false);
    int  countTokens();
    bool hasMoreTokens();
    void reset();
    string peek();
    string nextToken();
    string getToken(int index);
    virtual ~StringTokenizer();
};
}
#endif // STRINGTOKENIZER_H
