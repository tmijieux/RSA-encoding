#ifndef RSAENCODER_H
#define RSAENCODER_H
#include <gmpxx.h>
#include <vector>

class RSAEncoder {
    mpz_class N, E;
    size_t key_length;
    std::vector<mpz_class> *split_data(std::string &str);
    std::string mpz_to_string(mpz_class &c);
    
public:
    RSAEncoder(mpz_class &N, mpz_class &E);
    std::string encrypt(std::string data);
};

#endif //RSAENCODER_H
