#include "RSAGenerator.hpp"
#include <fstream>
#include <cmath>

/**
 *     N = P * Q with P and Q prime
 *     C = (P-1)*(Q-1) Euler's totient function for N
 *     E and D such as E < C and E*D = 1 (mod C)
 *
 *     public key is (N, E) 
 *     private key is (N, D)
 *
 *     encrypting is c = m^E (mod N)
 *     decrypting is m = c^D (mod N)
 *
 *     valid:
 *     (m^E)^D  = m^(E*D)           (mod N)
 *              = m^(kC + 1)        (mod N) (because E*D = 1 (mod N))
 *              = ((m^C)^k) * (m^1) (mod N)
 *              = m                 (mod N) (because m^C = 1 (mod N))
 *
 *     attack is hard:
 *     there is a linear reduction between any attack and
 *     the factorization of N. This means that if you can attack
 *     this cryptosystem relatively fast, then you can have the
 *     factorization of N, relatively fast as well. But the latter is
 *     supposed to be hard.
 *      (i.e supposedly there is no algorithm to solve the problem other
 *       than the exponential ones)
 *
 */

mpz_class random_prime_number(
    mpz_t &rnum, gmp_randstate_t r_state, unsigned bit_count)
{
    do {
        mpz_urandomb(rnum, r_state, bit_count);
    } while (mpz_probab_prime_p(rnum, 50) == 0);
    return mpz_class(rnum);
}

mpz_class random_prime_number(
    mpz_t &rnum, gmp_randstate_t r_state, mpz_class max)
{
    do {
        mpz_urandomm(rnum, r_state, max.get_mpz_t());
    } while (mpz_probab_prime_p(rnum, 50) == 0);
    return mpz_class(rnum);
}

RSAGenerator::RSAGenerator(unsigned bit_count):
    P(0), Q(0), E(0), D(0), N(0), C(0)
{
    double seed = get_random_seed();
    mpz_t tmp;
    gmp_randstate_t r_state;
    mpz_init(tmp);
    gmp_randinit_default(r_state);
    gmp_randseed_ui(r_state, seed);

    P = random_prime_number(tmp, r_state, bit_count/2);
    Q = random_prime_number(tmp, r_state, bit_count/2);
    C = (P - 1) * (P - 1);
    E = random_prime_number(tmp, r_state, C);
    N = P * Q;
    
    if (mpz_invert(tmp, E.get_mpz_t(), C.get_mpz_t()))
        D = mpz_class(tmp);
    else
        throw "we may have a problem with the key generation algorithm";

    gmp_randclear(r_state);
    mpz_clear(tmp);
}

pair<mpz_class, mpz_class> RSAGenerator::get_public_key() const
{
    return make_pair(N, E);
}

pair<mpz_class, mpz_class> RSAGenerator::get_private_key() const
{
    return make_pair(N, D);
}

double RSAGenerator::get_random_seed()
{
    double r = 0.;
    ifstream random("/dev/random");
    if (random.is_open()) {
        do {
            char data[sizeof r];
            random.read(data, sizeof data);
            r = *(double*) data;
        } while (!isnormal(r));
        random.close();
    } else {
        r = time(NULL) + (unsigned long) &r;
    }

    return r;
}
