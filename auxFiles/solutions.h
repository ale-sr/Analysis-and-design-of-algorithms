//
// Created by Jean on 12/13/2021.
//

#ifndef ADA_PJ_SOLUTIONS_H
#define ADA_PJ_SOLUTIONS_H

#include "auxFiles/libraries.h"
#include "auxFiles/preprocess_functions.h"
#include "auxFiles/aux_functions.h"

namespace p1 {
    std::vector<int> intersect(const std::vector<int>& a, const std::vector<int>& b){
        std::vector<int> result;
        int size = (a.size() <= b.size())? a.size():b.size();
        int i = 0, j = 0;
        for(int x = 0; x < size+1; x++){
            if(a[i] == b[j]){
                result.push_back(a[i]);
                i++;
                j++;
            }
            else if(a[i] < b[j]){
                i++;
            }
            else if(a[i] > b[j]){
                j++;
            }
        }
        if(result.size() == 0)
            result.push_back(0);
        return result;
    }

    std::string minCod(const std::string& str){
        std::string resultado;
        int actualSet = 0, actual , siguiente, interseccion, codini, codact, codcam;
        for(decltype(str.size()) i = 0; i < str.size(); i++){

            actual = (!actualSet)? getSets(str[i])[0]:actualSet;

            if( i == str.size()-1){
                if(i == 0)
                    resultado += firstCode[actual];
                resultado += codify(str[i], actual);
                break;
            }

            siguiente = getSets(str[i+1])[0];
            interseccion = intersect(getSets(str[i]), getSets(str[i+1]))[0];
            if(!interseccion){
                codini = codact = actual;
                actualSet = codcam = siguiente;
            }
            else if(weights[actual] < weights[interseccion]){
                if(2*weights[actual] + weights[siguiente] <= 2*weights[interseccion]){
                    codcam = actualSet = siguiente;
                    codini = codact = actual;
                }
                else{
                    if(actualSet != actual)
                        codini = codact = codcam = actualSet = interseccion;
                    else{
                        codini = codact = actual;
                        codcam = actualSet = siguiente;
                    }
                }
            }
            else if(weights[actual] < weights[interseccion]){
                codini = codact = codcam = actualSet = interseccion;
            }
            else{
                codini= codact = actual;
                actualSet = codcam = getSets(str[i+1]).back();
            }

            if(i == 0)
                resultado += firstCode[codini];

            resultado += codify(str[i], codact) + changeCodeOf(codact, codcam);
        }
        return resultado;
    }
}

namespace p3{


    std::string minCod(const std::string& str, int pos, int code)
    {
        if(pos == 0) return firstCode[code] + codify(str[pos],code);

        int minimum = INT_MAX  ;
        std::string curCod = {};

        for(auto prev_code: getSets(str[pos-1]) ) {
            std::string temp_res =   minCod(str, pos - 1, prev_code) + changeCodeOf(prev_code, code) ;
            if(minimum > temp_res.length()){
                minimum = static_cast<int> (temp_res.length());
                curCod = temp_res;
            }
        }

        return curCod + codify(str[pos],code) ;
    }



    std::string minCod(const std::string& str)
    {
        int minimum = INT_MAX  ;
        int curPos = static_cast<int> (str.length()) - 1;
        std::string codStr = {};
        std::vector<int> sets = getSets(str[curPos]);

        for(auto cod: sets){
            std::string temp_res =  minCod(str, curPos, cod);
            if(minimum > temp_res.length() ){
                minimum = static_cast<int> (temp_res.length()); // just getting the cost length
                codStr = temp_res;
            }

        }

        return codStr;
    }

}

namespace p4{

    std::pair<int,int> minCod(const std::string& str, int pos, int code, std::vector<std::vector<std::pair<int, int>>>& matrix)
    {
        if(pos == 0) return matrix[pos][code];
        if(matrix[pos][code].second != INT_MAX)
            return matrix[pos][code];

        std::pair<int,int> actual, min (-1, INT_MAX);

        for(auto prev_code: getSets(str[pos-1]) ) {
            actual =  minCod(str, pos - 1, prev_code, matrix);
            int cost = actual.second + static_cast<int> (changeCodeOf(prev_code, code).size())+ weights[code];
            if(cost < min.second){
                min.first = prev_code;
                min.second = cost;
            }
        }

        matrix[pos][code] = min;
        return matrix[pos][code];
    }


    std::string minCod(const std::string& str)
    {
        std::vector<std::vector<std::pair<int, int>>> matrix(str.size(), std::vector<std::pair<int, int>>( 5, std::make_pair(-1,INT_MAX)));

        for(auto set: getSets(str[0])){
            matrix[0][set] = std::make_pair(0, 2 + weights[set]);
        }


        int n = static_cast<int> (str.length()) - 1;
        int actual_code;

        std::pair<int,int> actual, min (-1, INT_MAX);

        for(auto cod: getSets(str[n])) {
            actual =  minCod(str, n,cod, matrix);
            if(min.second > actual.second){
                min = actual;
                actual_code = cod;
            }
        }

        std::string res = {};
        int prev_code = min.first;

        for(int i = n ; i > 0; i--){
//            std::cout<<actual_code<<std::endl;

            res = changeCodeOf(prev_code, actual_code) + codify(str[i]
                    , actual_code) + res;
            actual_code = prev_code;
            prev_code = matrix[i-1][prev_code].first;
        }
//        std::cout<<actual_code<<std::endl;

        res = firstCode[actual_code] + codify(str[0], actual_code) +  res;


        return res;
    }

}




namespace p5{
    std::string minCod(const std::string& str)
    {
        std::vector<std::vector<std::pair<int, int>>> matrix(str.size(), std::vector<std::pair<int, int>>( 5, std::make_pair(-1,INT_MAX)));


        for(auto set: getSets(str[0])){
            matrix[0][set] = std::make_pair(0, 2 + weights[set]);
        }

        for(int pos = 1; pos < str.size(); pos++) {
            for (auto code: getSets(str[pos])) {
                for (auto prev_code: getSets(str[pos - 1])) {
                    int local_cost = matrix[pos - 1][prev_code].second +
                                     static_cast<int> (changeCodeOf(prev_code, code).size()) +
                                     weights[code];
                    if (local_cost < matrix[pos][code].second ) {
                        matrix[pos][code].first = prev_code;
                        matrix[pos][code].second = local_cost;
                    }
                }
            }
        }

        int n = static_cast<int> (str.size()) - 1;
        auto a = matrix[n];
        int actual_code = {};
        std::pair<int,int> actual_min = std::make_pair(-1,INT_MAX);
        for(auto code: getSets(str[n]) ){
            if(actual_min.second > matrix[n][code].second){
                actual_min.second = matrix[n][code].second;
                actual_min.first = matrix[n][code].first;
                actual_code = code;
            }
        }


        std::string  res = {};

        int prev_code = actual_min.first;
        for(int i = n ; i > 0; i--){
            res = changeCodeOf(prev_code, actual_code) + codify(str[i]
                    , actual_code) + res;
            actual_code = prev_code;
            prev_code = matrix[i-1][prev_code].first;
        }
        res = firstCode[actual_code] + codify(str[0], actual_code) +  res;
        return res;
    }
}


#endif //ADA_PJ_SOLUTIONS_H
