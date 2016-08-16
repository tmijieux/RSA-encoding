#ifndef RSA_GENERATOR_H
#define RSA_GENERATOR_H

#include <gmpxx.h>
#include <utility>
#include <fstream>
#include <cmath>

/**
 *    RSA cryptosystem:
 *
 *     N = P * Q with P and Q prime
 *     P and Q must have the same size
 *     C = (P-1)*(Q-1) Euler's totient function for N
 *     E and D such as E < C and E*D = 1 (mod C)
 *
 *     In practice P and Q are chosen randomly and they are confirmed to be prime
 *     with the Miller Rabin algorithm.
 *     Then E is chosen to be a random prime integer between 0 and C-1. Thus,
 *     E being prime, we are sure that gcd(E, C) = 1.
 *     (otherwise there is no D such as E*D=1(mod N)).
 *     Eventually D is computed as the modular inverse of E (mod N).
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
 *     factorization of N relatively fast as well. But the latter is
 *     supposed to be hard.
 *      (i.e supposedly there is no algorithm to solve the problem other
 *       than the exponential ones)
 *
 */


namespace RSA {
/**
 * the purpose of this class is to initialize a (possibly static)
 * gmp_randstate_t variable
 */
class init_rand_state {
    double get_random_seed();
public:
    init_rand_state(gmp_randstate_t &r_state);
};


/**
 *  generate key for the RSA Cryptosystem
 */
class Generator {
    static gmp_randstate_t r_state;
    static init_rand_state init_rs;
    mpz_class P, Q, E, D, N, C;

public:
    static const unsigned DEFAULT_KEY_SIZE = 1024;
    Generator(unsigned nbits = DEFAULT_KEY_SIZE);

    /** Return (N, E) */
    std::pair<mpz_class, mpz_class> GetPublicKey() const;

    /** Return (N, D) */
    std::pair<mpz_class, mpz_class> GetPrivateKey() const;
};


}; // end namespace RSA
#endif // RSA_GENERATOR_H
