#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        
        unsigned long long w[5] = {0}; //for storing w[0] - w[4]

        int wIndex = 4;

        int index = k.size() - 1; //since we start from the back

        while (wIndex >= 0 && index >= 0) { //for the w part
            for (int i = 5; i >= 0; i--) { //we need to do the last 6 digits at a time
                if (index < 0) {
                    break;
                }
                w[wIndex] += pow(36, 5 - i) * letterDigitToNumber(k[index]); // "conversion" part
                index--;
            } 

            // std::cout << "w[" << wIndex << "] = " << w[wIndex] << std::endl; //debug

            wIndex--;
        }

        //final hashing

        unsigned long long hash = 0;

        for (int i = 0; i < 5; i++) {
            hash += rValues[i] * w[i];
        }

        return hash;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        int ascii = int(letter);
        if (ascii >= 97) {//this is a lower case letter
            return ascii - 97;
        }
        else if (ascii >= 65) {
            return ascii - 65;
        }
        else {
            return ascii - 48 + 26;
        }

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
