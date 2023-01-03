
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
    std::vector<std::vector<double> > classified;
    int numT;

/**
 *function get 2 vectors and name of distance to use and return the distance using the distances.h file.
 * @param v1 first vector.
 * @param v2 second vector.
 * @param distanceType name of distance.
 * @return the calculated distance.
 */
    double distance(std::vector<double> v1, std::vector<double> v2, std::string distanceType);

/**
 * the function get input vector, tun over the classified vectors and return the classification of the vector.
 * @param input vector to classify.
 * @param k number of k neighbors.
 * @param disType type of distance.
 * @param numType number of possible classifications.
 * @return classification of the vector.
 */
    int runNeighbors(std::vector<double> input, int kNum, std::string disType, int numType);

/**
 * function get vector of vectors and vector x, insert the new vector and sort x.
 * @param x vector to insert to y.
 * @param y vector of vectors.
 * @return y with x, after removing the vector with 0 in the first element or the biggest first element.
 */
    std::vector<std::vector<double> > kNearestUpdate1(std::vector<double> x, std::vector<std::vector<double> > y);

public:

/**
 * constructor.
 * @param classifiedK vector of classified vectors, where rhe last parameter is the classification.
 */
    KNN(std::vector<std::vector<double> > classifiedK);

/**
 * the function get input from the user and calls the runNeighbors function.
 * @param input the input vector.
 * @return classification.
 */
    int classify(std::vector<double> input, int kNum, std::string disType, int numType);


};

#endif //MITKADEM_EX2_KNN_H