#ifndef RECCHECK
#include <iostream>
#include <set>
#include <string>
#endif

#include "wordle.h"
#include "dict-eng.h"

using namespace std;

// Helper function declaration
void genWords(std::string& current, int index, std::string floating, const std::set<std::string>& dict, std::set<std::string>& results);

// Main wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> results;
    std::string current = in;
    genWords(current, 0, floating, dict, results);
    return results;
}

// Recursive helper function
void genWords(std::string& current, int index, std::string floating, const std::set<std::string>& dict, std::set<std::string>& results)
{
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
        for(char c = 'a'; c <= 'z'; ++c) {
            current[index] = c;

            size_t pos = floating.find(c);

            if(pos != std::string::npos) {
                std::string new_floating = floating;
                new_floating.erase(pos, 1);
                genWords(current, index + 1, new_floating, dict, results);
            }
            else {
                // Count remaining dashes INCLUDING this one
                int leftoverDashes = 0;
                for(int i = index + 1; i < current.size(); ++i) {
                    if(current[i] == '-') leftoverDashes++;
                }

                if(leftoverDashes >= static_cast<int>(floating.size())) {
                    genWords(current, index + 1, floating, dict, results);
                }
            }
        }
        current[index] = '-'; // backtrack
    }
}



