//
//  main.cpp
//  RC4 Algorithm
//
//  Created by Brian Fernandez on 4/3/20.
//  Copyright © 2020 Brian Fernandez. All rights reserved.
//Implement the RC4 stream cipher in C++. User should be able to enter any key that is 5 bytes to 32 bytes long. Be sure to discard the first 3072 bytes of the pseudo random numbers. THE KEY OR THE INPUT TEXT MUST NOT BE HARD CODED IN THE PROGRAM.

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

bool check(vector<int>temp_key);
vector<int>permutation(vector<int>key);
void rng(vector<int>S);
void encryption();
void decryption();
int main()
{
    char c;
    
    vector<int>temp_key;
    
    cout << "Enter a key that is 5 bytes to 32 bytes long.\n";
    do
    {
    c = cin.get();
    //integer = (c);
    if(c != '\n')
        temp_key.push_back((c));
    } while (c != '\n');
    
    //for(int i = 0; i < temp_key.size(); i++)
      //cout<<temp_key[i];
        
    //if(check(temp_key))
      //cout<<"Key is correct length!\n";
    rng(permutation(temp_key));
    return 0;
}
bool check(vector<int>temp_key)
{
    char c;
    //checks to see key is 5 to 32 bytes long
    while (temp_key.size() < 5 || temp_key.size() > 32)
    {
        temp_key.clear();
        cout<<"Enter a key that is 5 bytes to 32 bytes long.\n";
         do
         {
         c = cin.get();
         if(c != '\n')
         temp_key.push_back((c));
         } while (c != '\n');
    }
    return true;
}
vector<int>permutation(vector<int>key)
{
    int i = 0;
    int j = 0;
    int n = 0;
    int temp = 0;
    vector<int>S;
    vector<int>T;
    //initialization
    for (i=0; i < 256; i++)
    {
        S.push_back(i);
    }
    //permuation & swapping
    for (i=0; i < 256; i++)
    {
        n = key[i % key.size()];
        j = (j + S[i] + n) % 256;
        temp = S[i];
        S.at(i) = S[j];
        S.at(j) = temp;
    }
    
    return S;
}
void rng(vector<int>S)
{
    int counter = 0;
    int i = 0;
    int j = 0;
    int t = 0;
    int temp;
    //while (counter <= 3072) //discarding the first 3072 bytes of the pseudo random numbers.
    while (counter <= 6)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        temp = S[i];
        S.at(i) = S[j];
        S.at(j) = temp;
        t = (S[i] + S[j]) % 256;
        cout<<S[t]<<endl;
        counter++;
    }
}
void encryption(); // the bit form of the char is going to be xor'd with the bit form of byte key chosen, use cout<< hex << cipher to output it into hex form.
void decryption();
