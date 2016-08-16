#ifndef RSA_ENCODER_H
#define RSA_ENCODER_H

#include <gmpxx.h>
#include <vector>

namespace RSA {

class Encoder {
    mpz_class _N, _E;
    size_t _keyBitLength;
    size_t _keyLength;

    std::vector<mpz_class> &SplitData(
        std::string &str, std::vector<mpz_class>&);
    std::string MpzToString(mpz_class &c);

public:
    Encoder(mpz_class const &N, mpz_class const &E);
    std::string Encrypt(std::string data);
};

}; // end namespace RSA

#endif //RSA_ENCODER_H
