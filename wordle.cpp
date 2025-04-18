#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void genWords(std::string& current, int index, std::string floating, const std::set<std::string>& dict, std::set<std::string>& results);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    std::set<std::string> results;
    std::string current = in;
    
    genWords(current, 0, floating, dict, results);

    return results;

}

// Define any helper functions here

void genWords(std::string& current, int index, std::string floating, const std::set<std::string>& dict, std::set<std::string>& results) {

    if(index == current.size()) {
        if(floating.empty() && dict.find(current) != dict.end()) {
            results.insert(current);
        }

        return;
    }

    if(current[index] != '-') {
        genWords(current, index + 1, floating, dict, results);
    }

    else {
        for(char c 'a'; c <= 'z'; ++c) {
            current[index] = c;

            size_t pos = floating.find(c);

            if(pos != std::string::npos) {
                std::string new_floating  = floating;
                new_floating.erase(pos, 1);

                genWords(current, index + 1, new_floating, dict, results);
            }

            else {
                int leftoverDashes = 0;

                for(int i = index + 1; i < current.size(); ++i) {
                    if(current[i] = '-') {
                        leftoverDashes++;
                    }
                }

                if(leftoverDashes >= static_cast<int>(floating.size())) {
                    genWords(current, index + 1, floating, dict, results);
                }
            }
        }

        current[index] = '-';
    }
}


