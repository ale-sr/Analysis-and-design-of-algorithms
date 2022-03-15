//
// Created by Jean on 12/12/2021.
//

#ifndef ADA_PJ_AUX_FUNCTIONS_H
#define ADA_PJ_AUX_FUNCTIONS_H

#include "libraries.h"
#include "preprocess_functions.h"


inline bool is_code(const char &c, const int &code)
{
    return codification[code][c] != -1;
}


std::string inToS(int n , int size) {
    std::string res;

    while (size--) {
        res += n & 1 ? '1' : '0';
        n >>= 1;
    }
    std::reverse(res.begin(), res.end());
    return res;
}


std::string codify(const char& c , const int& code) {
    std::string res;
    int n = codification[code][c];
    int size = cost[code];

    while (size--) {
        res += n & 1 ? '1' : '0';
        n >>= 1;
    }
    std::reverse(res.begin(), res.end());
    return res;
}



std::string changeCodeOf(const int& code, const int& to)
{
    return chageCode[code][to];
}

std::vector<int> getSets(const char& c)
{
    std::vector<int> results;
    for (int code = 1; code <= NUM_COD; code++)
        if (is_code(c, code))
            results.push_back(code);

    return results;
}

#endif //ADA_PJ_AUX_FUNCTIONS_H
