#include "RSAGenerator.hpp"


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

gmp_randstate_t RSAGenerator::r_state;
rand_state RSAGenerator::rs(RSAGenerator::r_state);

mpz_class random_prime_number_b(
    mpz_t &rnum, gmp_randstate_t &r_state, unsigned bit_count)
{
    do {
        mpz_urandomb(rnum, r_state, bit_count);
    } while (mpz_probab_prime_p(rnum, 50) == 0);
    return mpz_class(rnum);
}

mpz_class random_prime_number_m(
    mpz_t &rnum, gmp_randstate_t &r_state, mpz_class max)
{
    do {
        mpz_urandomm(rnum, r_state, max.get_mpz_t());
    } while (mpz_probab_prime_p(rnum, 50) == 0);
    return mpz_class(rnum);
}

RSAGenerator::RSAGenerator(unsigned bit_count):
    P(0), Q(0), E(0), D(0), N(0), C(0)
{
    mpz_t tmp;
    mpz_init(tmp);

    P = random_prime_number_b(tmp, r_state, bit_count/2);
    Q = random_prime_number_b(tmp, r_state, bit_count/2);
    C = (P - 1) * (Q - 1);
    E = random_prime_number_m(tmp, r_state, C);
    N = P * Q;
    
    if (mpz_invert(tmp, E.get_mpz_t(), C.get_mpz_t()))
        D = mpz_class(tmp);
    else
        throw "we may have a problem with the key generation algorithm";

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
