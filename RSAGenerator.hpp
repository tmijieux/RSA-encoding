#ifndef RSAGENERATOR_H
#define RSAGENERATOR_H

#include <gmpxx.h>
#include <utility>
using namespace std;

class RSAGenerator {
    mpz_class P, Q, E, D, N, C;
    double get_random_seed();
public:
    static const unsigned DEFAULT_KEY_SIZE = 2048;
    RSAGenerator(unsigned nbits = DEFAULT_KEY_SIZE);
    
    pair<mpz_class, mpz_class> get_public_key() const;
    pair<mpz_class, mpz_class> get_private_key() const;
};

#endif //RSAGENERATOR_H
