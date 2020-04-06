//  main.cpp
//  RC4 Algorithm
//
//  Created by Brian Fernandez on 4/3/20.
//  Copyright © 2020 Brian Fernandez. All rights reserved.

/*
Implement the RC4 stream cipher in C++. 
User should be able to enter any key that is 5 bytes to 32 bytes long. 
Be sure to discard the first 3072 bytes of the pseudo random numbers. 
THE KEY OR THE INPUT TEXT MUST NOT BE HARD CODED IN THE PROGRAM.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;

//prototype functions
bool check(vector<int>temp_key);
vector<int>permutation(vector<int>key);
vector<int>rng(vector<int>S);
vector<int>file_upload();
void encryption(vector<int>plaintext, vector<int>stream);
void decryption(vector<int>stream);
unsigned long int hex2dec(string hex);
int main()
{
    char c = ' ';
    string fileName;
    vector<int>temp_key;
    vector<int>characters;
    characters = file_upload();

    cout << "Enter a key that is 5 bytes to 32 bytes long.\n";
	cin.get(); // grabs last whitespace character from previous entry
    do
    { // if it is new line character, it doesn't get pushed back into the vector
		c = cin.get();
		if (c != '\n') 
		{
			temp_key.push_back((c)); 
		}
    } while (c != '\n');

	// checks key length
    if(check(temp_key)) 
      cout<<"Key length is correct length!\n"; 

    temp_key = permutation(temp_key);

    temp_key = rng(temp_key);
    
	encryption(characters, temp_key);

	decryption(temp_key);

    return 0;
}
bool check(vector<int>temp_key)
{
    char c;
    //checks to see key is between 5 to 32 bytes long
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
    //initialization of the S vector
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
	//S vector is now permutated and swapped
    return S;
}
vector<int>rng(vector<int>S)
{
    int counter = 0;
    int i = 0;
    int j = 0;
    int t = 0;
    int temp;
    vector<int>stream;
    //while (counter < 3572)
	cout<< "Pseudo random keystream created...\n";
	while (counter < 3572) // plaintext size is 462 , 500 stream size covers it
	{
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        temp = S[i];
        S.at(i) = S[j];
        S.at(j) = temp;
        t = (S[i] + S[j]) % 256;
		//discards the first 3072 bytes of the pseudo random numbers by
		//not saving until it passes counter of 3072
		if (counter > 3072) 
		{
			stream.push_back(S[t]);
			//if you want to display the RNG's
			//cout << S[t] << ' ';
		}
		counter++;
    }
    return stream;
}
vector<int>file_upload()
{	
	string file_name;
	cout<<"Enter name of file to encrypt: \n";
	cin >> file_name;
    ifstream inFile;
    string input;

	inFile.open(file_name);

	if (!inFile)
	{
		cout << "ERROR OPENING FILE...\n";
		exit(0);
	}
	else
		cout << "File uploaded...\n";

    getline(inFile, input);
    int length = input.length();

    vector<int>plainText;

    for (int i = 0; i < length; ++i)
    {
        plainText.push_back(input[i]);
    }
    inFile.close();
    return plainText;
}
void encryption(vector<int>plaintext, vector<int>stream) // the bit form of the char is going to be xor'd with the bit form of byte key chosen, use cout<< hex << cipher to output it into hex form.
{
	cout << "Encrypting file...";
	ofstream outFile;
	outFile.open("ciphertext.txt");

    vector<int>ciphertext;
    int n = 000;
    //encrypting with random stream
    for (int i = 0; i < plaintext.size(); i++)
    {
        n = plaintext[i] ^ stream[i];
		
		ciphertext.push_back(n);
		
			
    }
    //displaying ciphertext IN HEX
	cout << "\nciphertext.txt file created...\nCiphertext in hex:\n";
    for (int i = 0; i < ciphertext.size(); i++)
    {
        cout<< hex << setw(2) << setfill('0') << right << ciphertext[i]; 
		outFile << hex << setw(2) << setfill('0') << right << ciphertext[i]; 
    }
	cout << endl;
	outFile.close();

}
void decryption(vector<int>stream)
{
	cout << "Decrypting...";
	string input;
	ifstream inFile;
	ofstream outFile;
	string hextext;
	string plaintext;
	int key_index = 0;

	int n;
	//opening file
	inFile.open("ciphertext.txt");
	outFile.open("decryption.txt");
	if (!inFile)
	{
		cout << "ERROR OPENING FILE...\n";
		exit(0);
	}
	else
		cout << "ciphertext.txt file uploaded...\nPlaintext:\n";
	//saves file into string input;
	getline(inFile, input);
	//saves length of string
	int length = input.length();

	for (int i = 0; i < length; i++)
	{
		string temp;
		hextext = input.substr(i, 2);
		n = hex2dec(hextext);
		n = n ^ stream[key_index];
		temp = n;
		plaintext += (temp);
		key_index++;
		i++;
	}
	cout << plaintext;
	outFile << plaintext;
	outFile.close();
	inFile.close();
}
unsigned long int hex2dec(string hex)
{
	unsigned long result = 0;
	for (int i = 0; i < hex.length(); i++)
	{
		if (hex[i] >= 48 && hex[i] <= 57)
		{
			result += (hex[i] - 48) * pow(16, hex.length() -i-1);
		}
		else if (hex[i] >= 65 && hex[i] <= 70)
		{
			result += (hex[i] - 55) * pow(16, hex.length() -i-1);
		}
		else if (hex[i] >= 97 && hex[i] <= 102)
		{
			result += (hex[i] - 87) * pow(16, hex.length() -i-1);
		}
	}
	return result;
}