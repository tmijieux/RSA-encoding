#include <RSAEncoder.hpp>
#include <algorithm>
#include <cmath>
#include <ctgmath>

using std::vector;
using std::string;
using std::min;

RSAEncoder::RSAEncoder(mpz_class &N, mpz_class &E)
{
    this->N = N;
    this->E = E;

    key_length = mpz_sizeinbase(N.get_mpz_t(), 2);
}

vector<mpz_class> *RSAEncoder::split_data(std::string &str)
{
    size_t s_len = str.length();
    int n = ceil((double) s_len / key_length);
    vector<mpz_class> *output = new vector<mpz_class>();
    
    const char *data;
    data  = str.c_str();
    for (int i = 0; i < n; ++i) {
        mpz_class m_i;
        
        mpz_import(m_i.get_mpz_t(), 1, 1, min(key_length, s_len), 0, 0, data);
        output->push_back(m_i);

        if ( (ssize_t)(s_len - key_length) < 0) {
            s_len = 0;
            // break; we should be going out of the loop now anyway
        } else {
            s_len -= key_length;
        }
        data += key_length;
    }

    return output;
}

string RSAEncoder::mpz_to_string(mpz_class &c)
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

std::string RSAEncoder::encrypt(string data)
{
    vector<mpz_class> *input;
    string output = "";
    
    input = split_data(data);
    for_each(
        input->begin(), input->end(),
        [&] (mpz_class m) {
            mpz_class c;
            mpz_powm(
                c.get_mpz_t(),
                m.get_mpz_t(),
                E.get_mpz_t(),
                N.get_mpz_t()
            );
            output += mpz_to_string(c) + " ";
        }
    );
    delete input;

    return trim(output);
}


