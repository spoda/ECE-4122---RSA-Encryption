// ECE4122/6122 RSA Encryption/Decryption assignment
// Fall Semester 2015

#include <iostream>
#include "RSA_Algorithm.h"

using namespace std;

int main()
{
  // Instantiate the one and only RSA_Algorithm object
  RSA_Algorithm RSA;
  
  // Loop from sz = 32 to 1024 inclusive
  // for each size choose 10 different key pairs
  // For each key pair choose 10 differnt plaintext 
  // messages making sure it is smaller than n.
  // If not smaller then n then choose another
  // For eacm message encrypt it using the public key (n,e).
  // After encryption, decrypt the ciphertext using the private
  // key (n,d) and verify it matches the original message.

  // your code here
gmp_randclass rng(gmp_randinit_default);
mpz_class m,c,d;
int sz = 32;
int fail = 0, total = 0;

for (int sz = 32; sz <= 1024; sz *=2) {
    for (int i = 0; i < 10; i++) {
        RSA.GenerateRandomKeyPair(sz);
        RSA.PrintNDE();
        for (int j = 0; j < 10; j++) {
            do {
                   m=rng.get_z_bits(sz*2);
               }
            while ( m>= RSA.n);
                RSA.PrintM(m);
               c = RSA.Encrypt(m);
                RSA.PrintC(c);
                d = RSA.Decrypt(c);
                if (m != d) {
                    fail++;
                }
                total++;
            }
        }
     }
}
  
