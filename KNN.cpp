#include "KNN.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include "Distances.h"


/**
 *function get 2 vectors and name of distance to use and return the distance using the distances.h file.
 * @param v1 first vector.
 * @param v2 second vector.
 * @param distanceType name of distance.
 * @return the calculated distance.
 */
KNN::KNN(int kValue, std::string disType, std::vector<double> inputK, std::vector<std::vector<double>> classifiedK,
         std::vector<std::string> type) {
    k = kValue;
    distanceType = disType;
    input = inputK;
    classified = classifiedK;
    types = type;
    typesToNumbers();
}

double KNN::distance(std::vector<double> v1, std::vector<double> v2, std::string distanceType) {
    //Do I check the inputs here or in the distances file? need to check if numeric and the same size.
    double distance;
    Distances d(v1, v2);
    if (distanceType == "AUC") {
        distance = d.euclideanDistance();
    }
    if (distanceType == "MAN") {
        distance = d.manhattanDistance();
    }
    if (distanceType == "CHB") {
        distance = d.chebyshevDistance();
    }
    if (distanceType == "CAN") {
        distance = d.canberraDistance();
        if (distance == -1) {
            // throw error
        }
    }
    if (distanceType == "MIN") {
        distance = d.minkowskiDistance(3);
    }
    return distance;
}

int KNN::runNeighbors() {
    int i = 0;
    int x = input.size();
    int y = types.size();
    int numInKNearest = 0;
    std::vector<std::vector<double>> kNearest;
    for (int j = 0; j < k; j++) {
        std::vector<double> vec(2, 0);
        kNearest.push_back(vec);
    }
    //double kNearest[k][2] = {};
    std::vector<double> subVector;
    while (!classified[i].empty()) {
        subVector = {classified[i].begin(), classified[i].end() - 1};
        double dis = distance(subVector, input, distanceType);
        if (numInKNearest == 0) {// if the array that stores the k nearest neighbors is empty.
            kNearest[0][0] = dis;
            kNearest[0][1] = classified[i][x];
            numInKNearest += 1;
        } else {
            if (numInKNearest < k) {//if the array that stores the k nearest neighbors isn't full.
                for (int j = 0; j < k; j++) {
                    if (kNearest[k - j - 2][0] < dis) {
                        kNearest[k - j - 1][0] = kNearest[k - j - 2][0];
                        kNearest[k - j - 1][1] = kNearest[k - j - 2][1];
                    } else {
                        kNearest[k - j - 1][0] = dis;
                        kNearest[k - j - 1][1] = classified[i][x];
                        break;
                    }
                }
                numInKNearest += 1;
            } else {
                if (dis <
                    kNearest[0][0]) {//when the new distance smaller than the biggest distance in k nearest neighbors array.
                    for (int j = 0; j < k; j++) {
                        if (kNearest[j + 1][0] > dis) {
                            kNearest[j][0] = kNearest[j + 1][0];
                            kNearest[j][1] = kNearest[j + 1][1];
                        } else {
                            kNearest[j][0] = dis;
                            kNearest[j][1] = classified[i][x];
                            break;
                        }
                    }
                }
            }
        }
        i += 1;
    }
    //int count[y] = {};
    std::vector<int> count(y, 0);
    for (int j = 0; j < k; j++) {
        int a = int(kNearest[j][0]);
        count[a] += 1;
    }
    int maxIndex = 0;
    for (int j = 0; j < k; j++) {
        if (count[j] > count[maxIndex]) {
            maxIndex = j;
        }
    }
    return maxIndex;
}

std::string KNN::classify() {
    int type = runNeighbors();
    return numToType[type];
}

void KNN::typesToNumbers() {
    int size = types.size();
    for (int i = 0; i < size; i++) {
        typeToNum.insert({types[i], i});
        numToType.insert({i, types[i]});
    }
}

