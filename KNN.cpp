#include "KNN.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include "Distances.h"

/**
 * constructor.
 * @param kValue number of k neighbors.
 * @param disType type of distance.
 * @param classifiedK vector of classified vectors, where rhe last parameter is the classification.
 * @param numType number of possible classifications.
 */
KNN::KNN(int kValue, std::string disType, std::vector<std::vector<double>> classifiedK, int numType) {
    k = kValue;
    distanceType = disType;
    classified = classifiedK;
    numT = numType;
}

/**
 *function get 2 vectors and name of distance to use and return the distance using the distances.h file.
 * @param v1 first vector.
 * @param v2 second vector.
 * @param distanceType name of distance.
 * @return the calculated distance.
 */
double KNN::distance(std::vector<double> v1, std::vector<double> v2, std::string distanceType) {
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
    }
    if (distanceType == "MIN") {
        distance = d.minkowskiDistance(3);
    }
    return distance;
}

/**
 * the function get input vector, tun over the classified vectors and return the classification of the vector.
 * @param input vector to classify.
 * @return classification of the vector.
 */
int KNN::runNeighbors(std::vector<double> input) {
    int i = 0;
    int x = input.size();
    int y = numT;
    int numInKNearest = 0;
    std::vector<std::vector<double>> kNearest;
    //initialize vector of k vectors of zeros. in this vector the function will keep the closest neighbors and their
    // classification.
    for (int j = 0; j < k; j++) {
        std::vector<double> vec(2, 0);
        kNearest.push_back(vec);
    }
    std::vector<double> subVector;
    while (!classified[i].empty()) {//running over the classified vector.
        subVector = {classified[i].begin(), classified[i].end() - 1}; //sub vector without the classification.
        double dis = distance(subVector, input, distanceType);// finding distance.
        if (dis == -1) {//the distance function return -1 if tha function attempt to divide by 0.
            continue;
        }
        if (numInKNearest == 0) {// if the array that stores the k nearest neighbors is empty.
            kNearest[0][0] = dis;
            kNearest[0][1] = classified[i][x];
            numInKNearest += 1;
        } else {
            if (numInKNearest < k) {//if the array that stores the k nearest neighbors isn't full.
                for (int j = 0; j < k; j++) {
                    //the function will move the parameters that smaller than dis to the end, and insert dis in the correct spot.
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
                        //the function will move the parameters that than dis bigger to the start, removing the biggest
                        // number from the vector, and insert dis in the correct spot.
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
    std::vector<int> count(y, 0);
    for (int j = 0; j < k; j++) {
        //count how many neighbors of each classification there are in the k nearest neighbors vector.
        int a = int(kNearest[j][1]);
        count[a] += 1;
    }
    int maxIndex = 0;
    for (int j = 0; j < y; j++) {
        //finds the maximum classification. if there are classification equal in the number of neighbors, it returns
        // the one that come first in the vector.
        if (count[j] > count[maxIndex]) {
            maxIndex = j;
        }
    }
    return maxIndex;
}

/**
 * the function get input from the user and calls the runNeighbors function.
 * @param input the input vector.
 * @return classification.
 */
int KNN::classify(std::vector<double> input) {
    int type = runNeighbors(input);
    return type;
}


