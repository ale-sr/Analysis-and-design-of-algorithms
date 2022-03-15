//
// Created by Jean on 12/15/2021.
//

#ifndef ADA_PJ_TEST_FUNCTIONS_H
#define ADA_PJ_TEST_FUNCTIONS_H

#include "../auxFiles/libraries.h"
#include "timer.h"

std::string randomEncode(const int& n){

    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count() );

    std::mt19937 gen(seed);
    std::uniform_int_distribution<unsigned> distrib(32, 126);

    std::string res ={};
    for (int i = 0; i < n; ++i) {
        res += char(distrib(gen) );
    }

//    std::cout<<res<<std::endl;

    return  res;
}





#endif //ADA_PJ_TEST_FUNCTIONS_H
