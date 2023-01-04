//
// Created by Nof Golan on 18/12/2022.
//
using namespace std;

#include "PreProcess.h"
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include<algorithm>

/**
 *
 * @param argv a string
 * @return false if argv is not a positive integer true if it is.
 */
bool positiveInteger(const std::string &argv) {
// Check if the argument is a positive integer
    for (char c: argv) {
        if (!isdigit(c) or stoi(argv) == 0) {
            return false;
        }
    }
    return true;
}

/**
 *
 * @param argv a way to measure distance.
 * @return if the measurment exist in this program.
 */
bool distanceMetric(const std::string &argv) {
    if (argv == "AUC" or argv == "MAN" or argv == "CHB" or argv == "CAN" or argv == "MIN") {
        return true;
    }
    return false;
}

// for string delimiter
vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector <string> res;
    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    return res;
}

// function check if all strings in are valid number.
// if number start with . add 0 to beginning if number ends with . add 0 to the end.
// return false if -/+ are not at the beginning of the number or added mor than once
// return false if there are signs not digits/+/-/.
bool inputCheck(vector<string> &vec) {
    for (int i = 0; i < static_cast<int>(vec.size()); i++) {

        string s = vec[i];

        // counting the digits.
        size_t count = 0;
        for (std::string::size_type pos = 0;
             (pos = s.find_first_of("0123456789.-+", pos)) != std::string::npos;
             ++pos) {
            ++count;
        }

        // counting dots.
        size_t countDots = 0;
        for (std::string::size_type pos = 0;
             (pos = s.find_first_of(".", pos)) != std::string::npos;
             ++pos) {
            ++countDots;
        }

        // counting minus.
        size_t countMinus = 0;
        for (std::string::size_type pos = 0;
             (pos = s.find_first_of("-", pos)) != std::string::npos;
             ++pos) {
            ++countMinus;
        }

        // counting minus.
        size_t countPlus = 0;
        for (std::string::size_type pos = 0;
             (pos = s.find_first_of("+", pos)) != std::string::npos;
             ++pos) {
            ++countPlus;
        }

        // if there is more than 1 dot and minus number is not valid.
        if (countDots > 1 || countMinus > 1)
            return false;

        // if there are other signs but "0123456789.-+" number is wrong or there are no correct signs.
        if (count != s.size() || count == 0) {
            return false;
        }

        // if - is not first number is wrong.
        if (countMinus == 1) {
            if (s.at(0) != *"-")
                return false;
            // add 0 at the beginning needed before .
            if (s.at(1) == *".")
                vec[i] = "-0" + s.substr(1, s.size() - 1);
            s = vec[i];
        }

        // if + is not first number is wrong.
        if (countPlus == 1) {
            if (s.at(0) != *"+")
                return false;
            // add 0 at the beginning needed before .
            if (s.at(1) == *".")
                vec[i] = "0" + s.substr(1, s.size() - 1);
            s = vec[i];
        }

        // add 0 at the beginning needed before .
        if (s.at(0) == *".") {
            vec[i] = "0" + s;
            s = vec[i];
        }

        // add 0 at the end needed after .
        if (s.at(s.size() - 1) == *".") {
            vec[i] = s + "0";
            s = vec[i];
        }

        // if there is no . add .0 to the end.
        // add 0 at the end needed after .
        if (countDots == 0) {
            vec[i] = s + ".0";
            s = vec[i];
        }
    }
    return true;
}

double stringToDouble(const std::string &val) {
    return std::stod(val);
}

// get a vector of string and return vector of double.
std::vector<double> convertStringVectortoDoubleVector(const std::vector<std::string> &stringVector) {
    std::vector<double> doubleVector(stringVector.size());
    std::transform(stringVector.begin(), stringVector.end(), doubleVector.begin(), [](const std::string &val){return std::stod(val);});
    return doubleVector;
}