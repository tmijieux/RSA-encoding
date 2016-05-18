#include <RSADecoder.hpp>
#include <algorithm>
#include <cmath>
#include <ctgmath>

using std::min;
using std::string;
using std::stringstream;
using std::vector;

RSADecoder::RSADecoder(mpz_class &N_, mpz_class &D_):
    N(N_), D(D_)
{
    key_length = mpz_sizeinbase(N.get_mpz_t(), 2);
    printf("decoder N key length = %zu\n", key_length);
}

vector<mpz_class> &RSADecoder::split_data(
    string &str, vector<mpz_class> &output)
{
    stringstream ss(str);
    string item;
    
    while (std::getline(ss, item, ' ')) {
        output.push_back(mpz_class(item));
    }
    return output;
}

string RSADecoder::mpz_to_string(mpz_class &c)
{
    size_t bit_length = mpz_sizeinbase(c.get_mpz_t(), 2);
    size_t length = (bit_length + 7) / 8;

    printf("length = %zu\n", length);
    char *c_str = new char[length+1];
    c_str[length] = '\0';
    mpz_export(c_str, NULL, 1, length, 0, 0, c.get_mpz_t());
    
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

string RSADecoder::decrypt(string data)
{
    vector<mpz_class> input;
    string output = "";
    
    input = split_data(data, input);
    for_each(
        input.begin(), input.end(),
        [&] (mpz_class c) {
            mpz_class m;
            mpz_powm_sec(
                m.get_mpz_t(),
                c.get_mpz_t(),
                D.get_mpz_t(),
                N.get_mpz_t()
            );
            output += mpz_to_string(m);
        }
    );

    return trim(output);
}


