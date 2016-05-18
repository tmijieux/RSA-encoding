#include <RSAEncoder.hpp>
#include <algorithm>
#include <cmath>
#include <ctgmath>

using std::vector;
using std::string;
using std::min;

RSAEncoder::RSAEncoder(mpz_class &N_, mpz_class &E_):
    N(N_), E(E_)
{
    key_bit_length = mpz_sizeinbase(N.get_mpz_t(), 2);
    key_length = key_bit_length / 8;
                                                      
    printf("encoder N key_bit_length = %zu\n", key_bit_length);
    if (key_bit_length <= CHAR_BIT + 1)
        throw "key too small";
}

vector<mpz_class> &RSAEncoder::split_data(
    std::string &str, vector<mpz_class> &output)
{
    size_t s_length = str.length();
    size_t s_length_cpy = s_length;
    size_t nread = 0;
    
    const char *data = str.c_str();
    while (nread < s_length) {
        mpz_class m_i;
        size_t read = min(key_length, s_length_cpy);
        
        mpz_import(m_i.get_mpz_t(), 1, 1, read, 0, 0, data);
        output.push_back(m_i);

        data += read;
        nread += read;
        s_length_cpy -= read;
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
    vector<mpz_class> input;
    string output = "";
    
    input = split_data(data, input);
    for_each(
        input.begin(), input.end(),
        [&] (mpz_class m) {
            mpz_class c;
            mpz_powm_sec(
                c.get_mpz_t(),
                m.get_mpz_t(),
                E.get_mpz_t(),
                N.get_mpz_t()
            );
            output += mpz_to_string(c) + " ";
        }
    );

    return trim(output);
}


