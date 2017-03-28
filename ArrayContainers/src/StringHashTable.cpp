 #include "ArrayContainers.h"
 #include <cstring>
 #include <string>

using namespace std;
namespace ArrayContainers {


 /*
  * This is a helper class to hold the data, allowing
  * it to act as a singly linked list in case of either
  * hash collision or simple slot collisions.
  */
template <class T>
class Node {
    public:
        Node(string key, T data) {
            this->data = data;
            this->key  = key;
            next = NULL;
        }
        T getValue(string key) {
            if(next == NULL) {
                // If true, there are no other options, so this mush be
                // the correct value (assuming no bugs in placement).
                return data;
            } else if(key.compare(this->key) == 0) {
                // Slow but accurate; alternately use the hash for speed,
                // but that add as small chance of returning the wrong value
                // due to a collision.
                return data;
            } else return next->getValue(key);
        }
        virtual ~Node(){}
    private:
        friend int StringHash(const string &s);
        string key;
        T data;
        Node<T>* next;
};


unsigned int StringHash(const string &s) {
    unsigned int out = 0;
    unsigned int i = 0;
    const char* data = s.c_str();
    while(data[i] != 0) {
        out ^= (data[i] << (8 * (i%4)));
        out ^= (data[i] << (23 - (i%17)));
        i++;
    }
    /*// Not sure the extra Xorshift is needed
    out ^=  (out << 13);
    out ^=  (out >> 5);
    out ^=  (out << 17);*/
    return out;
}




}
