//
// Created by Nof Golan on 16/12/2022.
//

#ifndef AP_EX_2_PREPROCESS_H
#define AP_EX_2_PREPROCESS_H

using namespace std;
#include <string>
#include <vector>


bool positiveInteger(const std::string& argv);
bool distanceMetric(const std::string& argv);
vector<string> split (string s, string delimiter);
bool inputCheck(vector<string>& vec);
std::vector<double> convertStringVectortoDoubleVector(const std::vector<std::string>& stringVector);



#endif //AP_EX_2_PREPROCESS_H