#ifndef RSAGENERATOR_H
#define RSAGENERATOR_H

#include <gmpxx.h>
#include <utility>
#include <fstream>
#include <cmath>

using namespace std;

#define N_DEFAULT 8051
#define D_DEFAULT 4783
#define E_DEFAULT 79


class rand_state {
public:
    
    double get_random_seed()
    {
        double r = 0.;
        ifstream random("/dev/random");
        if (random.is_open()) {
            printf("reading random file ...\n");
            do {
                char data[sizeof r];
                random.read(data, sizeof data);
                r = *(double*) data;
            } while (!isnormal(r));
            random.close();
            printf("random file read!\n");
        } else {
            r = time(NULL) + (unsigned long) &r;
        }
        return r;
    }

    rand_state(gmp_randstate_t &r_state)
    {
        double seed = get_random_seed();
        gmp_randinit_default(r_state);
        gmp_randseed_ui(r_state, seed);
    }
};

class RSAGenerator {
    static gmp_randstate_t r_state;
    static rand_state rs;
    mpz_class P, Q, E, D, N, C;

public:
    static const unsigned DEFAULT_KEY_SIZE = 2048;
    RSAGenerator(unsigned nbits = DEFAULT_KEY_SIZE);
    
    pair<mpz_class, mpz_class> get_public_key() const;
    pair<mpz_class, mpz_class> get_private_key() const;
};

#endif //RSAGENERATOR_H
