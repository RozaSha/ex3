

#ifndef MITKADEM_EX2_DISTANCES_H
#define MITKADEM_EX2_DISTANCES_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;


class Distances {
private:
    vector<double> v1;
    vector<double> v2;
public:
/**
 * Distances constructor.
 * @param ve1 first vector.
 * @param ve2 second vector.
 */
    Distances(vector<double> ve1, vector<double> ve2);

/**
 * Calculating canberra distance.
 * @param v1 first vector.
 * @param v2 second vector.
 * @return canberra distance between 2 vectors.
 */
    double canberraDistance();

/**
 * calculating chebyshev distance.
 * @param v1 firs vector.
 * @param v2 second vector.
 * @return chebyshev distance between the 2 vectors.
 */
    double chebyshevDistance();

/**
 * calculating minkowski distance.
 * @param v1 first vector.
 * @param v2 second vector.
 * @param parameter parameter to calculate the distance.
 * @return minkowski distance between the 2 vectors.
 */
    double minkowskiDistance(int parameter);

/**
 * calculating manhattan distance.
 * @param v1 first vector.
 * @param v2 second vector.
 * @return between the 2 vectors
 */
    double manhattanDistance();

/**
 * calculating euclidean distance using minkowski distance when p = 2.
 * @param v1 first vector.
 * @param v2 second vector.
 * @return between the 2 vectors.
 */
    double euclideanDistance();


};


#endif //MITKADEM_EX2_DISTANCES_H
