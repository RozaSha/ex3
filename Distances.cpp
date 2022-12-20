#include "Distances.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

/**
 * Distances constructor.
 * @param ve1 first vector.
 * @param ve2 second vector.
 */
Distances::Distances(vector<double> ve1, vector<double> ve2) {
    v1 = ve1;
    v2 = ve2;
}

/**
 * Calculating canberra distance.
 * @param v1 first vector.
 * @param v2 second vector.
 * @return canberra distance between 2 vectors.
 */
double Distances::canberraDistance() {
    vector<double> vec1 = v1, vec2 = v2;
    double distance = 0;
    for (int i = 0; i < v1.size(); i++) {
        double denominator = abs((vec1.at(i)) + 0.0) + abs((vec2.at(i) + 0.0));
        if (denominator == 0) {
            cout << "Can not divide by 0" << endl;
            return -1; // in case the program cannot run because the denominator is 0, the function will return negative number.
        }
        double numerator = abs((vec1.at(i) + 0.0) - (vec2.at(i) + 0.0));
        distance += (numerator + 0.0) / denominator;
    }
    return distance;
}

/**
 * calculating chebyshev distance.
 * @param v1 firs vector.
 * @param v2 second vector.
 * @return chebyshev distance between the 2 vectors.
 */
double Distances::chebyshevDistance() {
    vector<double> vec1 = v1, vec2 = v2;
    double max = 0;
    for (int i = 0; i < v1.size(); i++) {
        double diff = abs((vec1.at(i) + 0.0) - (vec2.at(i) + 0.0));
        if (max < diff)
            max = diff;
    }
    return max;
}

/**
 * calculating minkowski distance.
 * @param v1 first vector.
 * @param v2 second vector.
 * @param parameter parameter to calculate the distance.
 * @return minkowski distance between the 2 vectors.
 */
double Distances::minkowskiDistance(int parameter) {
    vector<double> vec1 = v1, vec2 = v2;
    int p = parameter;
    double sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        double diff = abs((vec1.at(i) + 0.0) - (vec2.at(i)) + 0.0);
        sum += pow(diff, p);
    }
    return pow(sum, 1.0 / p);
}

/**
 * calculating manhattan distance.
 * @param v1 first vector.
 * @param v2 second vector.
 * @return between the 2 vectors
 */
double Distances::manhattanDistance() {
    vector<double> vec1 = v1, vec2 = v2;
    double sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        sum += abs((vec1.at(i) + 0.0) - vec2.at(i));
    }
    return sum;
}

/**
 * calculating euclidean distance using minkowski distance when p = 2.
 * @param v1 first vector.
 * @param v2 second vector.
 * @return between the 2 vectors.
 */
double Distances::euclideanDistance() {
    return minkowskiDistance(2);
}
