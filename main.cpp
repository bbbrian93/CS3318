//
//  main.cpp
//  RC4 Algorithm
//
//  Created by Brian Fernandez on 4/3/20.
//  Copyright © 2020 Brian Fernandez. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

bool check(vector<char>temp_key);
void permutation(vector<char>key);
void rng();
void encryption();
void decryption();`
int main()
{
    char c;
    int integer;
    
    vector<char>temp_key;

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
        
    if(check(temp_key))
        cout<<"Key is correct length!\n";
    permutation(temp_key);
    return 0;
}
bool check(vector<char>temp_key)
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
int permutation(vector<char>key)
{
    int i = 0;
    int j = 0;
    int n = 0;
    int S[255];
    int T[255];
    //initialization
    for (i; i < 255; i++)
    {
        S[i] = i;
        
        n = key[i % key.size()];
    //permuation & swapping
    //for (i=0; i < 255; i++)
    
        j = (j + S[i] + n) % 256;
        S[i] = S[j];
    }
    return S[i];
}
void rng(int array[])
{
    int counter = 0;
    int i = 0;
    int j = 0;
    int t = 0;
    int temp;
    //while (counter <= 3072) //discarding the first 3072 bytes of the pseudo random numbers.
    while (counter <= 10)
    {
        i = (i + 1) % 256;
        j = (j + array[i]) % 256;
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        t = (array[i] + array[j]) % 256;
        counter++;
    }
    cout<<array[t];
}
void encryption();
void decryption();
