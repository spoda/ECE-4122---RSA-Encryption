// RSA Assignment for ECE4122/6122 Fall 2015

#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "RSA_Algorithm.h"

using namespace std;

// Implement the RSA_Algorithm methods here
mpz_class GetRandomKP(size_t sz);
mpz_class Encryption(mpz_class M);
mpz_class Decryption(mpz_class C);
gmp_randclass rng2(gmp_randinit_default);
mpz_class n,d,e;
// Constructor
RSA_Algorithm::RSA_Algorithm()
  : rng(gmp_randinit_default)
{
  // get a random seed for the random number generator
  int dr = open("/dev/random", O_RDONLY);
  if (dr < 0)
    {
      cout << "Can't open /dev/random, exiting" << endl;
      exit(0);
    }
  unsigned long drValue;
  read(dr, (char*)&drValue, sizeof(drValue));
  //cout << "drValue " << drValue << endl;
  rng.seed(drValue);
// No need to init n, d, or e.
}

// Fill in the remainder of the RSA_Algorithm methods


mpz_class GetPrime(size_t sz) {
int flag;
mpz_class bits(sz);
mpz_class result;
do {
    result = rng2.get_z_bits(bits);
    flag = mpz_probab_prime_p(result.get_mpz_t(), 100);
}
while (flag == 0);
return result;
}

void RSA_Algorithm::GenerateRandomKeyPair(size_t sz) {
mpz_class p, q, gcd;
p = GetPrime(sz);
q = GetPrime(sz);
n = p *q;
mpz_class ph = (p - 1) * (q-1);
mpz_class temp(1);
mpz_class bits(sz * 2);
do {
d = rng2.get_z_bits(bits);
mpz_gcd(gcd.get_mpz_t(), d.get_mpz_t(), ph.get_mpz_t());
}
while (d >=ph || gcd != temp);
int results = mpz_invert(e.get_mpz_t(), d.get_mpz_t(), ph.get_mpz_t());
}

mpz_class RSA_Algorithm::Encrypt(mpz_class M) {
mpz_class c;
mpz_powm(c.get_mpz_t(), M.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
return c;
}

mpz_class RSA_Algorithm::Decrypt(mpz_class C) {
mpz_class m;
mpz_powm(m.get_mpz_t(), C.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
return m;
}




void RSA_Algorithm::PrintND()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " d " << d << endl;
}

void RSA_Algorithm::PrintNE()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " e " << e << endl;
}

void RSA_Algorithm::PrintNDE()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " d " << d << " e " << e << endl;
}

void RSA_Algorithm::PrintM(mpz_class M)
{ // Do not change this, right format for the grading script
  cout << "M " << M << endl;
}

void RSA_Algorithm::PrintC(mpz_class C)
{ // Do not change this, right format for the grading script
  cout << "C " << C << endl;
}




