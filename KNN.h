
#ifndef MITKADEM_EX2_KNN_H
#define MITKADEM_EX2_KNN_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>

class KNN {
private:
    int k;
    std::string distanceType;
    std::vector<std::vector<double >> classified;
    std::vector<double> input;
    std::vector<std::string> types;
    std::map<int, std::string> numToType;
    std::map<std::string, int> typeToNum;

    void typesToNumbers();

    double distance(std::vector<double> v1, std::vector<double> v2, std::string distanceType);

    int runNeighbors();

public:
    KNN(int kValue, std::string disType, std::vector<double> inputK, std::vector<std::vector<double>> classifiedK,
        std::vector<std::string> type);

    std::string classify();


};

#endif //MITKADEM_EX2_KNN_H
