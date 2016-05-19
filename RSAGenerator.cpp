#include "RSAGenerator.hpp"

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
 *     factorization of N, relatively fast as well. But the latter is
 *     supposed to be hard.
 *      (i.e supposedly there is no algorithm to solve the problem other
 *       than the exponential ones)
 *
 */
using namespace std;

gmp_randstate_t RSAGenerator::r_state;
init_rand_state RSAGenerator::init_rs(RSAGenerator::r_state);

double init_rand_state::get_random_seed()
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

init_rand_state::init_rand_state(gmp_randstate_t &r_state)
{
    double seed = get_random_seed();
    gmp_randinit_default(r_state);
    gmp_randseed_ui(r_state, seed);
}

/**
 *  return a random prime number of 'bit_count' bits
 *
 *  @arg tmp must be a initialized mpz_t variable and is used as an
 *       internal temporary variable
 *  @arg r_state must be an initialized and seeded gmp random state variable
 */
mpz_class random_prime_number_b(
    mpz_t &tmp, gmp_randstate_t &r_state, unsigned bit_count)
{
    do {
        mpz_urandomb(tmp, r_state, bit_count);
    } while (mpz_probab_prime_p(tmp, 50) == 0);
    // 50 is the number of iteration in the Miller Rabin algorithm
    return mpz_class(tmp);
}


/**
 *  return a random prime number between 0 and max-1 included.
 *
 *  @arg tmp must be a initialized mpz_t variable and is used as an
 *       internal temporary variable
 *  @arg r_state must be an initialized and seeded gmp random state variable
 */
mpz_class random_prime_number_m(
    mpz_t &tmp, gmp_randstate_t &r_state, mpz_class max)
{
    do {
        mpz_urandomm(tmp, r_state, max.get_mpz_t());
    } while (mpz_probab_prime_p(tmp, 50) == 0);
    return mpz_class(tmp);
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
