#ifndef CHARSET_H
#define CHARSET_H
#include <string>

namespace stringtoken  {

class CharSet {
    private:
        static const int BYTES = 256 / 8;
        char *data;
        int bit, loc;
    public:
        CharSet();
        CharSet(const char *in);
        CharSet(const std::string &in);
        void add(const char &in);
        void add(const char *in);
        void add(const std::string &in);
        void add(const CharSet &in);
        void remove(const char &in);
        void remove(const char *in);
        void remove(const std::string &in);
        void remove(const CharSet &in);
        CharSet* setUnion(const CharSet &in);
        CharSet* intersection(const CharSet &in);
        CharSet* complement();
        bool contains(const char &in);
        virtual ~CharSet();
};
}
#endif // CHARSET_H
