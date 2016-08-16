#include <RSAEncoder.hpp>
#include <algorithm>
#include <cmath>
#include <ctgmath>

using std::vector;
using std::string;
using std::min;
using RSA::Encoder;

#ifndef __GNUC__
# define noexcept
#endif

namespace RSA {
class exception : public std::exception {
    std::string _s;
public:
    exception(std::string s): _s(s) {}
    char const *what() const noexcept { return _s.c_str(); }
};
};
        
Encoder::Encoder(mpz_class const &N, mpz_class const &E):
    _N(N), _E(E)
{
    _keyBitLength = mpz_sizeinbase(_N.get_mpz_t(), 2);
    _keyLength = _keyBitLength / 8;
                                                      
    printf("encoder N key_bit_length = %zu\n", _keyBitLength);
    if (_keyBitLength <= CHAR_BIT + 1)
        throw exception("key too small");
}

/* if the binary representation 'S' of the ToBeEncoded String is bigger
   than N ( N =~ keySize(N) ) it cannot be decoded properly
   ( rather the decoding algorithm may output something like "S mod N" )
   
   String longer than keyLength are then splitted
 */
vector<mpz_class> &Encoder::SplitData(
    std::string &str, vector<mpz_class> &output)
{
    size_t len = str.length();
    size_t lenCopy = len;
    size_t nread = 0;
    
    const char *data = str.c_str();
    while (nread < len) {
        mpz_class i;
        size_t read = min(_keyLength, lenCopy);
        
        mpz_import(i.get_mpz_t(), 1, 1, read, 0, 0, data);
        output.push_back(i);

        data += read;
        nread += read;
        lenCopy -= read;
    }

    return output;
}

string Encoder::MpzToString(mpz_class &c)
{
    size_t length = mpz_sizeinbase(c.get_mpz_t(), 10) + 2;
    char *c_str = new char[length];
    mpz_get_str(c_str, 10, c.get_mpz_t());
    string s(c_str);
    delete [] c_str;
    return s;
}

static string trim(string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

string Encoder::Encrypt(string data)
{
    vector<mpz_class> input;
    string output = "";
    
    input = SplitData(data, input);
    for_each(
        input.begin(), input.end(),
        [&] (mpz_class m) {
            mpz_class c;
            mpz_powm_sec(
                c.get_mpz_t(),
                m.get_mpz_t(),
                _E.get_mpz_t(),
                _N.get_mpz_t()
            );
            output += MpzToString(c) + " ";
        }
    );
    return trim(output);
}
