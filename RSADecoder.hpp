#ifndef RSADECODER_H
#define RSADECODER_H

#include <gmpxx.h>
#include <vector>

using std::vector;
using std::string;

class RSADecoder {
    mpz_class N, D;
    size_t key_length;
    vector<mpz_class> &split_data(string &str, vector<mpz_class> &output);
    string mpz_to_string(mpz_class &c);
    
public:
    RSADecoder(mpz_class &N, mpz_class &D);
    string decrypt(string data);
};

#endif //RSADECODER_H
